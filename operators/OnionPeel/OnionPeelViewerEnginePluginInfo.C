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
//  File: OnionPeelViewerEnginePluginInfo.C
// ************************************************************************* //

#include <OnionPeelPluginInfo.h>
#include <OnionPeelAttributes.h>

//
// Storage for static data elements.
//
OnionPeelAttributes *OnionPeelViewerEnginePluginInfo::clientAtts = NULL;
OnionPeelAttributes *OnionPeelViewerEnginePluginInfo::defaultAtts = NULL;

// ****************************************************************************
//  Method:  OnionPeelViewerEnginePluginInfo::InitializeGlobalObjects
//
//  Purpose:
//    Initialize the operator atts.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
void
OnionPeelViewerEnginePluginInfo::InitializeGlobalObjects()
{
    OnionPeelViewerEnginePluginInfo::clientAtts  = new OnionPeelAttributes;
    OnionPeelViewerEnginePluginInfo::defaultAtts = new OnionPeelAttributes;
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::GetClientAtts
//
//  Purpose:
//    Return a pointer to the viewer client attributes.
//
//  Returns:    A pointer to the viewer client attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

AttributeSubject *
OnionPeelViewerEnginePluginInfo::GetClientAtts()
{
    return clientAtts;
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::GetDefaultAtts
//
//  Purpose:
//    Return a pointer to the viewer default attributes.
//
//  Returns:    A pointer to the viewer default attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

AttributeSubject *
OnionPeelViewerEnginePluginInfo::GetDefaultAtts()
{
    return defaultAtts;
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::SetClientAtts
//
//  Purpose:
//    Set the viewer client attributes.
//
//  Arguments:
//    atts      A pointer to the new client attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
OnionPeelViewerEnginePluginInfo::SetClientAtts(AttributeSubject *atts)
{
    *clientAtts = *(OnionPeelAttributes *)atts;
    clientAtts->Notify();
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::GetClientAtts
//
//  Purpose:
//    Get the viewer client attributes.
//
//  Arguments:
//    atts      A pointer to return the client default attributes in.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
OnionPeelViewerEnginePluginInfo::GetClientAtts(AttributeSubject *atts)
{
    *(OnionPeelAttributes *)atts = *clientAtts;
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::InitializeOperatorAtts
//
//  Purpose:
//    Initialize the operator attributes to the default attributes.
//
//  Arguments:
//    atts      The attribute subject to initialize.
//
//  Programmer: kbonnell -- generated by xml2info
//  Creation:   Tue Sep 9 16:04:02 PST 2003
//
//  Modifications:
//    Added code to set the category name and subset name from the plot's
//    SILRestriction. 
//
//    Kathleen Bonnell, Thu Jan 26 07:33:29 PST 2006 
//    Add silTopSet to argslist for GetCollectionIndex. 
//
//    Brad Whitlock, Fri Feb 15 15:32:57 PST 2008
//    Delete silAtts.
//
//    Hank Childs, Tue Nov 18 09:39:37 PST 2008
//    Account for new optimization in CompactSILAttributes.
//
//    Hank Childs, Mon Dec 14 16:43:16 PST 2009
//    Update for new SIL interface.
//
// ****************************************************************************
#include <avtSIL.h>
#include <avtSILRestriction.h>
#include <CompactSILRestrictionAttributes.h>
#include <avtPlotMetaData.h>
void
OnionPeelViewerEnginePluginInfo::InitializeOperatorAtts(AttributeSubject *atts,
                                              const avtPlotMetaData &plot,
                                              const bool fromDefault)
{
    if (fromDefault)
        *(OnionPeelAttributes*)atts = *defaultAtts;
    else
        *(OnionPeelAttributes*)atts = *clientAtts;

    OnionPeelAttributes *opAtts = (OnionPeelAttributes*)atts;


    std::string categoryName = opAtts->GetCategoryName();
    std::string subsetName = opAtts->GetSubsetName();
    std::string defaultName = "Whole";
    std::string firstCategoryName = defaultName;
    std::string firstSubsetName = defaultName;

    bool categoryNameValid = false;
    bool subsetNameValid = false;
    avtSILRestriction_p restriction = plot.GetSILRestriction();
    int silTopSet = restriction->GetTopSet();

    // 
    // Determine the first valid category name, and determine if
    // currently set category name is valid. 
    // 
    avtSILSet_p current = restriction->GetSILSet(silTopSet);
    const std::vector<int> &mapsOut = current->GetMapsOut();
    for (size_t j = 0; j < mapsOut.size() && !categoryNameValid; ++j)
    {
        int cIndex = mapsOut[j];
        avtSILCollection_p collection =restriction->GetSILCollection(cIndex);
        if ((collection->GetRole() == SIL_DOMAIN) ||
            (collection->GetRole() == SIL_BLOCK)) 
        {
            if (collection->GetCategory() == categoryName)
            {
                categoryNameValid = true;
            }
            else if (firstCategoryName == defaultName)
            {
                firstCategoryName = collection->GetCategory();
            }
            CompactSILRestrictionAttributes *silAtts = 
                restriction->MakeCompactAttributes();
            const unsignedCharVector &useSet =  silAtts->GetUseSet();
            //
            // Find the first valid subset name, and also determine if
            // the currently set subset name is valid.
            //
            int colIndex = restriction->GetCollectionIndex(
                           collection->GetCategory(), silTopSet);
            avtSILCollection_p collection =
                           restriction->GetSILCollection(colIndex); 
            if (*collection != NULL)
            {
                int nSets = collection->GetNumberOfSubsets();
                for (int i = 0; i < nSets && !subsetNameValid; ++i)
                {
                    bool isOn = false;
                    if (silAtts->GetTopSetIsAllOn())
                        isOn = true;
                    else
                    {
                        int idx = collection->GetSubset(i);
                        if(idx >= 0 && idx < (int)useSet.size())
                            isOn = (useSet[idx] != 0);
                    }

                    if (isOn)
                    {
                        avtSILSet_p set = restriction->GetSILSet(collection->GetSubset(i));
                        if (set->GetName() == subsetName)
                        {
                            subsetNameValid = true;
                        }
                        else if (firstSubsetName == defaultName)
                        {
                            firstSubsetName = set->GetName();
                        }
                    }
                }
            }

            delete silAtts;
        } 
    }

    // 
    // Use the currently set category and subsets name only if they
    // have they are valid.
    // 
    if (subsetNameValid)
    {
        opAtts->SetSubsetName(subsetName);
        defaultAtts->SetSubsetName(subsetName);
    }
    else 
    {
        opAtts->SetSubsetName(firstSubsetName);
        defaultAtts->SetSubsetName(firstSubsetName);
    }
    if (categoryNameValid)
    {
       opAtts->SetCategoryName(categoryName);
       defaultAtts->SetCategoryName(categoryName);
    }
    else 
    {
        opAtts->SetCategoryName(firstCategoryName);
        defaultAtts->SetCategoryName(firstCategoryName);
    }

    UpdateOperatorAtts(opAtts, plot);
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::UpdateOperatorAtts
//
//  Purpose:
//    Update the operator attributes when using operator expressions.
//
//  Arguments:
//    atts        The attribute subject to update.
//    plot        The viewer plot that owns the operator.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

void
OnionPeelViewerEnginePluginInfo::UpdateOperatorAtts(AttributeSubject *atts, const avtPlotMetaData &plot)
{
}

// ****************************************************************************
//  Method: OnionPeelViewerEnginePluginInfo::GetMenuName
//
//  Purpose:
//    Return a pointer to the name to use in the viewer menus.
//
//  Returns:    A pointer to the name to use in the viewer menus.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
OnionPeelViewerEnginePluginInfo::GetMenuName() const
{
    return "Onion Peel";
}

