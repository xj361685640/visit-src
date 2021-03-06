/*****************************************************************************
*
* Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//  File: avtCoordSystemConvert.C
// ************************************************************************* //

#include <avtCoordSystemConvert.h>

#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDataSet.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkRectilinearGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDoubleArray.h>
#include <vtkAppendFilter.h>

#include <vtkVisItUtility.h>
#include <vtkIdList.h>

#include <avtDatasetExaminer.h>
#include <avtExtents.h>

#include <vector>

typedef void(*xformFunc)(double *, const double *);
static vtkDataSet *CreateNewDataset(vtkDataSet *in_ds, vtkPoints *newPts);

// ****************************************************************************
//  Method: avtCoordSystemConvert constructor
//
//  Programmer: Hank Childs
//  Creation:   Fri Jun 27 16:41:32 PST 2003
//
//  Modifications:
//    Jeremy Meredith, Fri Aug  7 15:34:37 EDT 2009
//    Initialize vectorTransformMethod.
//
// ****************************************************************************

avtCoordSystemConvert::avtCoordSystemConvert()
{
    inputSys  = CARTESIAN;
    outputSys = CARTESIAN;
    continuousPhi = false;
    vectorTransformMethod = AsDirection;
}


// ****************************************************************************
//  Method: avtCoordSystemConvert destructor
//
//  Programmer: Hank Childs
//  Creation:   Fri Jun 27 16:41:32 PST 2003
//
//  Modifications:
//
// ****************************************************************************

avtCoordSystemConvert::~avtCoordSystemConvert()
{
}


// ****************************************************************************
//  Function: CylindricalToCartesianPoint
//
//  Purpose:
//      Converts cylindrical coordinates to cartesian coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
//
// ****************************************************************************

static void 
CylindricalToCartesianPoint(double *newpt, const double *pt)
{
    newpt[0] = pt[0] * cos(pt[1]);
    newpt[1] = pt[0] * sin(pt[1]);
    newpt[2] = pt[2];
}

// ****************************************************************************
//  Function: SphericalToCartesianPoint
//
//  Purpose:
//      Converts spherical coordinates to cartesian coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
//    Jeremy Meredith, Wed Jun  3 16:41:35 EDT 2009
//    Reversed sense of 2nd and 3rd spherical components to match ISO 31-11.
//    Removed "in2D" setting.
//
// ****************************************************************************

static void 
SphericalToCartesianPoint(double *newpt, const double *pt)
{
    newpt[0] = pt[0]*sin(pt[1])*cos(pt[2]);
    newpt[1] = pt[0]*sin(pt[1])*sin(pt[2]);
    newpt[2] = pt[0]*cos(pt[1]);
}

// ****************************************************************************
//  Function: CartesianToCylindricalPoint
//
//  Purpose:
//      Converts cartesian coordinates to cylindrical coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
//    Jeremy Meredith, Fri Aug  7 15:34:16 EDT 2009
//    Removed "in2D" setting.
// ****************************************************************************

static void 
CartesianToCylindricalPoint(double *newpt, const double *pt)
{
    newpt[0] = sqrt(pt[0]*pt[0] + pt[1]*pt[1]);
    newpt[1] = atan2(pt[1], pt[0]);
    if (newpt[1] < 0.)
      newpt[1] += 2.0 * M_PI;
    newpt[2] = pt[2];
}

// ****************************************************************************
//  Function: CartesianToSphericalPoint
//
//  Purpose:
//      Converts cartesian coordinates to spherical coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
// ****************************************************************************

static void 
CartesianToSphericalPoint(double *newpt, const double *pt)
{
    newpt[0] = sqrt(pt[0]*pt[0] + pt[1]*pt[1] + pt[2]*pt[2]);
    newpt[1] = acos ( pt[2]/newpt[0] );
    newpt[2] = atan2( pt[1], pt[0]);
    if (newpt[2] < 0.)
        newpt[2] += 2.0 * M_PI;
}

// ****************************************************************************
//  Function: SphericalToCylindricalPoint
//
//  Purpose:
//      Converts spherical coordinates to cylindrical coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
//
// ****************************************************************************

static void 
SphericalToCylindricalPoint(double *newpt, const double *pt)
{
    newpt[0] = pt[0] * sin(pt[1]);
    newpt[1] = pt[2];             
    newpt[2] = pt[0] * cos(pt[1]);
}

// ****************************************************************************
//  Function: CylindricalToSphericalPoint
//
//  Purpose:
//      Converts cylindrical coordinates to spherical coordinates.
//
//  Programmer: Dave Bremer
//  Creation:   Wed Oct 17 14:24:01 PDT 2007
//
//  Modifications:
//    Jeremy Meredith, Wed Jun  3 16:41:35 EDT 2009
//    Reversed sense of 2nd and 3rd spherical components to match ISO 31-11.
//    Removed "in2D" setting.
//
// ****************************************************************************

static void 
CylindricalToSphericalPoint(double *newpt, const double *pt)
{
    newpt[0] = sqrt(pt[0]*pt[0] + pt[2]*pt[2]);
    newpt[1] = atan2(pt[0], pt[2]);            
    if (newpt[1] < 0.)
        newpt[1] += 2.0 * M_PI;
    newpt[2] = pt[1];                          
}

// ****************************************************************************
//  Function:  TransformSingleVector
//
//  Purpose:
//    Transform a single vector, given its old value, its 3d location, 
//    and a selection of one of the vector transformation methods.
//
//  Arguments:
//    method     the choice of xform method
//    xf         the coordinate system conversion function
//    newvec     the output vector value
//    vec        the input vector value
//    newpt      the new point the vector will originate from
//    pt         the original point the vector originated from
//
//  Programmer:  Jeremy Meredith
//  Creation:    August  7, 2009
//
//  Modifications:
//    Kathleen Bonnell, Thu Dec  9 14:53:18 PST 2010
//    Normalize the vector before projection in the AsDirection case.
//
// ****************************************************************************

inline static void 
TransformSingleVector(avtCoordSystemConvert::VectorTransformMethod method,
                      xformFunc xf,
                      double *newvec, const double *const vec,
                      const double *const newpt, const double *const pt)
{
    const double instantEps    = 1.e-5;
    const double instantEpsInv = 1.e+5;

    switch (method)
    {
      case avtCoordSystemConvert::None:
        newvec[0] = vec[0];
        newvec[1] = vec[1];
        newvec[2] = vec[2];
        break;
      case avtCoordSystemConvert::AsPoint:
        xf(newvec, vec);
        break;
      case avtCoordSystemConvert::AsDisplacement:
        {
        double tmpvec[3] = {vec[0] + pt[0],
                            vec[1] + pt[1],
                            vec[2] + pt[2]};
        xf(newvec, tmpvec);
        newvec[0] -= newpt[0];
        newvec[1] -= newpt[1];
        newvec[2] -= newpt[2];
        }
        break;
      case avtCoordSystemConvert::AsDirection:
        {
        double tmpvec[3] = {0., 0., 0.};
        double mag = sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
        if (mag != 0.)
        {
            tmpvec[0] = vec[0]/mag;
            tmpvec[1] = vec[1]/mag;
            tmpvec[2] = vec[2]/mag;
        }
        tmpvec[0] = instantEps*tmpvec[0] + pt[0];
        tmpvec[1] = instantEps*tmpvec[1] + pt[1];
        tmpvec[2] = instantEps*tmpvec[2] + pt[2];

        xf(newvec, tmpvec);
        newvec[0] = (newvec[0] - newpt[0]) * instantEpsInv *mag;
        newvec[1] = (newvec[1] - newpt[1]) * instantEpsInv *mag;
        newvec[2] = (newvec[2] - newpt[2]) * instantEpsInv *mag;
        }
        break;
    }
}

// ****************************************************************************
//  Function: Transform
//
//  Purpose:
//      Converts one coordinate system to another.
//
//      More info at: 
//      http://www.geom.uiuc.edu/docs/reference/CRC-formulas/node42.html
//      (For the record, I did this myself and only *confirmed* the formulas at
//      this site.)
//
//  Programmer: Hank Childs
//  Creation:   June 28, 2003
//
//  Modifications:
//    Hank Childs, Tue Nov 15 15:40:04 PST 2005
//    Add support for 2D.  Also re-order coordinates.
//
//    Dave Bremer, Wed Oct 17 14:24:01 PDT 2007
//    Factored core function out, and added transform of vector data.
//
//    Jeremy Meredith, Fri Aug  7 15:37:28 EDT 2009
//    Made this function apply to all types of coordinate transforms
//    to avoid code duplication.  Added four different user-selectable
//    vector transformation methods.  Added vector transform code
//    to this function; since some of the methods require the original
//    and transformed cell/point coordinates, so it has to be done here.
//
//    Kathleen Biagas, Tue Aug 21 16:53:09 MST 2012
//    Preserve coordinate type.
//
//    Kathleen Biagas, Thu Jun 4 16:51:27 MST 2015
//    Pass along FieldData.
//
// ****************************************************************************

static vtkDataSet *
Transform(vtkDataSet *in_ds,
          bool continuousPhi,
          avtCoordSystemConvert::VectorTransformMethod vectorTransformMethod,
          xformFunc xf)
{
    int numPts  = in_ds->GetNumberOfPoints();
    int numCells = in_ds->GetNumberOfCells();

    //
    // Transform the points
    //
    vtkPoints *pts = vtkVisItUtility::GetPoints(in_ds);
    vtkPoints *newPts = vtkPoints::New(pts->GetDataType());
    newPts->SetNumberOfPoints(numPts);

    // When converting from cartesian to cylindrical with a continuous
    // phi the points must be converted using the points ids so to be
    // contiguous. If the points are not part of a VTK_POLY_LINE just
    // convert the points.
    if( continuousPhi )
    {
        // Set the wrap value for +/- pi at 75% which accounts for
        // large steps but avoids the "wrap" at 0.
        double pi_low  = 0.25 * M_PI;
        double pi_high = 1.75 * M_PI;

        for (int c=0; c<in_ds->GetNumberOfCells(); ++c)
        {
            vtkIdList *idlist = vtkIdList::New();
            in_ds->GetCellPoints(c, idlist);
            
            double lastPhi = 0, angle = 0;
            
            for (int j=0; j<idlist->GetNumberOfIds(); ++j)
            {
                double pt[3], newpt[3];
                pts->GetPoint(idlist->GetId(j), pt);
                xf(newpt, pt);
                
                if( in_ds->GetCellType(c) == VTK_POLY_LINE )
                {
                    // Check for a wrapped-around from -pi radians to pi
                    // radians.
                    if( lastPhi < pi_low && pi_high < newpt[1] )
                    {
                        angle -= 2.0 * M_PI;
                    }
                    else if( newpt[1] < pi_low && pi_high < lastPhi )
                    {
                        angle += 2.0 * M_PI;
                    }
                    
                    lastPhi = newpt[1];
                    
                    newpt[1] += angle;
                }
                
                newPts->SetPoint(idlist->GetId(j), newpt);
            }

            idlist->Delete();
        }
    }
    else
    {
        for (int i=0; i<numPts; ++i)
        {
            double pt[3], newpt[3];
            pts->GetPoint(i, pt);
            xf(newpt, pt);
            newPts->SetPoint(i, newpt);
        }
    }

    vtkDataSet *rv = CreateNewDataset(in_ds, newPts);

    //
    // Transform the vectors if necessary
    //
    enum Pass { PointPass, CellPass };
    for (int p = 0; p <= 1; p++)
    {
        Pass pass = Pass(p);

        // Skip out early for no-op
        if (vectorTransformMethod == avtCoordSystemConvert::None)
            continue;

        // Get some values for this pass
        vtkDataSetAttributes *dsatts;
        if (pass==PointPass)
            dsatts = rv->GetPointData();
        else
            dsatts = rv->GetCellData();
        int numTuples = (pass==PointPass) ? numPts : numCells;
        int numArrays = dsatts->GetNumberOfArrays();
        vtkDataArray *activeArr = dsatts->GetVectors();

        // Are we doing a transform that needs point coordinates?
        bool needPointCoordinates =
            (vectorTransformMethod == avtCoordSystemConvert::AsDisplacement ||
             vectorTransformMethod == avtCoordSystemConvert::AsDirection);

        // Point coordinates for the Cell pass means cell centroids
        // Calclate those (original and transformed) here.
        vtkDoubleArray *cellCoordsOld = vtkDoubleArray::New();
        vtkDoubleArray *cellCoordsNew = vtkDoubleArray::New();
        if (pass == CellPass && needPointCoordinates)
        {
            cellCoordsOld->SetNumberOfComponents(3);
            cellCoordsOld->SetNumberOfTuples(numCells);
            cellCoordsNew->SetNumberOfComponents(3);
            cellCoordsNew->SetNumberOfTuples(numCells);
            vtkIdList *ptIds = vtkIdList::New();
            double pt[3]    = {0,0,0};
            double newpt[3] = {0,0,0};
            for (int n = 0 ; n < numCells ; n++)
            {
                in_ds->GetCellPoints(n, ptIds);
                int numCellPts = ptIds->GetNumberOfIds();
                pt[0] = pt[1] = pt[2] = 0.0;
                for (int j = 0; j < numCellPts; j++)
                {
                    double tmppt[3];
                    pts->GetPoint(ptIds->GetId(j), tmppt);
                    pt[0] += tmppt[0];
                    pt[1] += tmppt[1];
                    pt[2] += tmppt[2];
                }
                pt[0] /= double(numCellPts);
                pt[1] /= double(numCellPts);
                pt[2] /= double(numCellPts);
                xf(newpt, pt); // need to transform it, too
                cellCoordsOld->SetTuple(n, pt);
                cellCoordsNew->SetTuple(n, newpt);
            }
            ptIds->Delete();
        }

        //
        // Loop over the arrays
        //
        for (int k = numArrays-1 ; k >= 0 ; k--)
        {
            // Make sure we want to transform this array
            vtkDataArray *arr = dsatts->GetArray(k);
            int ncomp = arr->GetNumberOfComponents();
            if (ncomp != 2 && ncomp != 3)
                continue;
            if (arr->GetName() != NULL)
            {
                std::string name = arr->GetName();
                if (name == "avtOriginalNodeNumbers" ||
                    name == "avtOriginalCellNumbers" ||
                    name == "avtSubsets")
                    continue;
            }

            // Create an output array to fill
            vtkDataArray *arr_new = vtkDataArray::CreateDataArray(arr->GetDataType());
            if (arr->GetName() != NULL)
                arr_new->SetName(arr->GetName());
            arr_new->SetNumberOfComponents(ncomp);
            arr_new->SetNumberOfTuples(numTuples);

            // fill the output array
            for (int n = 0 ; n < numTuples ; n++)
            {
                // Get the old and new point locations.
                double tup[3] = {0,0,0}, newtup[3] = {0,0,0};
                double pt[3]  = {0,0,0}, newpt[3]  = {0,0,0};
                if (needPointCoordinates && pass==PointPass)
                {
                    pts->GetPoint(n, pt);
                    newPts->GetPoint(n, newpt);
                }
                else if (needPointCoordinates && pass==CellPass)
                {
                    cellCoordsOld->GetTuple(n, pt);
                    cellCoordsNew->GetTuple(n, newpt);
                }

                // Get the old vector values.
                arr->GetTuple(n, tup);
                // Transform it.
                TransformSingleVector(vectorTransformMethod, xf,
                                      newtup, tup, newpt, pt);
                // And store it.
                arr_new->SetTuple(n, newtup);
            }

            // Set up the active variables as necessary
            bool isActive = false;
            if (activeArr &&
                activeArr->GetName() != NULL &&
                arr->GetName() != NULL &&
                strcmp(activeArr->GetName(), arr->GetName()) == 0)
                isActive = true;
            if (arr->GetName() != NULL)
                dsatts->RemoveArray(arr->GetName());
            dsatts->AddArray(arr_new);
            arr_new->Delete();
            if (isActive)
                dsatts->SetVectors(arr_new);
        }
        cellCoordsOld->Delete();
        cellCoordsNew->Delete();
    }

    rv->GetFieldData()->PassData(in_ds->GetFieldData());
    pts->Delete();
    newPts->Delete();

    return rv;
}


// ****************************************************************************
//  Function: FixWraparounds
//
//  Purpose:
//      Locates cells where the dataset has been wrapped-around from 0 radians
//      to 2*pi radians.
//
//  Programmer: Hank Childs
//  Creation:   July 7, 2003
//
//  Modifications:
//
//    Hank Childs, Mon Feb 28 15:04:00 PST 2011
//    Fix wraparound for poly data as well.
//
//    Kathleen Biagas, Tue Aug 21 16:53:32 MST 2012
//    Preserve coordinate type.
//
// ****************************************************************************

static vtkDataSet *
FixWraparounds(vtkDataSet *in_ds, int comp_idx)
{
    if (in_ds->GetDataObjectType() != VTK_UNSTRUCTURED_GRID &&
        in_ds->GetDataObjectType() != VTK_POLY_DATA)
    {
        in_ds->Register(NULL);
        return in_ds;
    }

    vtkDataSet *out_ds = NULL;

    int ncells = in_ds->GetNumberOfCells();

    vtkPoints *pts = vtkVisItUtility::GetPoints(in_ds);
    int npts = pts->GetNumberOfPoints();

    vtkPoints *new_pts = vtkPoints::New(pts->GetDataType());
    new_pts->SetNumberOfPoints(2*npts);

    if (in_ds->GetDataObjectType() == VTK_UNSTRUCTURED_GRID)
    {
        vtkUnstructuredGrid *new_grid = vtkUnstructuredGrid::New();
        new_grid->SetPoints(new_pts);
        new_grid->Allocate(2*ncells);
        out_ds = new_grid;
    }
    else if (in_ds->GetDataObjectType() == VTK_POLY_DATA)
    {
        vtkPolyData *new_polydata = vtkPolyData::New();
        new_polydata->SetPoints(new_pts);
        new_polydata->Allocate(2*ncells);
        out_ds = new_polydata;
    }

    vtkPointData *in_pd  =  in_ds->GetPointData();
    vtkPointData *out_pd = out_ds->GetPointData();
    out_pd->CopyAllocate(in_pd, 2*npts);
   
    for (int i = 0 ; i < npts ; i++)
    {
        double pt[3];
        pts->GetPoint(i, pt);

        new_pts->SetPoint(2*i, pt);

        if (pt[comp_idx] > M_PI)
            pt[comp_idx] -= 2.0 * M_PI;
        else
            pt[comp_idx] += 2.0 * M_PI;

        new_pts->SetPoint(2*i+1, pt);
        out_pd->CopyData(in_pd, i, 2*i);
        out_pd->CopyData(in_pd, i, 2*i+1);
    }
 
    int cellCnt = 0;

    vtkCellData *out_cd = out_ds->GetCellData();
    vtkCellData *in_cd  = in_ds->GetCellData();
    out_cd->CopyAllocate(in_cd, 2*ncells);
   
    float zeroPiCutoff = 0.25 * M_PI;
    float twoPiCutoff  = 1.75 * M_PI;

    for (int i = 0 ; i < ncells ; i++)
    {
        vtkIdList *idlist = vtkIdList::New();
        in_ds->GetCellPoints(i, idlist);
        int numCellPts = idlist->GetNumberOfIds();

        bool closeToZero = false;
        bool closeToTwoPi = false;
        bool *closeToLow = new bool[numCellPts];

        vtkIdType *new_ids = new vtkIdType[numCellPts];

        for (int j = 0 ; j < numCellPts ; j++)
        {
            double pt[3];
            pts->GetPoint(idlist->GetId(j), pt);

            if (pt[comp_idx] > twoPiCutoff)
                closeToTwoPi = true;
            if (pt[comp_idx] < zeroPiCutoff)
                closeToZero  = true;

            closeToLow[j] = (pt[comp_idx] < M_PI ? false : true);
        }

        if (closeToTwoPi && closeToZero)
        {
            // Make two cells -- start with the one close to 0 radians.
            for (int j = 0 ; j < numCellPts ; j++)
                new_ids[j] = (closeToLow[j] ? 2*idlist->GetId(j) :
                                              2*idlist->GetId(j)+1);

            if (in_ds->GetDataObjectType() == VTK_UNSTRUCTURED_GRID)
              ((vtkUnstructuredGrid*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);
            else // if (in_ds->GetDataObjectType() == VTK_POLY_DATA)
              ((vtkPolyData*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);

            out_cd->CopyData(in_cd, i, cellCnt++);
            
            // Make the second cells -- create the one close to pie radians.
            for (int j = 0 ; j < numCellPts ; j++)
                new_ids[j] = (!closeToLow[j] ? 2*idlist->GetId(j) :
                                               2*idlist->GetId(j)+1);

            if (in_ds->GetDataObjectType() == VTK_UNSTRUCTURED_GRID)
              ((vtkUnstructuredGrid*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);
            else // if (in_ds->GetDataObjectType() == VTK_POLY_DATA)
              ((vtkPolyData*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);

            out_cd->CopyData(in_cd, i, cellCnt++);

        }
        else
        {
            for (int j = 0 ; j < numCellPts ; j++)
              new_ids[j] = 2*idlist->GetId(j);

            if (in_ds->GetDataObjectType() == VTK_UNSTRUCTURED_GRID)
              ((vtkUnstructuredGrid*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);
            else // if (in_ds->GetDataObjectType() == VTK_POLY_DATA)
              ((vtkPolyData*) out_ds)->
                InsertNextCell(in_ds->GetCellType(i), numCellPts, new_ids);

            out_cd->CopyData(in_cd, i, cellCnt++);
        }

        delete[] closeToLow;
        delete[] new_ids;
    }

    out_ds->Squeeze();
    new_pts->Delete();

    return out_ds;
}

// ****************************************************************************
//  Method: avtCoordSystemConvert::ExecuteData
//
//  Purpose:
//      Sends the specified input and output through the CoordConvert filter.
//
//  Arguments:
//      in_dr      The input data representation.
//
//  Returns:       The output data representation.
//
//  Programmer: Hank Childs
//  Creation:   Fri Jun 27 16:41:32 PST 2003
//
//  Modifications:
//
//    Hank Childs, Tue Nov 15 15:40:04 PST 2005
//    Add support for 2D.
//
//    Jeremy Meredith, Fri Aug  7 15:35:29 EDT 2009
//    Call a common transform function to avoid code duplication.
//
//    Eric Brugger, Mon Jul 21 10:33:06 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

avtDataRepresentation *
avtCoordSystemConvert::ExecuteData(avtDataRepresentation *in_dr)
{
    //
    // Get the VTK data set.
    //
    vtkDataSet *in_ds = in_dr->GetDataVTK();

    std::vector<vtkDataSet *> deleteList;

    CoordSystem ct_current = inputSys;

    vtkDataSet *cur_ds = in_ds;
    vtkDataSet *new_ds;

    if( ct_current == CARTESIAN && outputSys == CYLINDRICAL )
        new_ds = Transform(cur_ds,
                           continuousPhi, vectorTransformMethod,
                           CartesianToCylindricalPoint);
    else if( ct_current == CARTESIAN && outputSys == SPHERICAL )
      new_ds = Transform(cur_ds,
                         continuousPhi, vectorTransformMethod,
                         CartesianToSphericalPoint);

    else if( ct_current == CYLINDRICAL && outputSys == CARTESIAN )
      new_ds = Transform(cur_ds,
                         continuousPhi, vectorTransformMethod,
                         CylindricalToCartesianPoint);

    else if( ct_current == CYLINDRICAL && outputSys == SPHERICAL )
      new_ds = Transform(cur_ds,
                         continuousPhi, vectorTransformMethod,
                         CylindricalToSphericalPoint);

    else if( ct_current == SPHERICAL && outputSys == CARTESIAN )
      new_ds = Transform(cur_ds,
                         continuousPhi, vectorTransformMethod,
                         SphericalToCartesianPoint);

    else if( ct_current == SPHERICAL && outputSys == CYLINDRICAL )
      new_ds = Transform(cur_ds,
                         continuousPhi, vectorTransformMethod,
                         SphericalToCylindricalPoint);
    else
      return in_dr;
      
    deleteList.push_back(new_ds);
    cur_ds = new_ds;

    if (outputSys == SPHERICAL)
    {
        cur_ds = FixWraparounds(cur_ds, 1);
        deleteList.push_back(cur_ds);
        cur_ds = FixWraparounds(cur_ds, 2);
        deleteList.push_back(cur_ds);
    }
    else if (outputSys == CYLINDRICAL)
    {
        if( ct_current != CARTESIAN || !continuousPhi )
        {
          cur_ds = FixWraparounds(cur_ds, 1);
          deleteList.push_back(cur_ds);
        }
    }

    avtDataRepresentation *out_dr = new avtDataRepresentation(cur_ds,
        in_dr->GetDomain(), in_dr->GetLabel());

    for (unsigned int i = 0 ; i < deleteList.size() ; i++)
    {
         deleteList[i]->Delete();
    }

    return out_dr;
}


// ****************************************************************************
//  Method: avtCoordSystemConvert::PostExecute
//
//  Purpose:
//      This is called to set up the output extents.
//
//  Programmer: Hank Childs
//  Creation:   June 30, 2003
//
//  Modifications:
//
//    Hank Childs, Tue Jul  5 09:23:13 PDT 2005
//    Properly create extents.
//
//    Hank Childs, Thu Aug 26 13:47:30 PDT 2010
//    Change extents names.
//
// ****************************************************************************
 
void
avtCoordSystemConvert::PostExecute()
{
    avtDataAttributes &outAtts = GetOutput()->GetInfo().GetAttributes();
    outAtts.GetOriginalSpatialExtents()->Clear();
    outAtts.GetDesiredSpatialExtents()->Clear();
    outAtts.GetActualSpatialExtents()->Clear();

    double bounds[6];
    avtDataset_p ds = GetTypedOutput();
    avtDatasetExaminer::GetSpatialExtents(ds, bounds);
    outAtts.GetThisProcsOriginalSpatialExtents()->Set(bounds);
}


// ****************************************************************************
//  Function: CreateNewDataset
//
//  Purpose:
//      Creates a dataset just like the input, except with the new set of
//      points.
//
//  Programmer: Hank Childs
//  Creation:   June 30, 2003
//
// ****************************************************************************

static vtkDataSet *
CreateNewDataset(vtkDataSet *in_ds, vtkPoints *newPts)
{
    vtkDataSet *rv = NULL;

    int dstype = in_ds->GetDataObjectType();

    if (dstype == VTK_POLY_DATA ||
        dstype == VTK_STRUCTURED_GRID ||
        dstype == VTK_UNSTRUCTURED_GRID)
    {
        vtkPointSet *rv2 = (vtkPointSet *) in_ds->NewInstance();
        rv2->ShallowCopy(in_ds);
        rv2->SetPoints(newPts);

        rv = rv2;
    }
    else if (dstype == VTK_RECTILINEAR_GRID)
    {
        int dims[3];
        vtkRectilinearGrid *rg = (vtkRectilinearGrid *) in_ds;
        rg->GetDimensions(dims);

        vtkStructuredGrid *rv2 = vtkStructuredGrid::New();
        rv2->SetDimensions(dims);
        rv2->GetPointData()->ShallowCopy(in_ds->GetPointData());
        rv2->GetCellData()->ShallowCopy(in_ds->GetCellData());
        rv2->SetPoints(newPts);

        rv = rv2;
    }
    else
    {
      EXCEPTION1(ImproperUseException, "The dataset type can not be converted.");
    }

    return rv;
}


// ****************************************************************************
//  Method: avtCoordSystemConvert::UpdateDataObjectInfo
//
//  Purpose:
//      Changes the labels of the axes
//
//  Programmer: Hank Childs
//  Creation:   June 8, 2005
//
//  Modifications:
//
//    Hank Childs, Tue Nov 15 15:40:04 PST 2005
//    Re-order coordinates.
//
//    Hank Childs, Thu Jan  7 16:20:04 PST 2010
//    Invalidate spatial meta-data.
//
// ****************************************************************************

void
avtCoordSystemConvert::UpdateDataObjectInfo(void)
{
    avtDataAttributes &inAtts  = GetInput()->GetInfo().GetAttributes();
    avtDataAttributes &outAtts = GetOutput()->GetInfo().GetAttributes();
    if (inputSys == CARTESIAN)
    {
        if (outputSys == SPHERICAL)
        {
            if (inAtts.GetXLabel() == "X-Axis" ||
                inAtts.GetXLabel() == "X Axis")
                outAtts.SetXLabel("Radius");
            else
                outAtts.SetXLabel(std::string("Radius / ") + 
                                  inAtts.GetXLabel());

            if (inAtts.GetYLabel() == "Y-Axis" ||
                inAtts.GetYLabel() == "Y Axis")
                outAtts.SetYLabel("Theta");
            else
                outAtts.SetYLabel(std::string("Theta / ") + 
                                  inAtts.GetYLabel());

            if (inAtts.GetZLabel() == "Z-Axis" ||
                inAtts.GetZLabel() == "Z Axis")
                outAtts.SetZLabel("Phi");
            else
                outAtts.SetZLabel(std::string("Phi / ") + 
                                  inAtts.GetZLabel());
        }
        else if (outputSys == CYLINDRICAL)
        {
            if (inAtts.GetXLabel() == "X-Axis" ||
                inAtts.GetXLabel() == "X Axis")
                outAtts.SetXLabel("Radius");
            else
                outAtts.SetXLabel(std::string("Radius / ") + 
                                   inAtts.GetXLabel());

            if (inAtts.GetYLabel() == "Y-Axis" ||
                inAtts.GetYLabel() == "Y Axis")
                outAtts.SetYLabel("Theta");
            else
                outAtts.SetYLabel(std::string("Theta / ") + 
                                   inAtts.GetYLabel());

            if (inAtts.GetZLabel() == "Z-Axis" ||
                inAtts.GetZLabel() == "Z Axis")
                outAtts.SetZLabel("Height");
            else
                outAtts.SetZLabel(std::string("Height / ") + 
                                   inAtts.GetZLabel());
        }
    }
    if (outputSys == SPHERICAL)
    {
        outAtts.SetYUnits("radians");
        outAtts.SetZUnits("radians");
    }
    else if (outputSys == CYLINDRICAL)
    {
        outAtts.SetYUnits("radians");
    }
    GetOutput()->GetInfo().GetValidity().SetPointsWereTransformed(true);
    GetOutput()->GetInfo().GetValidity().InvalidateSpatialMetaData();
}
