/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
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
//  File: avtConeFilter.h
// ************************************************************************* //

#ifndef AVT_Cone_FILTER_H
#define AVT_Cone_FILTER_H


#include <avtPluginDataTreeIterator.h>
#include <ConeAttributes.h>


class vtkClipPolyData;
class vtkCone;
class vtkVisItCutter;
class vtkDataSet;
class vtkImplicitBoolean;
class vtkPlane;
class vtkTransformPolyDataFilter;

class vtkPolarTransformFilter;


// ****************************************************************************
//  Class: avtConeFilter
//
//  Purpose:
//      A plugin operator for Cone.
//
//  Programmer: childs -- generated by xml2info
//  Creation:   Wed May 29 16:09:58 PST 2002
//
//  Modifications:
//    Kathleen Bonnell, Tue May 20 10:23:38 PDT 2003
//    Added method ModifyContract.
//
//    Kathleen Bonnell, Thu Apr 28 10:28:22 PDT 2005
//    Use vtkVisItCutter instead of vtkCutter, since it has logic to correctly
//    handle CellData.
//
// ****************************************************************************

class avtConeFilter : public avtPluginDataTreeIterator
{
  public:
                                 avtConeFilter();
    virtual                     ~avtConeFilter();

    static avtFilter            *Create();

    virtual const char          *GetType(void)  { return "avtConeFilter"; };
    virtual const char          *GetDescription(void) 
                                             { return "Slicing by a cone"; };
    virtual void                 ReleaseData(void);

    virtual void                 SetAtts(const AttributeGroup*);
    virtual bool                 Equivalent(const AttributeGroup*);

  protected:
    ConeAttributes               atts;
    vtkCone                     *cone;
    vtkVisItCutter              *cutter;
    vtkImplicitBoolean          *allFunctions;
    vtkPlane                    *plane;
    vtkPolarTransformFilter     *polar;
    vtkTransformPolyDataFilter  *transform;
    vtkClipPolyData             *clipOffSides;
    vtkClipPolyData             *clipBottom;
    vtkPlane                    *planeToClipBottom;
    vtkClipPolyData             *clipByLength;
    vtkPlane                    *planeToClipByLength;

    virtual vtkDataSet          *ExecuteData(vtkDataSet *, int, std::string);
    virtual void                 UpdateDataObjectInfo(void);
    void                         SetUpClipping(void);
    void                         SetUpCone(void);
    void                         SetUpProjection(void);
    avtContract_p   ModifyContract(avtContract_p);
};


#endif
