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
//                           avtUserDefinedMapper.C                          //
// ************************************************************************* //

#include <avtUserDefinedMapper.h>

#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>

#include <ColorAttribute.h>

#include <avtCallback.h>

#include <VisItException.h>


// ****************************************************************************
//  Method: avtUserDefinedMapper constructor
//
//  Arguments:
//      r       The custom-defined renderer.
//
//  Programmer: Hank Childs
//  Creation:   March 26, 2001
//
// ****************************************************************************

avtUserDefinedMapper::avtUserDefinedMapper(avtCustomRenderer_p r)
    : avtMapper()
{
    renderer = r;
}


// ****************************************************************************
//  Method: avtUserDefinedMapper destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtUserDefinedMapper::~avtUserDefinedMapper()
{
    ;
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::GetDataRange
//
//  Arguments:
//    rmin      The minimum in the range.
//    rmax      The maximum in the range.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   October 4, 2001 
//
//  Modifications:
//    Kathleen Bonnell, Tue May  9 15:45:04 PDT 2006
//    Set rmax when mappers==NULL (was setting rmin twice).
//
// ****************************************************************************

bool
avtUserDefinedMapper::GetDataRange(double &rmin, double &rmax)
{
    if (mappers == NULL)
    {
        //
        // We have been asked for the range before the input has been set.
        //
        rmin = 0.;
        rmax = 1.;
        return false;
    }

    avtMapper::GetRange(rmin, rmax);
    return true;
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::GetCurrentDataRange
//
//  Arguments:
//    rmin      The minimum in the range.
//    rmax      The maximum in the range.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   October 4, 2001 
//
//  Modifications:
//    Kathleen Bonnell, Tue May  9 15:45:04 PDT 2006
//    Set rmax when mappers==NULL (was setting rmin twice).
//
// ****************************************************************************

bool
avtUserDefinedMapper::GetCurrentDataRange(double &rmin, double &rmax)
{
    if (mappers == NULL)
    {
        //
        // We have been asked for the range before the input has been set.
        //
        rmin = 0.;
        rmax = 1.;
        return false;
    }

    avtMapper::GetCurrentRange(rmin, rmax);
    return true;
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::CustomizeMappers
//
//  Purpose:
//      A hook from the base class that allows the user defined mapper to
//      determine its extents and set them.
//
//  Programmer: Hank Childs
//  Creation:   November 19, 2001
//
//  Modifications:
//    Kathleen Bonnell, Wed Mar 19 14:26:05 PST 2003
//    Removed test for min == max, no longer an issue with vtkLookupTables or 
//    vtkMappers.
//
//    Hank Childs, Thu Sep 30 00:45:38 PDT 2010
//    Also do bounding boxes.
//
//    Hank Childs, Thu Feb 23 15:17:49 PST 2012
//    Properly initialize bounding boxes.
//
// ****************************************************************************

void
avtUserDefinedMapper::CustomizeMappers(void)
{
    if (renderer->OperatesOnScalars())
    {
        double mmin = 0.;
        double mmax = 0.;
        GetRange(mmin, mmax);
    
        //
        // Now tell the renderer what its variable range should be.
        //
        renderer->SetRange(mmin, mmax);
    }
    if (renderer->NeedsBoundingBox())
    {
        double bbox[6] = { 0, 0, 0, 0, 0, 0 };
        avtDataAttributes &atts = GetInput()->GetInfo().GetAttributes();
        atts.GetSpatialExtents(bbox);
        renderer->SetBoundingBox(bbox);
    }
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::CreateMapper
//
//  Purpose:
//      Creates a mapper that will act as a bridge from vtk to the user's
//      custom defined renderer.
//
//  Returns:     The mapper.
//
//  Programmer:  Hank Childs
//  Creation:    March 26, 2001
//
// ****************************************************************************

vtkDataSetMapper *
avtUserDefinedMapper::CreateMapper(void)
{
    vtkUserDefinedMapperBridge *rv = vtkUserDefinedMapperBridge::New();
    rv->SetRenderer(renderer);

    return rv;
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::GlobalLightingOn
//
//  Purpose:
//      Tells the renderer that global lighting has been turned on. 
//      Allows the renderer to update lighting coefficients if necessary. 
//
//  Programmer:  Kathleen Bonnell 
//  Creation:    August 13, 2002 
//
// ****************************************************************************

void 
avtUserDefinedMapper::GlobalLightingOn()
{
    renderer->GlobalLightingOn();
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::GlobalLightingOff
//
//  Purpose:
//      Tells the renderer that global lighting has been turned off. 
//      Allows the renderer to update lighting coefficients if necessary. 
//
//  Programmer:  Kathleen Bonnell 
//  Creation:    August 13, 2002 
//
// ****************************************************************************

void 
avtUserDefinedMapper::GlobalLightingOff()
{
    renderer->GlobalLightingOff();
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::GlobalSetAmbientCoefficient
//
//  Purpose:
//      Tells the renderer that global ambient lighting coefficient has
//      been set.
//
//  Programmer:  Kathleen Bonnell 
//  Creation:    August 13, 2002 
//
// ****************************************************************************

void 
avtUserDefinedMapper::GlobalSetAmbientCoefficient(const double amb)
{
    renderer->GlobalSetAmbientCoefficient(amb);
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::SetSpecularProperties
//
//  Purpose:
//    Sends the specular properties to the renderer. 
//
//  Arguments:
//    flag  :  true to enable specular, false otherwise
//    coeff :  the new specular coefficient
//    power :  the new specular power
//    color :  the new specular color
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 2, 2004 
//
//  Modifications:
//
// ****************************************************************************

void
avtUserDefinedMapper::SetSpecularProperties(bool flag, double coeff, 
                                           double power,
                                           const ColorAttribute &color)
{
    renderer->SetSpecularProperties(flag, coeff, power, color);
}


// ****************************************************************************
//  Method: avtUserDefinedMapper::SetSurfaceRepresentation
//
//  Purpose:
//    Sends the surface representation to the renderer. 
//
//  Arguments:
//    rep  :  the new representation 
//
//  Programmer: Kathleen Bonnell 
//  Creation:   September 2, 2004 
//
//  Modifications:
//
// ****************************************************************************

void
avtUserDefinedMapper::SetSurfaceRepresentation(int rep)
{
    renderer->SetSurfaceRepresentation(rep);
}

// ****************************************************************************
// Method: avtUserDefinedMapper::SetAlternateDisplay
//
// Purpose: 
//   Tells the plot to use its own rendering method instead of putting the
//   plot into the vis window.
//
// Arguments:
//   dpy : Handle to the plot's display.
//
// Programmer: Brad Whitlock
// Creation:   Wed Feb 7 16:20:43 PST 2007
//
// Modifications:
//   
// ****************************************************************************

void
avtUserDefinedMapper::SetAlternateDisplay(void *dpy)
{
    renderer->SetAlternateDisplay(dpy);
}

// ****************************************************************************
// Method: avtUserDefinedMapper::ReducedDetailModeOn
//
// Purpose: 
//   Tells the renderer to enter reduced detail mode.
//
// Programmer: Brad Whitlock
// Creation:   Wed Aug 22 11:37:51 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

void
avtUserDefinedMapper::ReducedDetailModeOn()
{
    renderer->ReducedDetailModeOn();
}

// ****************************************************************************
// Method: avtUserDefinedMapper::ReducedDetailModeOff
//
// Purpose: 
//   Tells the renderer to exit reduced detail mode.
//
// Programmer: Brad Whitlock
// Creation:   Wed Aug 22 11:37:51 PDT 2007
//
// Modifications:
//   
// ****************************************************************************

bool
avtUserDefinedMapper::ReducedDetailModeOff()
{
    return renderer->ReducedDetailModeOff();
}

// ****************************************************************************
//  Method: vtkUserDefinedMapperBridge::New
//
//  Purpose:
//      Meets the VTK convention of instantiating objects through a static
//      function, since the constructors and destructors are protected for
//      reference counting reasons.
//
//  Returns:     A new instance of vtkUserDefinedMapperBridge
//
//  Programmer:  Hank Childs
//  Creation:    March 26, 2001
//
// ****************************************************************************

vtkUserDefinedMapperBridge *
vtkUserDefinedMapperBridge::New(void)
{
    //
    // First try to create the object from the vtkObjectFactory
    //
    vtkObject *ret = NULL;
    ret = vtkObjectFactory::CreateInstance("vtkUserDefinedMapperBridge");
    if (ret == NULL)
    {
        ret = new vtkUserDefinedMapperBridge;
    }

    return (vtkUserDefinedMapperBridge *) ret;
}


// ****************************************************************************
//  Method: vtkUserDefinedMapperBridge constructor
//
//  Programmer: Hank Childs
//  Creation:   March 26, 2001
//
// ****************************************************************************

vtkUserDefinedMapperBridge::vtkUserDefinedMapperBridge() : vtkDataSetMapper()
{
    ren = NULL;
}

// ****************************************************************************
//  Method: vtkUserDefinedMapperBridge destructor
//
//  Programmer: Brad Whitlock
//  Creation:   Thu Jan 10 14:21:45 PST 2013
//
// ****************************************************************************

vtkUserDefinedMapperBridge::~vtkUserDefinedMapperBridge()
{
}

// ****************************************************************************
//  Method: vtkUserDefinedMapperBridge::SetRenderer
//
//  Purpose:
//      Registers the renderer that the bridge should call asked to map data.
//
//  Arguments:
//      r       The renderer.
//
//  Programmer: Hank Childs
//  Creation:   March 26, 2001
//
// ****************************************************************************

void 
vtkUserDefinedMapperBridge::SetRenderer(avtCustomRenderer_p r)
{
    ren = r;
}


// ****************************************************************************
//  Method: vtkUserDefinedMapperBridge::Render
//
//  Purpose:
//      Called when a mapper should makes its rendering calls.  This re-routes
//      the call to the avtCustomRenderer and sets some information with the
//      renderer.
//
//  Arguments:
//      r          The vtkRenderer.
//      <unnamed>  The actor associated with the mapper.
//
//  Programmer: Hank Childs
//  Creation:   March 26, 2001
//
//  Modifications:
//
//    Hank Childs, Wed Mar  1 09:59:45 PST 2006
//    Added some exception handling.  Not a good idea to let an exception
//    be thrown up through VTK's GL code.
//
//    Carson Brownlee, Fri Jul 27 13:57:44 PDT 2012
//    Pass along vtkActor.
//
// ****************************************************************************

void 
vtkUserDefinedMapperBridge::Render(vtkRenderer *r, vtkActor *a)
{
    //
    // Retrieve the view information and set it with the avt renderer.
    //
    avtViewInfo view;
    vtkCamera *cam = r->GetActiveCamera();
    view.SetViewFromCamera(cam);
    ren->SetView(view);

    //
    // Ask the avt renderer to draw this dataset.
    //
    vtkDataSet *input = this->GetInput();
    ren->SetVTKRenderer(r);
    ren->SetVTKActor(a);
    TRY
    {
        ren->Execute(input);
    }
    CATCH2(VisItException, ve)
    {
        //
        // We do not want to throw an exception here.  This call has a bunch
        // of VTK/GL code above it and throwing an exception will leave it
        // in a very bad state.  So, log the exception in avtCallback and let
        // the VisWindow look for it after the render is finished.
        //
        avtCallback::SetRenderingException(ve.Message());
    }
    ENDTRY
}



