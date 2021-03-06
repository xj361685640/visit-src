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
#include <QtCore>
#include <QPainter>
#include <QImage>

#include "vtkQtImagePrinter.h"
#include "vtkObjectFactory.h"

#include <vtkImageData.h>
#include <vtkPointData.h>

// ****************************************************************************
// Method: vtkQtImagePrinter::New
//
// Purpose: 
//   Creates a new instance of a vtkQtImagePrinter object.
//
// Returns:    A pointer to a new instance of a vtkQtImagePrinter object.
//
// Programmer: Brad Whitlock
// Creation:   Thu Feb 21 15:57:48 PST 2002
//
// Modifications:
//   
// ****************************************************************************

vtkQtImagePrinter *
vtkQtImagePrinter::New()
{
    // First try to create the object from the vtkObjectFactory
    vtkObject* ret = vtkObjectFactory::CreateInstance("vtkQtImagePrinter");
    if(ret)
    {
        return (vtkQtImagePrinter*)ret;
    }

    // If the factory was unable to create the object, then create it here.
    return new vtkQtImagePrinter;
}

// ****************************************************************************
// Method: vtkQtImagePrinter::vtkQtImagePrinter
//
// Purpose: 
//   Constructor for the vtkQtImagePrinter class.
//
// Programmer: Brad Whitlock
// Creation:   Thu Feb 21 15:56:22 PST 2002
//
// Modifications:
//
// ****************************************************************************

vtkQtImagePrinter::vtkQtImagePrinter() : print()
{
    this->FileLowerLeft = 1;
}

// ****************************************************************************
// Method: vtkQtImagePrinter::WriteFile
//
// Purpose: 
//   Extracts the pixels from the image data and sends them to a Qt printer
//   object where they go to a file or a network printer.
//
// Arguments:
//   data   : The image data object.
//   extent : The size of the image.
//
// Programmer: Brad Whitlock
// Creation:   Thu Feb 21 15:55:05 PST 2002
//
// Modifications:
//   Brad Whitlock, Tue Feb 22 09:34:09 PDT 2005
//   I rewrote the code so it makes a single call to QPainter::drawImage
//   instead of drawing each scanline independently so we don't get horizontal
//   stripes in the output image. This uses more memory but it looks way better
//   in the printed image.
//
//   Brad Whitlock, Fri May 12 14:49:52 PST 2006
//   Check for data == NULL just in case.
//
//   Kathleen Bonnell, Wed Aug 22 17:40:34 PDT 2007 
//   Made scaling of viewport coords specific to WIN32 and QT version 3.0.2. 
//
//   Brad Whitlock, Fri May  9 10:21:26 PDT 2008
//   Qt 4.
//
// ****************************************************************************

void
vtkQtImagePrinter::WriteFile(ofstream *, vtkImageData *data, int extent[6], int [6])
{
    // Make sure that data is not NULL.
    if(data == NULL)
    {
        vtkErrorMacro(<< "NULL input.");
        return;
    }

    // Make sure we actually have data.
    if(!data->GetPointData()->GetScalars())
    {
        vtkErrorMacro(<< "Could not get data from input.");
        return;
    }

    // take into consideration the scalar type
    if(data->GetScalarType() != VTK_UNSIGNED_CHAR)
    {
        vtkErrorMacro("vtkQtImagePrinter only accepts unsigned char scalars!");
        return; 
    }

    // Try and start drawing on the printer.
    QPainter paint;
    if(!paint.begin(&print))
    {
        vtkErrorMacro("vtkQtImagePrinter cannot print!");
        return;
    }

    // Find the image dimensions
    int rowLength = extent[1] - extent[0] + 1;
    int columnHeight = extent[3] - extent[2] + 1;

    //
    // Figure out a viewport that will center the image on the printer page.
    //
    int vptW = rowLength;
    int vptH = columnHeight;
    bool squeezeX = vptW > print.width();
    bool squeezeY = vptH > print.height();
    float aspect = float(vptH) / float(vptW);
    do
    {
        if(squeezeX && squeezeY)
        {
            if(aspect > 1.)
            {
                // Taller than wide
                vptH = print.height();
                vptW = int(float(vptH) / aspect);
                squeezeY = false;
            }
            else
            {
                // Wider than tall
                vptW = print.width();
                vptH = int(float(vptW) * aspect);
                squeezeX = false;
            }
        }

        if(squeezeX)
        {
            // X dimension larger, Y smaller
            vptW = print.width();
            vptH = int(float(print.width()) * aspect);
        }
        else if(squeezeY)
        {
            // Y dimension larger, X smaller.
            vptH = print.height();
            vptW = int(float(print.height()) / aspect);
        }

        // See if we need to go through the loop again.
        squeezeX = vptW > print.width();
        squeezeY = vptH > print.height();
    } while(squeezeX || squeezeY);

    //
    // Set the viewport and the window.
    //
    int vptX = (print.width() - vptW) / 2;
    int vptY = (print.height() - vptH) / 2;
    paint.setViewport(vptX, vptY, vptW, vptH);
//    qDebug("paint.setViewport2(%d,%d,%d,%d)", vptX, vptY, vptW, vptH);
    paint.setWindow(0, 0, rowLength, columnHeight);
//    qDebug("paint.setWindow(0,0,%d,%d)", rowLength, columnHeight);

    //
    // Crudely determine the machine endianness.
    //
    unsigned int endianVal = 1;
    unsigned char *endianuptr = (unsigned char *)&endianVal;
    bool bigEndian = (endianuptr[0] != 1);

    //
    // Set up a pointer to the buffer that we'll use to create the image.
    //
    int bpp = data->GetNumberOfScalarComponents();
//    qDebug("bpp = %d", bpp);
    unsigned char *imageData = 0;
    bool ownImageData = false;
    if(bpp < 4)
    {
        imageData = (unsigned char *)(new unsigned int[rowLength * columnHeight]);
        unsigned char *uptr = imageData;
        ownImageData = true;

        // Rearrange memory into the format the QImage wants so we can make
        // a single call to QPrinter::drawImage.
        for(int y = extent[3]; y >= extent[2]; --y)
        {
            unsigned char *ptr = (unsigned char *)data->GetScalarPointer(extent[0], y, 0);
            if(bpp == 3)
            {
                if(bigEndian)
                {
                    for(int i = 0; i < rowLength; ++i, ptr += 3)
                    {
                        *uptr++ = 255;
                        *uptr++ = ptr[0];
                        *uptr++ = ptr[1];
                        *uptr++ = ptr[2];
                    }
                }
                else
                {
                    for(int i = 0; i < rowLength; ++i, ptr += 3)
                    {
                        *uptr++ = ptr[2];
                        *uptr++ = ptr[1];
                        *uptr++ = ptr[0];
                        *uptr++ = 255;
                    }
                }
            }
            else if(bpp == 1)
            {
                for(int i = 0; i < rowLength; ++i)
                {
                    *uptr++ = ptr[i];
                    *uptr++ = ptr[i];
                    *uptr++ = ptr[i];
                    *uptr++ = ptr[i];
                }
            }
            else if(bpp == 2)
            {
                for(int i = 0; i < rowLength; ++i, ptr += 2)
                {
                    *uptr++ = ptr[0];
                    *uptr++ = ptr[0];
                    *uptr++ = ptr[0];
                    *uptr++ = ptr[0];
                }
            }
        }
    }
    else
        imageData = (unsigned char *)data->GetScalarPointer(extent[0], extent[2], 0);

    //
    // Draw the image on the printer surface.
    //
    int bytesPerLine = 4 * rowLength;
    QImage image(imageData, rowLength, columnHeight, bytesPerLine, QImage::Format_RGB32);
    paint.drawImage(QPoint(0, 0), image);

    // Indicate that we're done drawing.
    paint.end();

    if(ownImageData)
        delete [] imageData;
}
