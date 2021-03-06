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
//  File: MultiCurveViewerEnginePluginInfo.C
// ************************************************************************* //

#include <MultiCurvePluginInfo.h>
#include <avtMultiCurvePlot.h>
#include <MultiCurveAttributes.h>

//
// Storage for static data elements.
//
MultiCurveAttributes *MultiCurveViewerEnginePluginInfo::clientAtts = NULL;
MultiCurveAttributes *MultiCurveViewerEnginePluginInfo::defaultAtts = NULL;

// ****************************************************************************
// Method:  MultiCurveViewerEnginePluginInfo::InitializeGlobalObjects
//
// Purpose:
//   Initialize the plot atts.
//
// Programmer: Eric Brugger
// Creation:   December 9, 2008
//
// Modifications:
//
// ****************************************************************************
void
MultiCurveViewerEnginePluginInfo::InitializeGlobalObjects()
{
    MultiCurveViewerEnginePluginInfo::clientAtts  = new MultiCurveAttributes;
    MultiCurveViewerEnginePluginInfo::defaultAtts = new MultiCurveAttributes;

    InitializeDefaultPalette(clientAtts);
    InitializeDefaultPalette(defaultAtts);
}


// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::GetClientAtts
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
MultiCurveViewerEnginePluginInfo::GetClientAtts()
{
    return clientAtts;
}

// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::GetDefaultAtts
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
MultiCurveViewerEnginePluginInfo::GetDefaultAtts()
{
    return defaultAtts;
}

// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::SetClientAtts
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
MultiCurveViewerEnginePluginInfo::SetClientAtts(AttributeSubject *atts)
{
    *clientAtts = *(MultiCurveAttributes *)atts;
    clientAtts->Notify();
}

// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::GetClientAtts
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
MultiCurveViewerEnginePluginInfo::GetClientAtts(AttributeSubject *atts)
{
    *(MultiCurveAttributes *)atts = *clientAtts;
}

// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::AllocAvtPlot
//
//  Purpose:
//    Return a pointer to a newly allocated avt plot.
//
//  Returns:    A pointer to the newly allocated avt plot.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

avtPlot *
MultiCurveViewerEnginePluginInfo::AllocAvtPlot()
{
    return new avtMultiCurvePlot;
}

// ****************************************************************************
// Method: MultiCurveViewerEnginePluginInfo::InitializePlotAtts
//
// Purpose:
//   Initialize the plot attributes to the default attributes.
//
// Arguments:
//   atts       The attribute subject to initialize.
//   plot       The viewer plot whose attributes are getting initialized.
//
// Programmer: Eric Brugger
// Creation:   December 9, 2008
//
// Modifications:
//
// ****************************************************************************

void
MultiCurveViewerEnginePluginInfo::InitializePlotAtts(AttributeSubject *atts,
    const avtPlotMetaData &)
{
    MultiCurveAttributes *multiCurve = (MultiCurveAttributes *)atts;
    *multiCurve = *defaultAtts;

    // Set the defaultPalette for the plot.
    InitializeDefaultPalette(multiCurve);
}

// ****************************************************************************
//  Method: MultiCurveViewerEnginePluginInfo::GetMenuName
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
MultiCurveViewerEnginePluginInfo::GetMenuName() const
{
    return "MultiCurve";
}

// ****************************************************************************
// Method: MultiCurveViewerEnginePluginInfo::InitializeDefaultPalette
//
// Purpose:
//   Initializes the default palette in the multiCurve attributes using the
//   default discrete color table.
//
// Arguments:
//   multiCurve The MultiCurveAttributes to initialize.
//
// Programmer: Eric Brugger
// Creation:   December 9, 2008
//
// Modifications:
//   Eric Brugger, Tue Jan 20 12:19:28 PST 2009
//   I added code to enlarge the multi color field to 16 entries so that
//   clients may set them.
//
// ****************************************************************************
#include <avtColorTables.h>
#include <ColorTableAttributes.h>
void
MultiCurveViewerEnginePluginInfo::InitializeDefaultPalette(
    MultiCurveAttributes *multiCurve)
{
    // Copy over the multiCurve's defaultPalette with the default discrete
    // color table from avtColorTable.
    if (multiCurve->GetColorType() != MultiCurveAttributes::ColorByMultipleColors ||
        multiCurve->GetDefaultPalette().GetNumControlPoints() < 1)
    {
        avtColorTables *ct = avtColorTables::Instance();
        ColorTableAttributes *ctAtts = ct->GetColorTables();
        int i = ctAtts->GetColorTableIndex(ct->GetDefaultDiscreteColorTable());
        if(i != -1)
        {
            multiCurve->SetDefaultPalette(ctAtts->operator[](i));
        }
    }
    multiCurve->EnlargeMultiColor(16);
}

