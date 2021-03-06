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

#include "QvisGaussianOpacityBar.h"

#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPolygon>

#include <visitstream.h>
#include <math.h>
#include <stdlib.h>

// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::QvisGaussianOpacityBar
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Wed Jun  4 10:35:08 PDT 2008
//    Qt 4.
//
// ****************************************************************************

QvisGaussianOpacityBar::QvisGaussianOpacityBar(QWidget *parent)
    : QvisAbstractOpacityBar(parent)
{
    setFrameStyle( QFrame::Panel | QFrame::Sunken );
    setLineWidth( 2 );
    setMinimumHeight(50);
    setMinimumWidth(128);
    ngaussian = 0;
    currentGaussian = 0;
    currentMode     = modeNone;

    // set a default:
    addGaussian(0.5, 0.5, 0.1, 0, 0);

    mousedown = false;
    setMouseTracking(true);
}

// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::~QvisGaussianOpacityBar
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************

QvisGaussianOpacityBar::~QvisGaussianOpacityBar()
{
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::drawControlPoints
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Wed Jun  4 10:37:39 PDT 2008
//    Draw on the image as opposed to a pixmap.
//
// ****************************************************************************

void
QvisGaussianOpacityBar::drawControlPoints()
{
    int pw = image->width();
    int ph = image->height();
    QPainter painter(image);
    QPen bluepen(QColor(100,100,255), 2);
    QPen greenpen(QColor(100,255,0),  2);;
    QPen cyanpen(QColor(100,255,255), 2);;
    QPen graypen(QColor(100,100,100), 2);
    QPolygon pts;
    for (int p=0; p<ngaussian; p++)
    {
        int x  = int(float(gaussian[p].x+gaussian[p].bx)*float(pw));
        int xr = int(float(gaussian[p].x+gaussian[p].w)*float(pw));
        int xl = int(float(gaussian[p].x-gaussian[p].w)*float(pw));
        int y  = int(float(1-gaussian[p].h)*float(ph));
        int y0 = int(float(1-0)*float(ph));
        int yb = int(float(1-gaussian[p].h/4. - gaussian[p].by*gaussian[p].h/4.)*float(ph));

        // lines:
        painter.setPen(graypen);
        painter.drawLine(x,y0-2, x,y);
        painter.drawLine(xl,y0-2, xr,y0-2);

        // square: position
        if (currentGaussian == p && currentMode == modeX)
        {
            if (mousedown)
                painter.setPen(greenpen);
            else
                painter.setPen(cyanpen);
        }
        else
            painter.setPen(bluepen);
        pts.setPoints(4, x-4,y0, x-4,y0-4, x+4,y0-4, x+4,y0);
        painter.drawPolyline(pts);

        // diamond: bias (horizontal and vertical)
        if (currentGaussian == p && currentMode == modeB)
        {
            if (mousedown)
                painter.setPen(greenpen);
            else
                painter.setPen(cyanpen);
        }
        else
            painter.setPen(bluepen);
        float bx = gaussian[p].bx;
        float by = gaussian[p].by;
        painter.drawLine(x,yb, x,yb+5);
        if (bx > 0)
        {
            painter.drawLine(x,yb-5, x+5,yb);
            painter.drawLine(x,yb+5, x+5,yb);
        }
        else
        {
            painter.drawLine(x,yb, x+5,yb);
        }
        if (bx < 0)
        {
            painter.drawLine(x,yb-5, x-5,yb);
            painter.drawLine(x,yb+5, x-5,yb);
        }
        else
        {
            painter.drawLine(x-5,yb, x,yb);
        }
        if (by > 0)
        {
            painter.drawLine(x,yb-5, x-5,yb);
            painter.drawLine(x,yb-5, x+5,yb);
        }
        else
        {
            painter.drawLine(x,yb-5, x,yb);
        }

        // up triangle: height
        if (currentGaussian == p && currentMode == modeH)
        {
            if (mousedown)
                painter.setPen(greenpen);
            else
                painter.setPen(cyanpen);
        }
        else
            painter.setPen(bluepen);
        pts.setPoints(4, x+5,y, x,y-5, x-5,y, x+5,y);
        painter.drawPolyline(pts);

        // triangle: width (R)
        if (currentGaussian == p && (currentMode == modeWR || currentMode == modeW))
        {
            if (mousedown)
                painter.setPen(greenpen);
            else
                painter.setPen(cyanpen);
        }
        else
            painter.setPen(bluepen);
        pts.setPoints(3, xr,y0, xr,y0-6, xr+6,y0);
        painter.drawPolyline(pts);

        // triangle: width (L)
        if (currentGaussian == p && (currentMode == modeWL  || currentMode == modeW))
        {
            if (mousedown)
                painter.setPen(greenpen);
            else
                painter.setPen(cyanpen);
        }
        else
            painter.setPen(bluepen);
        pts.setPoints(3, xl,y0, xl,y0-6, xl-6,y0);
        painter.drawPolyline(pts);
    }
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::drawOpacities
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Gunther H. Weber, April 6, 2007
//    Added possibility of having a "color table" background instead of solid
//    black background.
//
//    Brad Whitlock, Wed Jun  4 10:38:23 PDT 2008
//    Draw on an image instead of a pixmap.
//
//    Brad Whitlock, Thu Dec 18 12:10:05 PST 2008
//    I moved some code to the base class.
//
// ****************************************************************************

void
QvisGaussianOpacityBar::drawOpacities()
{
    int w = contentsRect().width();
    int h = contentsRect().height();
    float *values = getRawOpacities(w);

    QColor white(255, 255, 255 );
    QRgb cw = white.rgb();
    float dy = 1.0/float(h-1);
    for (int x = 0; x < w; x++)
    {
        float yval1 = values[x];
        float yval2 = values[x+1];
        for (int y = 0; y < h; y++)
        {
            float yvalc = 1 - float(y)/float(h-1);
            if (yvalc >= qMin(yval1,yval2)-dy && yvalc < qMax(yval1,yval2))
                image->setPixel(x,y, cw); 
       }
    }
    delete [] values;

    drawControlPoints();
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::mousePressEvent
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Wed Jun  4 10:39:42 PDT 2008
//    Use update().
//
//    Brad Whitlock, Thu Dec 18 14:05:51 PST 2008
//    I changed how the image gets updated.
//
// ****************************************************************************

void
QvisGaussianOpacityBar::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    if (e->button() == Qt::RightButton)
    {
        if (findGaussianControlPoint(x,y, &currentGaussian, &currentMode))
            removeGaussian(currentGaussian);
    }
    else if (e->button() == Qt::LeftButton)
    {
        if (! findGaussianControlPoint(x,y,
                                       &currentGaussian, &currentMode))
        {
            currentGaussian = ngaussian;
            currentMode     = modeW;
            addGaussian(x2val(x), y2val(y), 0.001, 0,0);
        }
        lastx = x;
        lasty = y;
        mousedown = true;
    }

    imageDirty();
    update();
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::mouseMoveEvent
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Wed Jun  4 10:40:22 PDT 2008
//    Use update().
//
//    Jeremy Meredith, Thu Aug  7 15:39:32 EDT 2008
//    Added missing case to avoid warnings.
//
//    Cyrus Harrison, Mon Aug 25 16:26:20 PDT 2008
//    Fixed build problem on AIX - confusion between float and double literal.
//
//    Brad Whitlock, Thu Dec 18 14:05:51 PST 2008
//    I changed how the image gets updated.
//
// ****************************************************************************

void
QvisGaussianOpacityBar::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    if (!mousedown)
    {
        int  oldGaussian = currentGaussian;
        Mode oldMode     = currentMode;
        findGaussianControlPoint(x,y, &currentGaussian, &currentMode);
        if (oldGaussian != currentGaussian ||
            oldMode     != currentMode)
        {
            imageDirty(); //drawControlPoints();
            update();
        }
        return;
    }

    switch (currentMode)
    {
      case modeX:
        gaussian[currentGaussian].x = x2val(x) - gaussian[currentGaussian].bx;
        break;
      case modeH:
        gaussian[currentGaussian].h = y2val(y);
        break;
      case modeW:
        gaussian[currentGaussian].w = qMax((float)fabs(x2val(x) - gaussian[currentGaussian].x),0.01f);
        break;
      case modeWR:
        gaussian[currentGaussian].w = qMax(x2val(x) - gaussian[currentGaussian].x,0.01f);
        if (gaussian[currentGaussian].w < fabs(gaussian[currentGaussian].bx))
            gaussian[currentGaussian].w = fabs(gaussian[currentGaussian].bx);
        break;
      case modeWL:
        gaussian[currentGaussian].w = qMax(gaussian[currentGaussian].x - x2val(x),0.01f);
        if (gaussian[currentGaussian].w < fabs(gaussian[currentGaussian].bx))
            gaussian[currentGaussian].w = fabs(gaussian[currentGaussian].bx);
        break;
      case modeB:
        gaussian[currentGaussian].bx = x2val(x) - gaussian[currentGaussian].x;
        if (gaussian[currentGaussian].bx > gaussian[currentGaussian].w)
            gaussian[currentGaussian].bx = gaussian[currentGaussian].w;
        if (gaussian[currentGaussian].bx < -gaussian[currentGaussian].w)
            gaussian[currentGaussian].bx = -gaussian[currentGaussian].w;
        if (fabs(gaussian[currentGaussian].bx) < .001)
            gaussian[currentGaussian].bx = 0;

        gaussian[currentGaussian].by = 4*(y2val(y) - gaussian[currentGaussian].h/4.)/gaussian[currentGaussian].h;
        if (gaussian[currentGaussian].by > 2)
            gaussian[currentGaussian].by = 2;
        if (gaussian[currentGaussian].by < 0)
            gaussian[currentGaussian].by = 0;
        break;
      case modeNone:
        break;
    }
    lastx = x;
    lasty = y;

    imageDirty();
    update();
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::mouseReleaseEvent
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Wed Jun  4 10:41:07 PDT 2008
//    Use update().
//
//    Brad Whitlock, Thu Dec 18 14:05:51 PST 2008
//    I changed how the image gets updated.
//
// ****************************************************************************

void
QvisGaussianOpacityBar::mouseReleaseEvent(QMouseEvent *)
{
    mousedown = false;

    imageDirty();
    update();

    emit mouseReleased();
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::getRawOpacities
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
float *
QvisGaussianOpacityBar::getRawOpacities(int n)
{
    float *values = new float[n+1];
    for (int i=0; i<n+1; i++)
        values[i] = 0;

    for (int p=0; p<ngaussian; p++)
    {
        float pos    = gaussian[p].x;
        float width  = gaussian[p].w;
        float height = gaussian[p].h;
        float xbias  = gaussian[p].bx;
        float ybias  = gaussian[p].by;
        for (int i=0; i<n+1; i++)
        {
            float x = float(i)/float(n-1);

            // clamp non-zero values to pos +/- width
            if (x > pos+width || x < pos-width)
            {
                values[i] = qMax(values[i],0.f);
                continue;
            }

            // non-zero width
            if (width == 0)
                width = .00001;

            // translate the original x to a new x based on the xbias
            float x0;
            if (xbias==0 || x == pos+xbias)
            {
                x0 = x;
            }
            else if (x > pos+xbias)
            {
                if (width == xbias)
                    x0 = pos;
                else
                    x0 = pos+(x-pos-xbias)*(width/(width-xbias));
            }
            else // (x < pos+xbias)
            {
                if (-width == xbias)
                    x0 = pos;
                else
                    x0 = pos-(x-pos-xbias)*(width/(width+xbias));
            }

            // center around 0 and normalize to -1,1
            float x1 = (x0-pos)/width;

            // do a linear interpolation between:
            //    a gaussian and a parabola        if 0<ybias<1
            //    a parabola and a step function   if 1<ybias<2
            float h0a = exp(-(4*x1*x1));
            float h0b = 1. - x1*x1;
            float h0c = 1.;
            float h1;
            if (ybias < 1)
                h1 = ybias*h0b + (1-ybias)*h0a;
            else
                h1 = (2-ybias)*h0b + (ybias-1)*h0c;
            float h2 = height * h1;
            
            // perform the MAX over different guassians, not the sum
            values[i] = qMax(values[i], h2);
        }
    }

    return values;
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::addGaussian
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
void
QvisGaussianOpacityBar::addGaussian(float x,float h,float w,float bx,float by)
{
    gaussian[ngaussian++] = Gaussian(x,h,w,bx,by);
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::removeGaussian
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
void
QvisGaussianOpacityBar::removeGaussian(int n)
{
    for (int i=n; i<ngaussian-1; i++)
        gaussian[i] = gaussian[i+1];
    ngaussian--;
}



// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::removeAllGaussian
//
//  Purpose:
//    
//
//  Programmer:  Pascal Grosset
//  Creation:    September 15, 2015
//
// ****************************************************************************
void
QvisGaussianOpacityBar::removeAllGaussians()
{
    ngaussian=0;

    imageDirty();
    update();
}


#define dist2(x1,y1,x2,y2) (((x2)-(x1))*((x2)-(x1)) + ((y2)-(y1))*((y2)-(y1)))
// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::findGaussianControlPoint
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
bool
QvisGaussianOpacityBar::findGaussianControlPoint(int x,int y,
                                             int *newgaussian, Mode *newmode)
{
    *newgaussian = -1;
    *newmode     = modeNone;
    bool  found   = false;
    float mindist = 100000;  // it's okay, it's pixels
    for (int p=0; p<ngaussian; p++)
    {
        int xc = val2x(gaussian[p].x+gaussian[p].bx);
        int xr = val2x(gaussian[p].x+gaussian[p].w);
        int xl = val2x(gaussian[p].x-gaussian[p].w);
        int yc = val2y(gaussian[p].h);
        int y0 = val2y(0);
        int yb = val2y(gaussian[p].h/4. + gaussian[p].by*gaussian[p].h/4.);

        float d1 = dist2(x,y, xc,y0);
        float d2 = dist2(x,y, xc,yc);
        float d3 = dist2(x,y, xr,y0);
        float d4 = dist2(x,y, xl,y0);
        float d5 = dist2(x,y, xc,yb);

        float rad = 8*8;

        if (d1 < rad && mindist > d1)
        {
            *newgaussian = p;
            *newmode     = modeX;
            mindist          = d1;
            found = true;
        }
        if (d2 < rad && mindist > d2)
        {
            *newgaussian = p;
            *newmode     = modeH;
            mindist          = d2;
            found = true;
        }
        if (d3 < rad && mindist > d3)
        {
            *newgaussian = p;
            *newmode     = modeWR;
            mindist          = d3;
            found = true;
        }
        if (d4 < rad && mindist > d4)
        {
            *newgaussian = p;
            *newmode     = modeWL;
            mindist          = d4;
            found = true;
        }
        if (d5 < rad && mindist > d5)
        {
            *newgaussian = p;
            *newmode     = modeB;
            mindist          = d5;
            found = true;
        }
    }
    return found;
}



// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::getNumberOfGaussians
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
int
QvisGaussianOpacityBar::getNumberOfGaussians()
{
    return ngaussian;
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::getGaussian
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
// ****************************************************************************
void
QvisGaussianOpacityBar::getGaussian(int i,
                                float *x,
                                float *h,
                                float *w,
                                float *bx,
                                float *by)
{
    *x  = gaussian[i].x;
    *h  = gaussian[i].h;
    *w  = gaussian[i].w;
    *bx = gaussian[i].bx;
    *by = gaussian[i].by;
}


// ****************************************************************************
//  Method:  QvisGaussianOpacityBar::setAllGaussians
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Thu Dec 18 14:05:51 PST 2008
//    I changed how the image gets updated.
//
// ****************************************************************************
void
QvisGaussianOpacityBar::setAllGaussians(int n, float *gaussdata)
{
    ngaussian = 0;
    for (int i=0; i<n; i++)
    {
        addGaussian(gaussdata[i*5 + 0],
                    gaussdata[i*5 + 1],
                    gaussdata[i*5 + 2],
                    gaussdata[i*5 + 3],
                    gaussdata[i*5 + 4]);
    }

    imageDirty();
    update();
}
