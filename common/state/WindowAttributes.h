/*****************************************************************************
*
* Copyright (c) 2000 - 2016, Lawrence Livermore National Security, LLC
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

#ifndef WINDOWATTRIBUTES_H
#define WINDOWATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>

#include <ViewCurveAttributes.h>
#include <View2DAttributes.h>
#include <View3DAttributes.h>
#include <ViewAxisArrayAttributes.h>
#include <LightList.h>
#include <RenderingAttributes.h>
#include <ColorTableAttributes.h>

// ****************************************************************************
// Class: WindowAttributes
//
// Purpose:
//    This class contains the attributes for a visualization window.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class STATE_API WindowAttributes : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    WindowAttributes();
    WindowAttributes(const WindowAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    WindowAttributes(private_tmfs_t tmfs);
    WindowAttributes(const WindowAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~WindowAttributes();

    virtual WindowAttributes& operator = (const WindowAttributes &obj);
    virtual bool operator == (const WindowAttributes &obj) const;
    virtual bool operator != (const WindowAttributes &obj) const;
private:
    void Init();
    void Copy(const WindowAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectViewCurve();
    void SelectView2D();
    void SelectView3D();
    void SelectViewAxisArray();
    void SelectLights();
    void SelectRenderAtts();
    void SelectColorTables();
    void SelectSize();
    void SelectBackground();
    void SelectForeground();
    void SelectGradBG1();
    void SelectGradBG2();
    void SelectBackgroundImage();

    // Property setting methods
    void SetViewCurve(const ViewCurveAttributes &viewCurve_);
    void SetView2D(const View2DAttributes &view2D_);
    void SetView3D(const View3DAttributes &view3D_);
    void SetViewAxisArray(const ViewAxisArrayAttributes &viewAxisArray_);
    void SetLights(const LightList &lights_);
    void SetRenderAtts(const RenderingAttributes &renderAtts_);
    void SetColorTables(const ColorTableAttributes &colorTables_);
    void SetSize(const int *size_);
    void SetBackground(const unsigned char *background_);
    void SetForeground(const unsigned char *foreground_);
    void SetBackgroundMode(int backgroundMode_);
    void SetGradBG1(const double *gradBG1_);
    void SetGradBG2(const double *gradBG2_);
    void SetGradientBackgroundStyle(int gradientBackgroundStyle_);
    void SetBackgroundImage(const std::string &backgroundImage_);
    void SetImageRepeatX(int imageRepeatX_);
    void SetImageRepeatY(int imageRepeatY_);

    // Property getting methods
    const ViewCurveAttributes     &GetViewCurve() const;
          ViewCurveAttributes     &GetViewCurve();
    const View2DAttributes        &GetView2D() const;
          View2DAttributes        &GetView2D();
    const View3DAttributes        &GetView3D() const;
          View3DAttributes        &GetView3D();
    const ViewAxisArrayAttributes &GetViewAxisArray() const;
          ViewAxisArrayAttributes &GetViewAxisArray();
    const LightList               &GetLights() const;
          LightList               &GetLights();
    const RenderingAttributes     &GetRenderAtts() const;
          RenderingAttributes     &GetRenderAtts();
    const ColorTableAttributes    &GetColorTables() const;
          ColorTableAttributes    &GetColorTables();
    const int                     *GetSize() const;
          int                     *GetSize();
    const unsigned char           *GetBackground() const;
          unsigned char           *GetBackground();
    const unsigned char           *GetForeground() const;
          unsigned char           *GetForeground();
    int                           GetBackgroundMode() const;
    const double                  *GetGradBG1() const;
          double                  *GetGradBG1();
    const double                  *GetGradBG2() const;
          double                  *GetGradBG2();
    int                           GetGradientBackgroundStyle() const;
    const std::string             &GetBackgroundImage() const;
          std::string             &GetBackgroundImage();
    int                           GetImageRepeatX() const;
    int                           GetImageRepeatY() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_viewCurve = 0,
        ID_view2D,
        ID_view3D,
        ID_viewAxisArray,
        ID_lights,
        ID_renderAtts,
        ID_colorTables,
        ID_size,
        ID_background,
        ID_foreground,
        ID_backgroundMode,
        ID_gradBG1,
        ID_gradBG2,
        ID_gradientBackgroundStyle,
        ID_backgroundImage,
        ID_imageRepeatX,
        ID_imageRepeatY,
        ID__LAST
    };

private:
    ViewCurveAttributes     viewCurve;
    View2DAttributes        view2D;
    View3DAttributes        view3D;
    ViewAxisArrayAttributes viewAxisArray;
    LightList               lights;
    RenderingAttributes     renderAtts;
    ColorTableAttributes    colorTables;
    int                     size[2];
    unsigned char           background[3];
    unsigned char           foreground[3];
    int                     backgroundMode;
    double                  gradBG1[3];
    double                  gradBG2[3];
    int                     gradientBackgroundStyle;
    std::string             backgroundImage;
    int                     imageRepeatX;
    int                     imageRepeatY;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define WINDOWATTRIBUTES_TMFS "aaaaaaaIUUiDDisii"

#endif
