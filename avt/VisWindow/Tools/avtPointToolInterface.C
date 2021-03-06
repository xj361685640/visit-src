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

#include <avtPointToolInterface.h>
#include <PointAttributes.h>
#include <VisWindow.h>

avtPointToolInterface::avtPointToolInterface(const VisWindow *v) :
    avtToolInterface(v)
{
    atts = new PointAttributes;
}

avtPointToolInterface::~avtPointToolInterface()
{
    // nothing
}

void
avtPointToolInterface::SetPoint(double x, double y, double z)
{
    PointAttributes *p = (PointAttributes *)atts;
    double d[3] = {x, y, z};
    if (const_cast<VisWindow*>(visWindow)->GetFullFrameMode())
    {
        //
        // If in full-frame mode, the point was computed in the scaled 
        // full-frame space.  Reverse the scaling to get the correct point. 
        //
        double scale;
        int type;
        const_cast<VisWindow*>(visWindow)->GetScaleFactorAndType(scale, type);
        if ( type == 0 && scale > 0.)
            d[0] /= scale;
        else if ( type == 1 && scale > 0.)
            d[1] /= scale;
    }
    p->SetPoint(d);
}

const double *
avtPointToolInterface::GetPoint() const
{
    PointAttributes *p = (PointAttributes *)atts;
    return p->GetPoint();
}
