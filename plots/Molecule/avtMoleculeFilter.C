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
//                           avtMoleculeFilter.C                             //
// ************************************************************************* //

#include <avtMoleculeFilter.h>
#include <vtkDataArray.h>
#include <vtkDataSet.h>
#include <vtkFloatArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <DebugStream.h>
#include <AtomicProperties.h>

#include <climits>

#include <set>
#include <string>
#include <vector>

// ****************************************************************************
//  Method: avtMoleculeFilter constructor
//
//  Arguments:
//
//  Programmer: Jeremy Meredith
//  Creation:   February 14, 2006
//
//  Modifications:
//
// ****************************************************************************

avtMoleculeFilter::avtMoleculeFilter()
{
}


// ****************************************************************************
//  Method: avtMoleculeFilter destructor
//
//  Programmer: Jeremy Meredith
//  Creation:   February 14, 2006
//
//  Modifications:
//
// ****************************************************************************

avtMoleculeFilter::~avtMoleculeFilter()
{
}


// ****************************************************************************
//  Method: avtMoleculeFilter::ExecuteData
//
//  Purpose:
//      If we've got an integral data type with less than 1000 entries, then
//      we want to treat it like an enumerated type.  We'll figure out which
//      values are used, then treat them like labels (cf. subset labels).
//
//  Arguments:
//      inDS      The input dataset.
//      <unused>  The domain number.
//      <unused>  The label.
//
//  Returns:      The output dataset.
//
//  Programmer:   Jeremy Meredith
//  Creation:     March 23, 2006
//
//  Modifications:
//    Jeremy Meredith, Mon Aug 28 18:18:17 EDT 2006
//    Bonds are now line segments cells, and atoms are both points and
//    vertex cells.  This means we cannot look at cell data when looking
//    for atom arrays.  Also, account for model number directory prefix.
//
//    Brad Whitlock, Fri Apr 20 16:17:08 PDT 2012
//    Support non-float arrays.
//
//    Eric Brugger, Tue Aug 19 11:00:33 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

avtDataRepresentation *
avtMoleculeFilter::ExecuteData(avtDataRepresentation *in_dr)
{
    //
    // Get the VTK data set.
    //
    vtkDataSet *in_ds = in_dr->GetDataVTK();

    vtkIdType natoms = in_ds->GetNumberOfPoints();
    vtkDataArray *primary = in_ds->GetPointData()->GetScalars();
    if (!primary)
    {
        debug4<<"avtMoleculeFilter::ExecuteData: primary was NULL\n";
        return  in_dr;
    }

    if (natoms>0 && primary)
    {
        name = primary->GetName();

        bool integral_type = true;
        int minval =  INT_MAX;
        int maxval = -INT_MAX;
        vtkIdType i;
        for (i=0; i<natoms; i++)
        {
            double scalar = primary->GetTuple1(i);
            int iscalar = int(scalar);
            if (scalar != double(iscalar))
            {
                integral_type = false;
                break;
            }
            if (iscalar < minval)
                minval = iscalar;
            if (iscalar > maxval)
                maxval = iscalar;
        }

        debug4 << "avtMoleculeFilter::ExecuteData: integral_type="
               << integral_type << endl;
        debug4 << "avtMoleculeFilter::ExecuteData: min=" << minval << endl;
        debug4 << "avtMoleculeFilter::ExecuteData: max=" << maxval << endl;

        if (integral_type && minval >= 0 && maxval < 10000)
        {
            bool *hasval = new bool[maxval+1];
            for (i=0; i<=maxval; i++)
                hasval[i] = false;

            for (i=0; i<natoms; i++)
            {
                int scalar = static_cast<int>(primary->GetTuple1(i));
                hasval[scalar] = true;
            }

            for (i=0; i<=maxval; i++)
            {
                if (hasval[i])
                {
                    used_values.insert(i);
                }
            }

            delete [] hasval;
        }
    }
    return in_dr;
}


// ****************************************************************************
//  Method: avtMoleculeFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Tell the thing to keep the node and zone number arrays.
//
//  Programmer: Jeremy Meredith
//  Creation:   February 14, 2006
//
//  Modifications:
//
// ****************************************************************************

void
avtMoleculeFilter::UpdateDataObjectInfo(void)
{
    // We're pretending it's a point plot
    GetOutput()->GetInfo().GetAttributes().SetTopologicalDimension(0);

    // Don't bother with the normals.
    GetOutput()->GetInfo().GetValidity().SetNormalsAreInappropriate(true);

    // Even though we requested original cell numbers, it will
    // rudely strip them off unless we tell it we were serious.
    GetOutput()->GetInfo().GetAttributes().SetKeepNodeZoneArrays(true);
}


// ****************************************************************************
//  Method: avtMoleculeFilter::ReleaseData
//
//  Purpose:
//      Releases all problem size data associated with this filter.
//
//  Programmer: Jeremy Meredith
//  Creation:   February 14, 2006
//
//  Modifications:
//
// ****************************************************************************

void
avtMoleculeFilter::ReleaseData(void)
{
    avtDataTreeIterator::ReleaseData();
}


// ****************************************************************************
//  Method: avtMoleculeFilter::ModifyContract
//
//  Purpose:  
//    Do nothing; the plot already requests original zones. 
// 
//  Programmer: Jeremy Meredith
//  Creation:   February 14, 2006
//
//  Modifications:
//
// ****************************************************************************

avtContract_p
avtMoleculeFilter::ModifyContract(avtContract_p spec)
{
    avtContract_p rv = spec;

    return rv;
}


// ****************************************************************************
//  Method:  avtMoleculeFilter::PreExecute
//
//  Purpose:
//    Clear out the values we've accumulated.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    March 23, 2006
//
//  Modifications:
//    Jeremy Meredith, Thu Feb 15 13:39:40 EST 2007
//    Call inherited PreExecute before everything else.
//
// ****************************************************************************
void
avtMoleculeFilter::PreExecute()
{
    avtDataTreeIterator::PreExecute();

    used_values.clear();
    name = "";
}

// ****************************************************************************
//  Method:  avtMoleculeFilter::PostExecute
//
//  Purpose:
//    Now that we know which integral values exist in this data base,
//    apply names to them and make these be the date attribute labels.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    March 23, 2006
//
//  Modifications:
//    Jeremy Meredith, Mon Aug 28 18:29:47 EDT 2006
//    Account for model number directory prefix.
//
//    Jeremy Meredith, Thu Mar 12 17:32:34 EDT 2009
//    Allow any variable starting with "element" to be treated as
//    an atomic number -- this makes creating new element expressions
//    to override ones in the file possible.
//
//    Jeremy Meredith, Wed May 20 11:49:18 EDT 2009
//    Added a fake "0" element which means "unknown", and hydrogen
//    now starts at 1, so we don't need to correct for 1-origin indices.
//
//    Jeremy Meredith, Tue Aug 25 14:17:15 EDT 2009
//    A strange bug occurs when switching the radius variable to an expression;
//    the plot legend picks up the extents of the radius variable instead of
//    the old primary variable, because it thinks the primary variable has
//    changed.  This is a bug at a different level, but the diagnosis of the
//    fuller problem is complex, and has not yet been replicated in other
//    plots; therefore, I simply set the primary variable again here, just
//    to make sure it's correct, which effectively works around the problem.
//
// ****************************************************************************
void
avtMoleculeFilter::PostExecute()
{
    std::vector<std::string> labels;

    if (name == "element" ||
        (name.length()>7 && name.substr(0,7) == "element") ||
        (name.length()>8 && name.substr(name.length()-8)=="/element"))
    {
        for (std::set<int>::iterator it = used_values.begin();
             it != used_values.end();
             it++)
        {
            labels.push_back(element_names[*it]);
        }
    }
    else if (name == "restype" || (name.length()>8 && name.substr(name.length()-8)=="/restype"))
    {
        // Poke on/off state, and the short and long names of all of 
        // the known residue names into the labels. We send them all 
        // with an on/off flag so we can let the viewer know about 
        // new residues that we've learned about.
        for(int i = 0; i < NumberOfKnownResidues(); ++i)
        {
            const char *rn = NumberToResiduename(i);
            if(rn == 0)
            {
                break;
            }

            if(used_values.find(i) == used_values.end())
                labels.push_back("off");
            else
                labels.push_back("on");
            labels.push_back(rn);
            labels.push_back(ResiduenameToLongName(rn));
        }
    }
    else
    {
        char nm[256];
        for (std::set<int>::iterator it = used_values.begin();
             it != used_values.end();
             it++)
        {
            sprintf(nm, "%d", *it);
            labels.push_back(nm);
        }
    }

    GetOutput()->GetInfo().GetAttributes().SetLabels(labels);
    OutputSetActiveVariable(pipelineVariable);
}


// ****************************************************************************
//  Method:  avtMoleculeFilter::SetAtts
//
//  Purpose:
//    Get a copy of the Plot's attributes.
//
//  Arguments:
//    a          the new MoleculeAttributes
//
//  Programmer:  Jeremy Meredith
//  Creation:    March 23, 2006
//
// ****************************************************************************
void
avtMoleculeFilter::SetAtts(const MoleculeAttributes *a)
{
    atts = *a;
}
