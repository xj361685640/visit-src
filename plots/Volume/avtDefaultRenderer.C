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
//                           avtDefaultRenderer.C                            //
// ************************************************************************* //

#include "avtDefaultRenderer.h"

#include <vtkRectilinearGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkRenderer.h>

#include <VolumeAttributes.h>
#include <avtCallback.h>
#include <DebugStream.h>

#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkImageData.h>
#include <vtkPiecewiseFunction.h>

#ifndef NO_DATA_VALUE
#define NO_DATA_VALUE -1e+37
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

// ****************************************************************************
//  Method: avtDefaultRenderer::avtDefaultRenderer
//
//  Purpose:
//    Initialize the memebers associated with the default renderer. 
//
//  Programmer:  Alister Maguire
//  Creation:    April 3, 2017
//
//  Modifications:
//
// ****************************************************************************

avtDefaultRenderer::avtDefaultRenderer()
{
    VTKRen        = NULL;
    curVolume     = NULL;
    imageToRender = NULL;
    resetColorMap = false;
    volumeProp    = vtkSmartPointer<vtkVolumeProperty>::New();
    mapper        = vtkSmartPointer<vtkSmartVolumeMapper>::New();
}


// ****************************************************************************
//  Method: avtDefaultRenderer::~avtDefaultRenderer
//
//  Purpose:
//    Destructor.  
//
//  Programmer:  Alister Maguire
//  Creation:    April 3, 2017
//
//  Modifications:
//
// ****************************************************************************

avtDefaultRenderer::~avtDefaultRenderer()
{
}


// ****************************************************************************
//  Method:  avtDefaultRenderer::Render
//
//  Purpose:
//    Render a volume using a vtkSmartVolumeMapper 
//
//  Arguments:
//    props   : the rendering properties
//    volume  : the volume to be rendered 
//
//  Programmer:  Alister Maguire
//  Creation:    April 3, 2017
//
//  Modifications:
//
// ****************************************************************************

void
avtDefaultRenderer::Render(
    const avtVolumeRendererImplementation::RenderProperties &props,
    const avtVolumeRendererImplementation::VolumeData &volume)
{ 
    bool needsReset   = false;
    const char *mName = "avtDefaultRenderer::Render: ";

    //2D data has no volume, so we don't try to render this. 
    if (props.dataIs2D)
    {
        debug5 << mName << "Cannot perform volume rendering on " 
            << "2D data... returning" << endl;
        return;
    }

    if(imageToRender == NULL)
    {
        debug5 << mName << "Converting from rectilinear grid " 
            << "to image data" << endl;

        //Need to create a vtkImageData object to feed into the mapper. 
        int dims[3], extent[6];
        ((vtkRectilinearGrid *)volume.grid)->GetDimensions(dims);
        ((vtkRectilinearGrid *)volume.grid)->GetExtent(extent);
        vtkDataArray *dataArr = 
            ((vtkRectilinearGrid *)volume.grid)->GetPointData()->GetScalars();

        vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *)volume.grid;
        double spacingX = rgrid->GetXCoordinates()->GetTuple1(1)-
            rgrid->GetXCoordinates()->GetTuple1(0);
        double spacingY = rgrid->GetYCoordinates()->GetTuple1(1)-
            rgrid->GetYCoordinates()->GetTuple1(0);
        double spacingZ = rgrid->GetZCoordinates()->GetTuple1(1)-
            rgrid->GetZCoordinates()->GetTuple1(0);

        imageToRender = vtkSmartPointer<vtkImageData>::New();
        imageToRender->SetDimensions(dims);
        imageToRender->SetExtent(extent);
        imageToRender->SetSpacing(spacingX, spacingY, spacingZ);
        imageToRender->AllocateScalars(VTK_FLOAT, 1);
        int limit = dims[0] * dims[1] * dims[2];

        //Set the origin to match the lower bounds of the grid
        double bounds[6];
        ((vtkRectilinearGrid *)volume.grid)->GetBounds(bounds);
        imageToRender->SetOrigin(bounds[0], bounds[2], bounds[4]);

        float magnitude = volume.data.max - volume.data.min;
        
        //We need to transfer the rgrid data over to the image data, 
        //but we also need to scale the values to a range that opengl
        //can handle.
        float *scalarP = (float *)imageToRender->GetScalarPointer();
        for (int i = 0 ; i < limit ; i++)
        {
            float tuple1 = dataArr->GetTuple1(i);
            if (tuple1 <= NO_DATA_VALUE)
                scalarP[i] = -1.0;//just below our color map
            else
                scalarP[i] = ((255*(tuple1-volume.data.min))/magnitude);
        }

        debug5 << mName << "Adding data to the SmartVolumeMapper" << endl;

        mapper->SetInputData(imageToRender);
        mapper->SetScalarModeToUsePointData();
        mapper->SetBlendModeToComposite();
        resetColorMap = true;
        needsReset    = true;
    }

    if(resetColorMap || oldAtts != props.atts)
    {

        debug5 << mName << "Resetting color" << endl;

        //Getting color/alpha transfer function from VisIt
        unsigned char rgba[256*4];
        props.atts.GetTransferFunction(rgba);

        vtkSmartPointer<vtkColorTransferFunction> transFunc = 
            vtkSmartPointer<vtkColorTransferFunction>::New();
        vtkSmartPointer<vtkPiecewiseFunction> opacity = 
            vtkSmartPointer<vtkPiecewiseFunction>::New();

        //We don't want to see the default values, so we turn clamping
        //off (opacity becomes 0.0)
        transFunc->SetScaleToLinear();
        transFunc->SetClamping(0);
        opacity->SetClamping(0);

        float atten = props.atts.GetOpacityAttenuation()/256.f;

        //Add the color map to vtk's transfer function
        for(int i = 0; i < 256; i++) 
        {
            int rgbIdx  = 4*i;
            float curOp = rgba[rgbIdx+3]*atten; 
            transFunc->AddRGBPoint(i, rgba[rgbIdx]/255.f, rgba[rgbIdx+1]/255.f, 
                rgba[rgbIdx+2]/255.f);
            opacity->AddPoint(i, MAX(0.0, MIN(1.0, curOp)));
        }
 
        //For some reason, the endpoints aren't included when clamping 
        //is turned off. So, let's put some padding on the ends of our
        //mapping functions. 
        int lastIdx = 255*4;
        transFunc->AddRGBPoint(-1, rgba[0]/255.f, rgba[1]/255.f, 
            rgba[2]/255.f);
        transFunc->AddRGBPoint(256, rgba[lastIdx]/255.f, rgba[lastIdx+1]/255.f, 
            rgba[lastIdx+2]/255.f);
        opacity->AddPoint(-1, rgba[3]*atten);
        opacity->AddPoint(256, rgba[lastIdx+3]*atten);

        //Set the volume properties
        if (props.atts.GetLightingFlag()) 
            volumeProp->SetShade(1);
        else
            volumeProp->SetShade(0);
        volumeProp->SetScalarOpacity(opacity);
        volumeProp->SetColor(transFunc);
        volumeProp->SetInterpolationType(VTK_LINEAR_INTERPOLATION);

        resetColorMap = false;
        needsReset    = true;
        oldAtts       = props.atts;
    }

    debug5 << mName << "Checking if volume needs to be updated" << endl;

    //Create the volume to be rendered and
    //set its mapper to our SmartVolumeMapper. 
    if (curVolume  == NULL || needsReset)
    {
        debug5 << mName << "Updating the volume!" << endl;
 
        curVolume = vtkSmartPointer<vtkVolume>::New();
        curVolume->SetMapper(mapper);
        curVolume->SetProperty(volumeProp);
    }

    debug5 << mName << "Rendering!" << endl;

    mapper->Render(VTKRen, curVolume);
}
