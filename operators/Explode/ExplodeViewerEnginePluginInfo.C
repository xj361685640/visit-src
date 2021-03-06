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
//  File: ExplodeViewerEnginePluginInfo.C
// ************************************************************************* //

#include <ExplodePluginInfo.h>
#include <ExplodeAttributes.h>

#include <avtPlotMetaData.h>

//
// Storage for static data elements.
//
ExplodeAttributes *ExplodeViewerEnginePluginInfo::clientAtts = NULL;
ExplodeAttributes *ExplodeViewerEnginePluginInfo::defaultAtts = NULL;

// ****************************************************************************
//  Method:  ExplodeViewerEnginePluginInfo::InitializeGlobalObjects
//
//  Purpose:
//    Initialize the operator atts.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
void
ExplodeViewerEnginePluginInfo::InitializeGlobalObjects()
{
    ExplodeViewerEnginePluginInfo::clientAtts  = new ExplodeAttributes;
    ExplodeViewerEnginePluginInfo::defaultAtts = new ExplodeAttributes;
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::GetClientAtts
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
ExplodeViewerEnginePluginInfo::GetClientAtts()
{
    return clientAtts;
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::GetDefaultAtts
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
ExplodeViewerEnginePluginInfo::GetDefaultAtts()
{
    return defaultAtts;
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::SetClientAtts
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
ExplodeViewerEnginePluginInfo::SetClientAtts(AttributeSubject *atts)
{
    *clientAtts = *(ExplodeAttributes *)atts;
    clientAtts->Notify();
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::GetClientAtts
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
ExplodeViewerEnginePluginInfo::GetClientAtts(AttributeSubject *atts)
{
    *(ExplodeAttributes *)atts = *clientAtts;
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::InitializeOperatorAtts
//
//  Purpose:
//    Initialize the operator attributes to the default attributes.
//
//  Arguments:
//    atts        The attribute subject to initialize.
//    plot        The viewer plot that owns the operator.
//    fromDefault True to initialize the attributes from the defaults. False
//                to initialize from the current attributes.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
//  Modifications:
//
//      Alister Maguire, Wed Nov  8 10:12:34 PST 2017
//      Added retrieval of boundary names. 
//
//      Alister Maguire, Wed Jan 17 15:28:46 PST 2018
//      Moved most of the method to PrivateSetOperatorAtts(). 
//
// ****************************************************************************

void
ExplodeViewerEnginePluginInfo::InitializeOperatorAtts(AttributeSubject *atts,
                                              const avtPlotMetaData &plot,
                                              const bool fromDefault)
{
    if (fromDefault)
        *(ExplodeAttributes*)atts = *defaultAtts;
    else
        *(ExplodeAttributes*)atts = *clientAtts;

    PrivateSetOperatorAtts(atts, plot);
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::UpdateOperatorAtts
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
//  Modifications:
//      Alister Maguire, Wed Jan 17 15:28:46 PST 2018
//      Added a call to PrivateSetOperatorAtts(). 
//
// ****************************************************************************

void
ExplodeViewerEnginePluginInfo::UpdateOperatorAtts(AttributeSubject *atts, const avtPlotMetaData &plot)
{
    *(ExplodeAttributes*)atts = *defaultAtts;

    PrivateSetOperatorAtts(atts, plot);
}

// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::GetMenuName
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
ExplodeViewerEnginePluginInfo::GetMenuName() const
{
    return "Explode";
}


// ****************************************************************************
//  Method: ExplodeViewerEnginePluginInfo::PrivateSetOperatorAtts
//
//  Purpose:
//      Retrieve the boundary (material) names and set them within the i
//      operator attributes. 
//
//  Programmer: Alister Maguire
//  Creation:   Wed Jan 17 15:28:46 PST 2018
//
// ****************************************************************************

void
ExplodeViewerEnginePluginInfo::PrivateSetOperatorAtts(AttributeSubject *atts, 
    const avtPlotMetaData &plot)
{
    ExplodeAttributes *explodeAtts = (ExplodeAttributes *)atts;

    const avtMaterialMetaData *mat = NULL;
    const avtDatabaseMetaData *md  = plot.GetMetaData();
    if (md == NULL)
    {
        return;
    }

    stringVector materialNames;
    int numMaterials = md->GetNumMaterials();  

    for (int i = 0; i < numMaterials; ++i)
    {
        mat = md->GetMaterial(i);
        if (mat != NULL)
        {
            for (stringVector::const_iterator pos = mat->materialNames.begin();
                 pos != mat->materialNames.end(); ++pos)
            {
                if ( !(*pos).empty() )
                {
                    materialNames.push_back(*pos); 
                }
            }
        }
        mat = NULL;
    }

    explodeAtts->SetBoundaryNames(materialNames);
    defaultAtts->SetBoundaryNames(materialNames);
}
