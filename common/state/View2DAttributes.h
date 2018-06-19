/*****************************************************************************
*
* Copyright (c) 2000 - 2009, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-400124
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

#ifndef VIEW2DATTRIBUTES_H
#define VIEW2DATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>
#include <float.h>

// ****************************************************************************
// Class: View2DAttributes
//
// Purpose:
//    This class contains the 2d view attributes.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class STATE_API View2DAttributes : public AttributeSubject
{
public:
    enum TriStateMode
    {
        On,
        Off,
        Auto
    };
    static const double DEFAULT_FULL_FRAME_AUTO_THRESHOLD;

    View2DAttributes();
    View2DAttributes(const View2DAttributes &obj);
    virtual ~View2DAttributes();

    virtual View2DAttributes& operator = (const View2DAttributes &obj);
    virtual bool operator == (const View2DAttributes &obj) const;
    virtual bool operator != (const View2DAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectWindowCoords();
    void SelectViewportCoords();

    // Property setting methods
    void SetWindowCoords(const double *windowCoords_);
    void SetViewportCoords(const double *viewportCoords_);
    void SetFullFrameActivationMode(TriStateMode fullFrameActivationMode_);
    void SetFullFrameAutoThreshold(double fullFrameAutoThreshold_);
    void SetXScale(int xScale_);
    void SetYScale(int yScale_);

    // Property getting methods
    const double *GetWindowCoords() const;
          double *GetWindowCoords();
    const double *GetViewportCoords() const;
          double *GetViewportCoords();
    TriStateMode GetFullFrameActivationMode() const;
    double       GetFullFrameAutoThreshold() const;
    int          GetXScale() const;
    int          GetYScale() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string TriStateMode_ToString(TriStateMode);
    static bool TriStateMode_FromString(const std::string &, TriStateMode &);
protected:
    static std::string TriStateMode_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    bool GetUseFullFrame(const double *limits=0) const;
    void SetUseFullFrame(bool ff);

    // IDs that can be used to identify fields in case statements
    enum {
        ID_windowCoords = 0,
        ID_viewportCoords,
        ID_fullFrameActivationMode,
        ID_fullFrameAutoThreshold,
        ID_xScale,
        ID_yScale
    };

private:
    double windowCoords[4];
    double viewportCoords[4];
    int    fullFrameActivationMode;
    double fullFrameAutoThreshold;
    int    xScale;
    int    yScale;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
};

#endif
