// ***************************************************************************
//
// Copyright (c) 2000 - 2009, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-400124
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit.plots;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;
import llnl.visit.ColorAttribute;

// ****************************************************************************
// Class: MeshAttributes
//
// Purpose:
//    Attributes for the mesh plot
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class MeshAttributes extends AttributeSubject implements Plugin
{
    private static int numAdditionalAttributes = 19;

    // Enum values
    public final static int POINTTYPE_BOX = 0;
    public final static int POINTTYPE_AXIS = 1;
    public final static int POINTTYPE_ICOSAHEDRON = 2;
    public final static int POINTTYPE_POINT = 3;
    public final static int POINTTYPE_SPHERE = 4;

    public final static int SMOOTHINGLEVEL_NONE = 0;
    public final static int SMOOTHINGLEVEL_FAST = 1;
    public final static int SMOOTHINGLEVEL_HIGH = 2;

    public final static int MESHCOLOR_FOREGROUND = 0;
    public final static int MESHCOLOR_MESHCUSTOM = 1;

    public final static int OPAQUECOLOR_BACKGROUND = 0;
    public final static int OPAQUECOLOR_OPAQUECUSTOM = 1;

    public final static int OPAQUEMODE_AUTO = 0;
    public final static int OPAQUEMODE_ON = 1;
    public final static int OPAQUEMODE_OFF = 2;


    public MeshAttributes()
    {
        super(numAdditionalAttributes);

        legendFlag = true;
        lineStyle = 0;
        lineWidth = 0;
        meshColor = new ColorAttribute(0, 0, 0);
        outlineOnlyFlag = false;
        errorTolerance = 0.01;
        meshColorSource = MESHCOLOR_FOREGROUND;
        opaqueColorSource = OPAQUECOLOR_BACKGROUND;
        opaqueMode = OPAQUEMODE_AUTO;
        pointSize = 0.05;
        opaqueColor = new ColorAttribute(255, 255, 255);
        smoothingLevel = SMOOTHINGLEVEL_NONE;
        pointSizeVarEnabled = false;
        pointSizeVar = new String("default");
        pointType = POINTTYPE_POINT;
        opaqueMeshIsAppropriate = true;
        showInternal = false;
        pointSizePixels = 2;
        opacity = 1;
    }

    public MeshAttributes(int nMoreFields)
    {
        super(numAdditionalAttributes + nMoreFields);

        legendFlag = true;
        lineStyle = 0;
        lineWidth = 0;
        meshColor = new ColorAttribute(0, 0, 0);
        outlineOnlyFlag = false;
        errorTolerance = 0.01;
        meshColorSource = MESHCOLOR_FOREGROUND;
        opaqueColorSource = OPAQUECOLOR_BACKGROUND;
        opaqueMode = OPAQUEMODE_AUTO;
        pointSize = 0.05;
        opaqueColor = new ColorAttribute(255, 255, 255);
        smoothingLevel = SMOOTHINGLEVEL_NONE;
        pointSizeVarEnabled = false;
        pointSizeVar = new String("default");
        pointType = POINTTYPE_POINT;
        opaqueMeshIsAppropriate = true;
        showInternal = false;
        pointSizePixels = 2;
        opacity = 1;
    }

    public MeshAttributes(MeshAttributes obj)
    {
        super(numAdditionalAttributes);

        legendFlag = obj.legendFlag;
        lineStyle = obj.lineStyle;
        lineWidth = obj.lineWidth;
        meshColor = new ColorAttribute(obj.meshColor);
        outlineOnlyFlag = obj.outlineOnlyFlag;
        errorTolerance = obj.errorTolerance;
        meshColorSource = obj.meshColorSource;
        opaqueColorSource = obj.opaqueColorSource;
        opaqueMode = obj.opaqueMode;
        pointSize = obj.pointSize;
        opaqueColor = new ColorAttribute(obj.opaqueColor);
        smoothingLevel = obj.smoothingLevel;
        pointSizeVarEnabled = obj.pointSizeVarEnabled;
        pointSizeVar = new String(obj.pointSizeVar);
        pointType = obj.pointType;
        opaqueMeshIsAppropriate = obj.opaqueMeshIsAppropriate;
        showInternal = obj.showInternal;
        pointSizePixels = obj.pointSizePixels;
        opacity = obj.opacity;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return numAdditionalAttributes;
    }

    public boolean equals(MeshAttributes obj)
    {
        // Create the return value
        return ((legendFlag == obj.legendFlag) &&
                (lineStyle == obj.lineStyle) &&
                (lineWidth == obj.lineWidth) &&
                (meshColor == obj.meshColor) &&
                (outlineOnlyFlag == obj.outlineOnlyFlag) &&
                (errorTolerance == obj.errorTolerance) &&
                (meshColorSource == obj.meshColorSource) &&
                (opaqueColorSource == obj.opaqueColorSource) &&
                (opaqueMode == obj.opaqueMode) &&
                (pointSize == obj.pointSize) &&
                (opaqueColor == obj.opaqueColor) &&
                (smoothingLevel == obj.smoothingLevel) &&
                (pointSizeVarEnabled == obj.pointSizeVarEnabled) &&
                (pointSizeVar.equals(obj.pointSizeVar)) &&
                (pointType == obj.pointType) &&
                (opaqueMeshIsAppropriate == obj.opaqueMeshIsAppropriate) &&
                (showInternal == obj.showInternal) &&
                (pointSizePixels == obj.pointSizePixels) &&
                (opacity == obj.opacity));
    }

    public String GetName() { return "Mesh"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetLegendFlag(boolean legendFlag_)
    {
        legendFlag = legendFlag_;
        Select(0);
    }

    public void SetLineStyle(int lineStyle_)
    {
        lineStyle = lineStyle_;
        Select(1);
    }

    public void SetLineWidth(int lineWidth_)
    {
        lineWidth = lineWidth_;
        Select(2);
    }

    public void SetMeshColor(ColorAttribute meshColor_)
    {
        meshColor = meshColor_;
        Select(3);
    }

    public void SetOutlineOnlyFlag(boolean outlineOnlyFlag_)
    {
        outlineOnlyFlag = outlineOnlyFlag_;
        Select(4);
    }

    public void SetErrorTolerance(double errorTolerance_)
    {
        errorTolerance = errorTolerance_;
        Select(5);
    }

    public void SetMeshColorSource(int meshColorSource_)
    {
        meshColorSource = meshColorSource_;
        Select(6);
    }

    public void SetOpaqueColorSource(int opaqueColorSource_)
    {
        opaqueColorSource = opaqueColorSource_;
        Select(7);
    }

    public void SetOpaqueMode(int opaqueMode_)
    {
        opaqueMode = opaqueMode_;
        Select(8);
    }

    public void SetPointSize(double pointSize_)
    {
        pointSize = pointSize_;
        Select(9);
    }

    public void SetOpaqueColor(ColorAttribute opaqueColor_)
    {
        opaqueColor = opaqueColor_;
        Select(10);
    }

    public void SetSmoothingLevel(int smoothingLevel_)
    {
        smoothingLevel = smoothingLevel_;
        Select(11);
    }

    public void SetPointSizeVarEnabled(boolean pointSizeVarEnabled_)
    {
        pointSizeVarEnabled = pointSizeVarEnabled_;
        Select(12);
    }

    public void SetPointSizeVar(String pointSizeVar_)
    {
        pointSizeVar = pointSizeVar_;
        Select(13);
    }

    public void SetPointType(int pointType_)
    {
        pointType = pointType_;
        Select(14);
    }

    public void SetOpaqueMeshIsAppropriate(boolean opaqueMeshIsAppropriate_)
    {
        opaqueMeshIsAppropriate = opaqueMeshIsAppropriate_;
        Select(15);
    }

    public void SetShowInternal(boolean showInternal_)
    {
        showInternal = showInternal_;
        Select(16);
    }

    public void SetPointSizePixels(int pointSizePixels_)
    {
        pointSizePixels = pointSizePixels_;
        Select(17);
    }

    public void SetOpacity(double opacity_)
    {
        opacity = opacity_;
        Select(18);
    }

    // Property getting methods
    public boolean        GetLegendFlag() { return legendFlag; }
    public int            GetLineStyle() { return lineStyle; }
    public int            GetLineWidth() { return lineWidth; }
    public ColorAttribute GetMeshColor() { return meshColor; }
    public boolean        GetOutlineOnlyFlag() { return outlineOnlyFlag; }
    public double         GetErrorTolerance() { return errorTolerance; }
    public int            GetMeshColorSource() { return meshColorSource; }
    public int            GetOpaqueColorSource() { return opaqueColorSource; }
    public int            GetOpaqueMode() { return opaqueMode; }
    public double         GetPointSize() { return pointSize; }
    public ColorAttribute GetOpaqueColor() { return opaqueColor; }
    public int            GetSmoothingLevel() { return smoothingLevel; }
    public boolean        GetPointSizeVarEnabled() { return pointSizeVarEnabled; }
    public String         GetPointSizeVar() { return pointSizeVar; }
    public int            GetPointType() { return pointType; }
    public boolean        GetOpaqueMeshIsAppropriate() { return opaqueMeshIsAppropriate; }
    public boolean        GetShowInternal() { return showInternal; }
    public int            GetPointSizePixels() { return pointSizePixels; }
    public double         GetOpacity() { return opacity; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(legendFlag);
        if(WriteSelect(1, buf))
            buf.WriteInt(lineStyle);
        if(WriteSelect(2, buf))
            buf.WriteInt(lineWidth);
        if(WriteSelect(3, buf))
            meshColor.Write(buf);
        if(WriteSelect(4, buf))
            buf.WriteBool(outlineOnlyFlag);
        if(WriteSelect(5, buf))
            buf.WriteDouble(errorTolerance);
        if(WriteSelect(6, buf))
            buf.WriteInt(meshColorSource);
        if(WriteSelect(7, buf))
            buf.WriteInt(opaqueColorSource);
        if(WriteSelect(8, buf))
            buf.WriteInt(opaqueMode);
        if(WriteSelect(9, buf))
            buf.WriteDouble(pointSize);
        if(WriteSelect(10, buf))
            opaqueColor.Write(buf);
        if(WriteSelect(11, buf))
            buf.WriteInt(smoothingLevel);
        if(WriteSelect(12, buf))
            buf.WriteBool(pointSizeVarEnabled);
        if(WriteSelect(13, buf))
            buf.WriteString(pointSizeVar);
        if(WriteSelect(14, buf))
            buf.WriteInt(pointType);
        if(WriteSelect(15, buf))
            buf.WriteBool(opaqueMeshIsAppropriate);
        if(WriteSelect(16, buf))
            buf.WriteBool(showInternal);
        if(WriteSelect(17, buf))
            buf.WriteInt(pointSizePixels);
        if(WriteSelect(18, buf))
            buf.WriteDouble(opacity);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetLegendFlag(buf.ReadBool());
            break;
        case 1:
            SetLineStyle(buf.ReadInt());
            break;
        case 2:
            SetLineWidth(buf.ReadInt());
            break;
        case 3:
            meshColor.Read(buf);
            Select(3);
            break;
        case 4:
            SetOutlineOnlyFlag(buf.ReadBool());
            break;
        case 5:
            SetErrorTolerance(buf.ReadDouble());
            break;
        case 6:
            SetMeshColorSource(buf.ReadInt());
            break;
        case 7:
            SetOpaqueColorSource(buf.ReadInt());
            break;
        case 8:
            SetOpaqueMode(buf.ReadInt());
            break;
        case 9:
            SetPointSize(buf.ReadDouble());
            break;
        case 10:
            opaqueColor.Read(buf);
            Select(10);
            break;
        case 11:
            SetSmoothingLevel(buf.ReadInt());
            break;
        case 12:
            SetPointSizeVarEnabled(buf.ReadBool());
            break;
        case 13:
            SetPointSizeVar(buf.ReadString());
            break;
        case 14:
            SetPointType(buf.ReadInt());
            break;
        case 15:
            SetOpaqueMeshIsAppropriate(buf.ReadBool());
            break;
        case 16:
            SetShowInternal(buf.ReadBool());
            break;
        case 17:
            SetPointSizePixels(buf.ReadInt());
            break;
        case 18:
            SetOpacity(buf.ReadDouble());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("legendFlag", legendFlag, indent) + "\n";
        str = str + intToString("lineStyle", lineStyle, indent) + "\n";
        str = str + intToString("lineWidth", lineWidth, indent) + "\n";
        str = str + indent + "meshColor = {" + meshColor.Red() + ", " + meshColor.Green() + ", " + meshColor.Blue() + ", " + meshColor.Alpha() + "}\n";
        str = str + boolToString("outlineOnlyFlag", outlineOnlyFlag, indent) + "\n";
        str = str + doubleToString("errorTolerance", errorTolerance, indent) + "\n";
        str = str + indent + "meshColorSource = ";
        if(meshColorSource == MESHCOLOR_FOREGROUND)
            str = str + "MESHCOLOR_FOREGROUND";
        if(meshColorSource == MESHCOLOR_MESHCUSTOM)
            str = str + "MESHCOLOR_MESHCUSTOM";
        str = str + "\n";
        str = str + indent + "opaqueColorSource = ";
        if(opaqueColorSource == OPAQUECOLOR_BACKGROUND)
            str = str + "OPAQUECOLOR_BACKGROUND";
        if(opaqueColorSource == OPAQUECOLOR_OPAQUECUSTOM)
            str = str + "OPAQUECOLOR_OPAQUECUSTOM";
        str = str + "\n";
        str = str + indent + "opaqueMode = ";
        if(opaqueMode == OPAQUEMODE_AUTO)
            str = str + "OPAQUEMODE_AUTO";
        if(opaqueMode == OPAQUEMODE_ON)
            str = str + "OPAQUEMODE_ON";
        if(opaqueMode == OPAQUEMODE_OFF)
            str = str + "OPAQUEMODE_OFF";
        str = str + "\n";
        str = str + doubleToString("pointSize", pointSize, indent) + "\n";
        str = str + indent + "opaqueColor = {" + opaqueColor.Red() + ", " + opaqueColor.Green() + ", " + opaqueColor.Blue() + ", " + opaqueColor.Alpha() + "}\n";
        str = str + indent + "smoothingLevel = ";
        if(smoothingLevel == SMOOTHINGLEVEL_NONE)
            str = str + "SMOOTHINGLEVEL_NONE";
        if(smoothingLevel == SMOOTHINGLEVEL_FAST)
            str = str + "SMOOTHINGLEVEL_FAST";
        if(smoothingLevel == SMOOTHINGLEVEL_HIGH)
            str = str + "SMOOTHINGLEVEL_HIGH";
        str = str + "\n";
        str = str + boolToString("pointSizeVarEnabled", pointSizeVarEnabled, indent) + "\n";
        str = str + stringToString("pointSizeVar", pointSizeVar, indent) + "\n";
        str = str + indent + "pointType = ";
        if(pointType == POINTTYPE_BOX)
            str = str + "POINTTYPE_BOX";
        if(pointType == POINTTYPE_AXIS)
            str = str + "POINTTYPE_AXIS";
        if(pointType == POINTTYPE_ICOSAHEDRON)
            str = str + "POINTTYPE_ICOSAHEDRON";
        if(pointType == POINTTYPE_POINT)
            str = str + "POINTTYPE_POINT";
        if(pointType == POINTTYPE_SPHERE)
            str = str + "POINTTYPE_SPHERE";
        str = str + "\n";
        str = str + boolToString("opaqueMeshIsAppropriate", opaqueMeshIsAppropriate, indent) + "\n";
        str = str + boolToString("showInternal", showInternal, indent) + "\n";
        str = str + intToString("pointSizePixels", pointSizePixels, indent) + "\n";
        str = str + doubleToString("opacity", opacity, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean        legendFlag;
    private int            lineStyle;
    private int            lineWidth;
    private ColorAttribute meshColor;
    private boolean        outlineOnlyFlag;
    private double         errorTolerance;
    private int            meshColorSource;
    private int            opaqueColorSource;
    private int            opaqueMode;
    private double         pointSize;
    private ColorAttribute opaqueColor;
    private int            smoothingLevel;
    private boolean        pointSizeVarEnabled;
    private String         pointSizeVar;
    private int            pointType;
    private boolean        opaqueMeshIsAppropriate;
    private boolean        showInternal;
    private int            pointSizePixels;
    private double         opacity;
}

