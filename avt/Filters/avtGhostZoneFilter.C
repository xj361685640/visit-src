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
//                            avtGhostZoneFilter.C                           //
// ************************************************************************* //

#include <avtGhostZoneFilter.h>

#include <vtkCellData.h>
#include <vtkDataSet.h>
#include <vtkDataSetRemoveGhostCells.h>
#include <vtkPointData.h>
#include <vtkRectilinearGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkUnsignedCharArray.h>

#include <DebugStream.h>


// ****************************************************************************
//  Method: avtGhostZoneFilter constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
//  Modifications:
//
//    Hank Childs, Wed Dec 20 09:25:42 PST 2006
//    Initialize ghostDataMustBeRemoved.
//
//    Hank Childs, Fri Aug  3 13:27:27 PDT 2007
//    Initialize ghostNodeTypesToRemove.
//
//    Hank Childs, Sun Oct 28 11:17:32 PST 2007
//    Initialize ghostZoneTypesToRemove.
//
// ****************************************************************************

avtGhostZoneFilter::avtGhostZoneFilter()
{
    ghostDataMustBeRemoved = false;
    ghostNodeTypesToRemove = 0xFF; // remove all types if must be removed
    ghostZoneTypesToRemove = 0xFF; // remove all types if must be removed
}


// ****************************************************************************
//  Method: avtGhostZoneFilter destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtGhostZoneFilter::~avtGhostZoneFilter()
{
    ;
}

// ****************************************************************************
//  Function: ExamineGhostArray
//
//  Purpose: Efficiently examine ghost array data for whether all entities are
//  ghost and/or whether all entities on exterior boundary are ghost.
//
//  Programmer: Mark C. Miller
//  Creation:   Thu Sep 14 11:17:39 PDT 2017
//
// ****************************************************************************
static void
ExamineGhostArray(vtkDataSet *in_ds, bool zones, bool haveGhost,
    unsigned char typesToRemove, bool *_allGhost, bool *_allLogBndGhost)
{
    if (!haveGhost)
    {
        if (_allGhost) *_allGhost = false;
        if (_allLogBndGhost) *_allLogBndGhost = false;
        return;
    }

    vtkUnsignedCharArray *ghostArray = zones ?
        (vtkUnsignedCharArray *) in_ds->GetCellData()->GetArray("avtGhostZones") :
        (vtkUnsignedCharArray *) in_ds->GetPointData()->GetArray("avtGhostNodes");
    const int nVals = zones ? in_ds->GetNumberOfCells() : in_ds->GetNumberOfPoints();

    unsigned char const *ghostVals = ghostArray->GetPointer(0);
    bool allGhost = true;
    for (int i = 0 ; i < nVals && allGhost; i++)
    {
        if ((ghostVals[i] & typesToRemove) == 0x00)
            allGhost = false;
    }
    if (_allGhost) *_allGhost = allGhost;

    bool allLogBndGhost = true;
    if (in_ds->GetDataObjectType() == VTK_RECTILINEAR_GRID ||
        in_ds->GetDataObjectType() == VTK_STRUCTURED_GRID)
    {
        int dims[3];
        if (in_ds->GetDataObjectType() == VTK_RECTILINEAR_GRID)
        {
            vtkRectilinearGrid *rg = vtkRectilinearGrid::SafeDownCast(in_ds);
            rg->GetDimensions(dims);
        }
        else
        {
            vtkStructuredGrid *sg = vtkStructuredGrid::SafeDownCast(in_ds);
            sg->GetDimensions(dims);
        }

        // If were here for cells instead of nodes, reduce dims by 1
        if (zones)
        {
            for (int i = 0; i < 3; i++)
            {
                if (dims[i] > 1)
                    dims[i]--;
            }
        }

        //
        // This nesting of loops looks bad but has plenty of
        // opportunities to terminate early.
        //
        for (int k = 0; k < dims[2] && allLogBndGhost; k++)
        {
            for (int j = 0; j < dims[1] && allLogBndGhost; j++)
            {
                for (int i = 0; i < dims[0] && allLogBndGhost; i++)
                {
                    if (i==0 || i==(dims[0]-1))
                    {
                        int idx = k*dims[1]*dims[0] + j*dims[0] + i;
                        if ((ghostVals[idx] & typesToRemove) == 0x00)
                            allLogBndGhost = false;
                    }
                    else if (j==0 || j==(dims[1]-1))
                    {
                        int idx = k*dims[1]*dims[0] + j*dims[0] + i;
                        if ((ghostVals[idx] & typesToRemove) == 0x00)
                            allLogBndGhost = false;
                    }
                    else if (k==0 || k==(dims[2]-1))
                    {
                        int idx = k*dims[1]*dims[0] + j*dims[0] + i;
                        if ((ghostVals[idx] & typesToRemove) == 0x00)
                            allLogBndGhost = false;
                    }
                }
            }
        }
    }
    else
    {
        allLogBndGhost = false;
    }
    if (_allLogBndGhost) *_allLogBndGhost = allLogBndGhost;
}

// ****************************************************************************
//  Method: avtGhostZoneFilter::ExecuteData
//
//  Purpose:
//      Sends the specified input and output through the GhostZone filter.
//
//  Arguments:
//      in_dr      The input data representation.
//
//  Returns:       The output data representation.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   May 1, 2001
//
//  Modifications:
//
//    Hank Childs, Tue Jun 26 18:57:57 PDT 2001
//    Handle case where input has no cells a little better.
//
//    Kathleen Bonnell, Wed Sep 19 12:55:57 PDT 2001
//    Added string arguments so that label will get passed to output. 
//
//    Hank Childs, Mon Apr 15 11:32:52 PDT 2002
//    Address memory leaks.
//
//    Hank Childs, Tue Sep 10 12:54:01 PDT 2002
//    Renamed to ExecuteData.  Added support for memory management.
//
//    Hank Childs, Sun Jun 27 09:45:20 PDT 2004
//    Add support for ghost nodes as well.
//
//    Hank Childs, Fri Aug 27 16:02:58 PDT 2004
//    Rename ghost data array.  Also remove SetGhostLevel call.
//
//    Hank Childs, Thu Mar  2 14:15:29 PST 2006
//    Change the way we access the vtkDataSetRemoveGhostCells filter, since
//    it can change type of output.
//
//    Hank Childs, Tue Dec 19 09:52:33 PST 2006
//    Allow rectilinear grids to pass through.
//
//    Hank Childs, Wed Dec 27 10:14:27 PST 2006
//    Allow curvilinear grids to pass through.
//
//    Hank Childs, Wed Jan  3 12:45:31 PST 2007
//    Look for ghost nodes for all mesh types.  Fix indexing bug.
//
//    Hank Childs, Sun Oct 28 11:17:32 PST 2007
//    Add support for ghostZoneTypesToRemove.
//
//    Gunther H. Weber, Thu May  8 19:36:53 PDT 2008
//    Bug fix: Consider ghostZoneTypesToRemove and ghostNodeTypesToRemove
//    when checking if data is all ghost.
//
//    Eric Brugger, Mon Jul 21 13:22:30 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
//    Eric Brugger, Fri Sep 26 08:41:30 PDT 2014
//    I modified the routine to return a NULL in the case where it previously
//    returned an avtDataRepresentation with a NULL vtkDataSet.
//
//    Mark C. Miller, Thu Sep 14 11:18:52 PDT 2017
//    Refactored code to check for all ghost nodes and zones and added checks
//    for all logical boundary ghost.
// ****************************************************************************

avtDataRepresentation *
avtGhostZoneFilter::ExecuteData(avtDataRepresentation *in_dr)
{
    //
    // Get the VTK data set and domain number.
    //
    vtkDataSet *in_ds = in_dr->GetDataVTK();
    int domain = in_dr->GetDomain();

    if (in_ds->GetNumberOfCells() == 0)
    {
        debug5 << "No Cells in input! domain:  " << domain << endl;
        return in_dr;
    }

    bool haveGhostZones = 
                    (in_ds->GetCellData()->GetArray("avtGhostZones") != NULL);
    bool haveGhostNodes = 
                    (in_ds->GetPointData()->GetArray("avtGhostNodes") != NULL);
    if (!haveGhostZones && !haveGhostNodes)
    {
        //
        //  No ghost cells, no need to use this filter.
        //
        debug5 << "No Ghost Zones present! domain:  " << domain << endl;
        return in_dr;
    }

    bool const zones = true;
    bool allGhost = true;
    bool allLogBndZonesGhost = false;
    ExamineGhostArray(in_ds, zones, haveGhostZones, ghostZoneTypesToRemove,
        &allGhost, &allLogBndZonesGhost);
    if (allGhost)
    {
        debug5 << "Domain " << domain << " contains only ghost zones.  Removing" << endl;
        return NULL;
    }

    allGhost = true;
    bool allLogBndNodesGhost = false;
    ExamineGhostArray(in_ds, !zones, haveGhostNodes, ghostNodeTypesToRemove,
        &allGhost, &allLogBndNodesGhost);
    if (allGhost)
    {
        debug5 << "Domain " << domain << " contains only ghost nodes.  Removing" << endl;
        return NULL;
    }
    bool allLogBndGhost = allLogBndZonesGhost || allLogBndNodesGhost;
    
#if 0
    if (in_ds->GetDataObjectType() == VTK_RECTILINEAR_GRID && 
        !ghostDataMustBeRemoved && !allLogBndGhost)
    {
        debug5 << "Allow rectilinear grid to travel through with ghost data;"
               << " depending on mapper to remove ghost data during render." 
               << endl;
        return in_dr;
    }

    if (in_ds->GetDataObjectType() == VTK_STRUCTURED_GRID && 
        !ghostDataMustBeRemoved && !allLogBndGhost)
    {
        debug5 << "Allow structured grid to travel through with ghost data;"
               << " depending on mapper to remove ghost data during render." 
               << endl;
        return in_dr;
    }
#endif

    debug5 << "Using vtkDataSetRemoveGhostCells" << endl;

    vtkDataSetRemoveGhostCells *filter = vtkDataSetRemoveGhostCells::New();
    filter->SetGhostNodeTypesToRemove(ghostNodeTypesToRemove);
    filter->SetGhostZoneTypesToRemove(ghostZoneTypesToRemove);
    filter->SetInputData(in_ds);

    //
    // Set up filter so that all cells with ghost level >=1
    // will be removed.  Currently our 'real' zones have
    // ghostlevel ==0, 'ghost' have ghostlevel ==1.
    //
    // Note: have to say "Update" before saying GetOutput, since output
    // may change during execution.
    //
    filter->Update();
    vtkDataSet *outDS = filter->GetOutput();

    if (outDS->GetNumberOfCells() == 0)
    {
        filter->Delete();
        return NULL;
    }

    avtDataRepresentation *out_dr = new avtDataRepresentation(outDS,
        in_dr->GetDomain(), in_dr->GetLabel());

    filter->Delete();

    return out_dr;
}


// ****************************************************************************
//  Method: avtGhostZoneFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Indicate that the zones are invalidated after this operation.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   May 1, 2001
//
//  Modifications:
//
//    Hank Childs, Mon Sep 30 09:55:26 PDT 2002
//    Tell the output that it does not contain any ghost zones.
//
//    Hank Childs, Sun Oct 28 11:17:32 PST 2007
//    Allow for the case where some ghost zones are not removed.
//
// ****************************************************************************

void
avtGhostZoneFilter::UpdateDataObjectInfo(void)
{
    GetOutput()->GetInfo().GetValidity().InvalidateZones();
    GetOutput()->GetInfo().GetValidity().InvalidateSpatialMetaData();
    if (ghostZoneTypesToRemove == 0xFF)
        GetOutput()->GetInfo().GetAttributes().
                                          SetContainsGhostZones(AVT_NO_GHOSTS);
}


// ****************************************************************************
//  Method:  avtGhostZoneFilter::FilterUnderstandsTransformedRectMesh
//
//  Purpose:
//    If this filter returns true, this means that it correctly deals
//    with rectilinear grids having an implied transform set in the
//    data attributes.  It can do this conditionally if desired.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    February 15, 2007
//
// ****************************************************************************

bool
avtGhostZoneFilter::FilterUnderstandsTransformedRectMesh()
{
    return true;
}


// ****************************************************************************
//  Method: avtGhostZoneFilter::SetGhostNodeTypesToRemove
//
//  Purpose:
//      Sets the field for which ghost node types to remove.
//
//  Programmer: Hank Childs
//  Creation:   August 3, 2007
//
// ****************************************************************************

void
avtGhostZoneFilter::SetGhostNodeTypesToRemove(unsigned char t)
{
    ghostNodeTypesToRemove = t;
}


// ****************************************************************************
//  Method: avtGhostZoneFilter::SetGhostZoneTypesToRemove
//
//  Purpose:
//      Sets the field for which ghost zone types to remove.
//
//  Programmer: Hank Childs
//  Creation:   October 28, 2007
//
// ****************************************************************************

void
avtGhostZoneFilter::SetGhostZoneTypesToRemove(unsigned char t)
{
    ghostZoneTypesToRemove = t;
}


