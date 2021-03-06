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
//                    avtTotalRevolvedVolumeQuery.C                          //
// ************************************************************************* //

#include <avtTotalRevolvedVolumeQuery.h>

#include <avtRevolvedVolume.h>
#include <avtSourceFromAVTDataset.h>
#include <NonQueryableInputException.h>


using     std::string;

// ****************************************************************************
//  Method: avtTotalRevolvedVolumeQuery constructor
//
//  Notes:  Taken mostly from Hank Childs' avtTotalRevolvedVolumeFilter, 
//          now deprecated.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 30, 2002 
//
//  Modifications:
//    Kathleen Bonnell, Fri Jul 11 16:06:59 PDT 2003
//    Set units_append.
//
// ****************************************************************************

avtTotalRevolvedVolumeQuery::avtTotalRevolvedVolumeQuery() : avtSummationQuery()
{
    string      varname = "revolved_volume";
    string      sum_type = "RevolvedVolume";    
    string      units_append = "^3";    

    volume      = new avtRevolvedVolume;
    volume->SetOutputVariableName(varname.c_str());

    SetVariableName(varname);
    SetSumType(sum_type);
    SetUnitsAppend(units_append);
    SumGhostValues(false);
}


// ****************************************************************************
//  Method: avtTotalRevolvedVolumeQuery destructor
//
//  Notes:  Taken mostly from Hank Childs' avtTotalRevolvedVolumeFilter, 
//          now deprecated.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 30, 2002 
//
//  Modifications:
//
// ****************************************************************************

avtTotalRevolvedVolumeQuery::~avtTotalRevolvedVolumeQuery()
{
    if (volume != NULL)
    {
        delete volume;
        volume = NULL;
    }
}


// ****************************************************************************
//  Method: avtTotalRevolvedVolumeQuery::ApplyFilters 
//
//  Notes:  Taken mostly from Hank Childs' avtTotalRevolvedVolumeFilter, 
//          now deprecated.
//
//  Purpose:
//    Apply any avt filters necessary for the completion of this query.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 30, 2002 
//
//  Modifications:
//    Kathleen Bonnell, Fri Nov 15 09:07:36 PST 2002   
//    Moved artificial pipeline creation from base class.
//
// ****************************************************************************

avtDataObject_p 
avtTotalRevolvedVolumeQuery::ApplyFilters(avtDataObject_p inData)
{
    avtContract_p contract = 
        inData->GetOriginatingSource()->GetGeneralContract();
    //
    // Create an artificial pipeline.
    //
    avtDataset_p ds;
    CopyTo(ds, inData);
    avtSourceFromAVTDataset termsrc(ds);
    avtDataObject_p dob = termsrc.GetOutput();

    volume->SetInput(dob);
    avtDataObject_p objOut = volume->GetOutput();
    objOut->Update(contract);
    return objOut;
}


// ****************************************************************************
//  Method: avtTotalRevolvedVolumeQuery::VerifyInput
//
//  Purpose:
//    Now that we have an input, we can determine what the units are 
//    and tell the base class.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   July 27, 2004 
//
//  Modifications:
//    Kathleen Bonnell, Fri Sep  3 09:03:24 PDT 2004
//    Added test for topological dimension, as that is no longer performed by
//    base class.  
//
// ****************************************************************************

void
avtTotalRevolvedVolumeQuery::VerifyInput(void)
{
    //
    // We want to do this in addition to what the base class does, so call the
    // base class' version of this method as well.
    //
    avtDataObjectQuery::VerifyInput();

    if (GetInput()->GetInfo().GetAttributes().GetTopologicalDimension() == 0)
    {
        EXCEPTION1(NonQueryableInputException,
            "Requires plot with topological dimension > 0.");
    }

    SetUnits(GetInput()->GetInfo().GetAttributes().GetXUnits());
}
