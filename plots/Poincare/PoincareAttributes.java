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
// Class: PoincareAttributes
//
// Purpose:
//    Attributes for the Poincare plot
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class PoincareAttributes extends AttributeSubject implements Plugin
{
    private static int numAdditionalAttributes = 38;

    // Enum values
    public final static int SOURCETYPE_SPECIFIEDPOINT = 0;
    public final static int SOURCETYPE_SPECIFIEDLINE = 1;
    public final static int SOURCETYPE_SPECIFIEDPLANE = 2;

    public final static int TERMINATIONTYPE_DISTANCE = 0;
    public final static int TERMINATIONTYPE_TIME = 1;
    public final static int TERMINATIONTYPE_STEPS = 2;
    public final static int TERMINATIONTYPE_INTERSECTIONS = 3;

    public final static int COLORBY_ORIGINALVALUE = 0;
    public final static int COLORBY_INPUTORDER = 1;
    public final static int COLORBY_POINTINDEX = 2;
    public final static int COLORBY_PLANE = 3;
    public final static int COLORBY_TOROIDALWINDINGORDER = 4;
    public final static int COLORBY_TOROIDALWINDINGPOINTORDER = 5;
    public final static int COLORBY_TOROIDALWINDINGS = 6;
    public final static int COLORBY_POLOIDALWINDINGS = 7;
    public final static int COLORBY_SAFETYFACTOR = 8;

    public final static int SHOWMESHTYPE_CURVES = 0;
    public final static int SHOWMESHTYPE_SURFACES = 1;

    public final static int OVERLAPTYPE_RAW = 0;
    public final static int OVERLAPTYPE_REMOVE = 1;
    public final static int OVERLAPTYPE_MERGE = 2;
    public final static int OVERLAPTYPE_SMOOTH = 3;

    public final static int INTEGRATIONTYPE_DORMANDPRINCE = 0;
    public final static int INTEGRATIONTYPE_ADAMSBASHFORTH = 1;

    public final static int COLORINGMETHOD_COLORBYSINGLECOLOR = 0;
    public final static int COLORINGMETHOD_COLORBYCOLORTABLE = 1;


    public PoincareAttributes()
    {
        super(numAdditionalAttributes);

        sourceType = SOURCETYPE_SPECIFIEDPOINT;
        maxStepLength = 0.1;
        termination = 10;
        pointSource = new double[3];
        pointSource[0] = 0;
        pointSource[1] = 0;
        pointSource[2] = 0;
        lineStart = new double[3];
        lineStart[0] = 0;
        lineStart[1] = 0;
        lineStart[2] = 0;
        lineEnd = new double[3];
        lineEnd[0] = 1;
        lineEnd[1] = 0;
        lineEnd[2] = 0;
        planeOrigin = new double[3];
        planeOrigin[0] = 0;
        planeOrigin[1] = 0;
        planeOrigin[2] = 0;
        planeNormal = new double[3];
        planeNormal[0] = 0;
        planeNormal[1] = 0;
        planeNormal[2] = 1;
        planeUpAxis = new double[3];
        planeUpAxis[0] = 0;
        planeUpAxis[1] = 1;
        planeUpAxis[2] = 0;
        planeRadius = 1;
        pointDensity = 1;
        colorTableName = new String("Default");
        singleColor = new ColorAttribute(0, 0, 0);
        verboseFlag = true;
        legendFlag = true;
        lightingFlag = true;
        relTol = 0.0001;
        absTol = 1e-05;
        terminationType = TERMINATIONTYPE_STEPS;
        integrationType = INTEGRATIONTYPE_ADAMSBASHFORTH;
        showStreamlines = false;
        showPoints = false;
        numberPlanes = 1;
        colorBy = COLORBY_SAFETYFACTOR;
        maxToroidalWinding = 30;
        overrideToroidalWinding = 0;
        hitRate = 0.9;
        showCurves = SHOWMESHTYPE_CURVES;
        adjustPlane = -1;
        showIslands = false;
        overlaps = OVERLAPTYPE_REMOVE;
        min = 0;
        max = 0;
        minFlag = false;
        maxFlag = false;
        colorType = COLORINGMETHOD_COLORBYSINGLECOLOR;
        intersectPlaneOrigin = new double[3];
        intersectPlaneOrigin[0] = 0;
        intersectPlaneOrigin[1] = 0;
        intersectPlaneOrigin[2] = 0;
        intersectPlaneNormal = new double[3];
        intersectPlaneNormal[0] = 1;
        intersectPlaneNormal[1] = 0;
        intersectPlaneNormal[2] = 0;
    }

    public PoincareAttributes(int nMoreFields)
    {
        super(numAdditionalAttributes + nMoreFields);

        sourceType = SOURCETYPE_SPECIFIEDPOINT;
        maxStepLength = 0.1;
        termination = 10;
        pointSource = new double[3];
        pointSource[0] = 0;
        pointSource[1] = 0;
        pointSource[2] = 0;
        lineStart = new double[3];
        lineStart[0] = 0;
        lineStart[1] = 0;
        lineStart[2] = 0;
        lineEnd = new double[3];
        lineEnd[0] = 1;
        lineEnd[1] = 0;
        lineEnd[2] = 0;
        planeOrigin = new double[3];
        planeOrigin[0] = 0;
        planeOrigin[1] = 0;
        planeOrigin[2] = 0;
        planeNormal = new double[3];
        planeNormal[0] = 0;
        planeNormal[1] = 0;
        planeNormal[2] = 1;
        planeUpAxis = new double[3];
        planeUpAxis[0] = 0;
        planeUpAxis[1] = 1;
        planeUpAxis[2] = 0;
        planeRadius = 1;
        pointDensity = 1;
        colorTableName = new String("Default");
        singleColor = new ColorAttribute(0, 0, 0);
        verboseFlag = true;
        legendFlag = true;
        lightingFlag = true;
        relTol = 0.0001;
        absTol = 1e-05;
        terminationType = TERMINATIONTYPE_STEPS;
        integrationType = INTEGRATIONTYPE_ADAMSBASHFORTH;
        showStreamlines = false;
        showPoints = false;
        numberPlanes = 1;
        colorBy = COLORBY_SAFETYFACTOR;
        maxToroidalWinding = 30;
        overrideToroidalWinding = 0;
        hitRate = 0.9;
        showCurves = SHOWMESHTYPE_CURVES;
        adjustPlane = -1;
        showIslands = false;
        overlaps = OVERLAPTYPE_REMOVE;
        min = 0;
        max = 0;
        minFlag = false;
        maxFlag = false;
        colorType = COLORINGMETHOD_COLORBYSINGLECOLOR;
        intersectPlaneOrigin = new double[3];
        intersectPlaneOrigin[0] = 0;
        intersectPlaneOrigin[1] = 0;
        intersectPlaneOrigin[2] = 0;
        intersectPlaneNormal = new double[3];
        intersectPlaneNormal[0] = 1;
        intersectPlaneNormal[1] = 0;
        intersectPlaneNormal[2] = 0;
    }

    public PoincareAttributes(PoincareAttributes obj)
    {
        super(numAdditionalAttributes);

        int i;

        sourceType = obj.sourceType;
        maxStepLength = obj.maxStepLength;
        termination = obj.termination;
        pointSource = new double[3];
        pointSource[0] = obj.pointSource[0];
        pointSource[1] = obj.pointSource[1];
        pointSource[2] = obj.pointSource[2];

        lineStart = new double[3];
        lineStart[0] = obj.lineStart[0];
        lineStart[1] = obj.lineStart[1];
        lineStart[2] = obj.lineStart[2];

        lineEnd = new double[3];
        lineEnd[0] = obj.lineEnd[0];
        lineEnd[1] = obj.lineEnd[1];
        lineEnd[2] = obj.lineEnd[2];

        planeOrigin = new double[3];
        planeOrigin[0] = obj.planeOrigin[0];
        planeOrigin[1] = obj.planeOrigin[1];
        planeOrigin[2] = obj.planeOrigin[2];

        planeNormal = new double[3];
        planeNormal[0] = obj.planeNormal[0];
        planeNormal[1] = obj.planeNormal[1];
        planeNormal[2] = obj.planeNormal[2];

        planeUpAxis = new double[3];
        planeUpAxis[0] = obj.planeUpAxis[0];
        planeUpAxis[1] = obj.planeUpAxis[1];
        planeUpAxis[2] = obj.planeUpAxis[2];

        planeRadius = obj.planeRadius;
        pointDensity = obj.pointDensity;
        colorTableName = new String(obj.colorTableName);
        singleColor = new ColorAttribute(obj.singleColor);
        verboseFlag = obj.verboseFlag;
        legendFlag = obj.legendFlag;
        lightingFlag = obj.lightingFlag;
        relTol = obj.relTol;
        absTol = obj.absTol;
        terminationType = obj.terminationType;
        integrationType = obj.integrationType;
        showStreamlines = obj.showStreamlines;
        showPoints = obj.showPoints;
        numberPlanes = obj.numberPlanes;
        colorBy = obj.colorBy;
        maxToroidalWinding = obj.maxToroidalWinding;
        overrideToroidalWinding = obj.overrideToroidalWinding;
        hitRate = obj.hitRate;
        showCurves = obj.showCurves;
        adjustPlane = obj.adjustPlane;
        showIslands = obj.showIslands;
        overlaps = obj.overlaps;
        min = obj.min;
        max = obj.max;
        minFlag = obj.minFlag;
        maxFlag = obj.maxFlag;
        colorType = obj.colorType;
        intersectPlaneOrigin = new double[3];
        intersectPlaneOrigin[0] = obj.intersectPlaneOrigin[0];
        intersectPlaneOrigin[1] = obj.intersectPlaneOrigin[1];
        intersectPlaneOrigin[2] = obj.intersectPlaneOrigin[2];

        intersectPlaneNormal = new double[3];
        intersectPlaneNormal[0] = obj.intersectPlaneNormal[0];
        intersectPlaneNormal[1] = obj.intersectPlaneNormal[1];
        intersectPlaneNormal[2] = obj.intersectPlaneNormal[2];


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

    public boolean equals(PoincareAttributes obj)
    {
        int i;

        // Compare the pointSource arrays.
        boolean pointSource_equal = true;
        for(i = 0; i < 3 && pointSource_equal; ++i)
            pointSource_equal = (pointSource[i] == obj.pointSource[i]);

        // Compare the lineStart arrays.
        boolean lineStart_equal = true;
        for(i = 0; i < 3 && lineStart_equal; ++i)
            lineStart_equal = (lineStart[i] == obj.lineStart[i]);

        // Compare the lineEnd arrays.
        boolean lineEnd_equal = true;
        for(i = 0; i < 3 && lineEnd_equal; ++i)
            lineEnd_equal = (lineEnd[i] == obj.lineEnd[i]);

        // Compare the planeOrigin arrays.
        boolean planeOrigin_equal = true;
        for(i = 0; i < 3 && planeOrigin_equal; ++i)
            planeOrigin_equal = (planeOrigin[i] == obj.planeOrigin[i]);

        // Compare the planeNormal arrays.
        boolean planeNormal_equal = true;
        for(i = 0; i < 3 && planeNormal_equal; ++i)
            planeNormal_equal = (planeNormal[i] == obj.planeNormal[i]);

        // Compare the planeUpAxis arrays.
        boolean planeUpAxis_equal = true;
        for(i = 0; i < 3 && planeUpAxis_equal; ++i)
            planeUpAxis_equal = (planeUpAxis[i] == obj.planeUpAxis[i]);

        // Compare the intersectPlaneOrigin arrays.
        boolean intersectPlaneOrigin_equal = true;
        for(i = 0; i < 3 && intersectPlaneOrigin_equal; ++i)
            intersectPlaneOrigin_equal = (intersectPlaneOrigin[i] == obj.intersectPlaneOrigin[i]);

        // Compare the intersectPlaneNormal arrays.
        boolean intersectPlaneNormal_equal = true;
        for(i = 0; i < 3 && intersectPlaneNormal_equal; ++i)
            intersectPlaneNormal_equal = (intersectPlaneNormal[i] == obj.intersectPlaneNormal[i]);

        // Create the return value
        return ((sourceType == obj.sourceType) &&
                (maxStepLength == obj.maxStepLength) &&
                (termination == obj.termination) &&
                pointSource_equal &&
                lineStart_equal &&
                lineEnd_equal &&
                planeOrigin_equal &&
                planeNormal_equal &&
                planeUpAxis_equal &&
                (planeRadius == obj.planeRadius) &&
                (pointDensity == obj.pointDensity) &&
                (colorTableName.equals(obj.colorTableName)) &&
                (singleColor == obj.singleColor) &&
                (verboseFlag == obj.verboseFlag) &&
                (legendFlag == obj.legendFlag) &&
                (lightingFlag == obj.lightingFlag) &&
                (relTol == obj.relTol) &&
                (absTol == obj.absTol) &&
                (terminationType == obj.terminationType) &&
                (integrationType == obj.integrationType) &&
                (showStreamlines == obj.showStreamlines) &&
                (showPoints == obj.showPoints) &&
                (numberPlanes == obj.numberPlanes) &&
                (colorBy == obj.colorBy) &&
                (maxToroidalWinding == obj.maxToroidalWinding) &&
                (overrideToroidalWinding == obj.overrideToroidalWinding) &&
                (hitRate == obj.hitRate) &&
                (showCurves == obj.showCurves) &&
                (adjustPlane == obj.adjustPlane) &&
                (showIslands == obj.showIslands) &&
                (overlaps == obj.overlaps) &&
                (min == obj.min) &&
                (max == obj.max) &&
                (minFlag == obj.minFlag) &&
                (maxFlag == obj.maxFlag) &&
                (colorType == obj.colorType) &&
                intersectPlaneOrigin_equal &&
                intersectPlaneNormal_equal);
    }

    public String GetName() { return "Poincare"; }
    public String GetVersion() { return "2.0"; }

    // Property setting methods
    public void SetSourceType(int sourceType_)
    {
        sourceType = sourceType_;
        Select(0);
    }

    public void SetMaxStepLength(double maxStepLength_)
    {
        maxStepLength = maxStepLength_;
        Select(1);
    }

    public void SetTermination(double termination_)
    {
        termination = termination_;
        Select(2);
    }

    public void SetPointSource(double[] pointSource_)
    {
        pointSource[0] = pointSource_[0];
        pointSource[1] = pointSource_[1];
        pointSource[2] = pointSource_[2];
        Select(3);
    }

    public void SetPointSource(double e0, double e1, double e2)
    {
        pointSource[0] = e0;
        pointSource[1] = e1;
        pointSource[2] = e2;
        Select(3);
    }

    public void SetLineStart(double[] lineStart_)
    {
        lineStart[0] = lineStart_[0];
        lineStart[1] = lineStart_[1];
        lineStart[2] = lineStart_[2];
        Select(4);
    }

    public void SetLineStart(double e0, double e1, double e2)
    {
        lineStart[0] = e0;
        lineStart[1] = e1;
        lineStart[2] = e2;
        Select(4);
    }

    public void SetLineEnd(double[] lineEnd_)
    {
        lineEnd[0] = lineEnd_[0];
        lineEnd[1] = lineEnd_[1];
        lineEnd[2] = lineEnd_[2];
        Select(5);
    }

    public void SetLineEnd(double e0, double e1, double e2)
    {
        lineEnd[0] = e0;
        lineEnd[1] = e1;
        lineEnd[2] = e2;
        Select(5);
    }

    public void SetPlaneOrigin(double[] planeOrigin_)
    {
        planeOrigin[0] = planeOrigin_[0];
        planeOrigin[1] = planeOrigin_[1];
        planeOrigin[2] = planeOrigin_[2];
        Select(6);
    }

    public void SetPlaneOrigin(double e0, double e1, double e2)
    {
        planeOrigin[0] = e0;
        planeOrigin[1] = e1;
        planeOrigin[2] = e2;
        Select(6);
    }

    public void SetPlaneNormal(double[] planeNormal_)
    {
        planeNormal[0] = planeNormal_[0];
        planeNormal[1] = planeNormal_[1];
        planeNormal[2] = planeNormal_[2];
        Select(7);
    }

    public void SetPlaneNormal(double e0, double e1, double e2)
    {
        planeNormal[0] = e0;
        planeNormal[1] = e1;
        planeNormal[2] = e2;
        Select(7);
    }

    public void SetPlaneUpAxis(double[] planeUpAxis_)
    {
        planeUpAxis[0] = planeUpAxis_[0];
        planeUpAxis[1] = planeUpAxis_[1];
        planeUpAxis[2] = planeUpAxis_[2];
        Select(8);
    }

    public void SetPlaneUpAxis(double e0, double e1, double e2)
    {
        planeUpAxis[0] = e0;
        planeUpAxis[1] = e1;
        planeUpAxis[2] = e2;
        Select(8);
    }

    public void SetPlaneRadius(double planeRadius_)
    {
        planeRadius = planeRadius_;
        Select(9);
    }

    public void SetPointDensity(int pointDensity_)
    {
        pointDensity = pointDensity_;
        Select(10);
    }

    public void SetColorTableName(String colorTableName_)
    {
        colorTableName = colorTableName_;
        Select(11);
    }

    public void SetSingleColor(ColorAttribute singleColor_)
    {
        singleColor = singleColor_;
        Select(12);
    }

    public void SetVerboseFlag(boolean verboseFlag_)
    {
        verboseFlag = verboseFlag_;
        Select(13);
    }

    public void SetLegendFlag(boolean legendFlag_)
    {
        legendFlag = legendFlag_;
        Select(14);
    }

    public void SetLightingFlag(boolean lightingFlag_)
    {
        lightingFlag = lightingFlag_;
        Select(15);
    }

    public void SetRelTol(double relTol_)
    {
        relTol = relTol_;
        Select(16);
    }

    public void SetAbsTol(double absTol_)
    {
        absTol = absTol_;
        Select(17);
    }

    public void SetTerminationType(int terminationType_)
    {
        terminationType = terminationType_;
        Select(18);
    }

    public void SetIntegrationType(int integrationType_)
    {
        integrationType = integrationType_;
        Select(19);
    }

    public void SetShowStreamlines(boolean showStreamlines_)
    {
        showStreamlines = showStreamlines_;
        Select(20);
    }

    public void SetShowPoints(boolean showPoints_)
    {
        showPoints = showPoints_;
        Select(21);
    }

    public void SetNumberPlanes(int numberPlanes_)
    {
        numberPlanes = numberPlanes_;
        Select(22);
    }

    public void SetColorBy(int colorBy_)
    {
        colorBy = colorBy_;
        Select(23);
    }

    public void SetMaxToroidalWinding(int maxToroidalWinding_)
    {
        maxToroidalWinding = maxToroidalWinding_;
        Select(24);
    }

    public void SetOverrideToroidalWinding(int overrideToroidalWinding_)
    {
        overrideToroidalWinding = overrideToroidalWinding_;
        Select(25);
    }

    public void SetHitRate(double hitRate_)
    {
        hitRate = hitRate_;
        Select(26);
    }

    public void SetShowCurves(int showCurves_)
    {
        showCurves = showCurves_;
        Select(27);
    }

    public void SetAdjustPlane(int adjustPlane_)
    {
        adjustPlane = adjustPlane_;
        Select(28);
    }

    public void SetShowIslands(boolean showIslands_)
    {
        showIslands = showIslands_;
        Select(29);
    }

    public void SetOverlaps(int overlaps_)
    {
        overlaps = overlaps_;
        Select(30);
    }

    public void SetMin(double min_)
    {
        min = min_;
        Select(31);
    }

    public void SetMax(double max_)
    {
        max = max_;
        Select(32);
    }

    public void SetMinFlag(boolean minFlag_)
    {
        minFlag = minFlag_;
        Select(33);
    }

    public void SetMaxFlag(boolean maxFlag_)
    {
        maxFlag = maxFlag_;
        Select(34);
    }

    public void SetColorType(int colorType_)
    {
        colorType = colorType_;
        Select(35);
    }

    public void SetIntersectPlaneOrigin(double[] intersectPlaneOrigin_)
    {
        intersectPlaneOrigin[0] = intersectPlaneOrigin_[0];
        intersectPlaneOrigin[1] = intersectPlaneOrigin_[1];
        intersectPlaneOrigin[2] = intersectPlaneOrigin_[2];
        Select(36);
    }

    public void SetIntersectPlaneOrigin(double e0, double e1, double e2)
    {
        intersectPlaneOrigin[0] = e0;
        intersectPlaneOrigin[1] = e1;
        intersectPlaneOrigin[2] = e2;
        Select(36);
    }

    public void SetIntersectPlaneNormal(double[] intersectPlaneNormal_)
    {
        intersectPlaneNormal[0] = intersectPlaneNormal_[0];
        intersectPlaneNormal[1] = intersectPlaneNormal_[1];
        intersectPlaneNormal[2] = intersectPlaneNormal_[2];
        Select(37);
    }

    public void SetIntersectPlaneNormal(double e0, double e1, double e2)
    {
        intersectPlaneNormal[0] = e0;
        intersectPlaneNormal[1] = e1;
        intersectPlaneNormal[2] = e2;
        Select(37);
    }

    // Property getting methods
    public int            GetSourceType() { return sourceType; }
    public double         GetMaxStepLength() { return maxStepLength; }
    public double         GetTermination() { return termination; }
    public double[]       GetPointSource() { return pointSource; }
    public double[]       GetLineStart() { return lineStart; }
    public double[]       GetLineEnd() { return lineEnd; }
    public double[]       GetPlaneOrigin() { return planeOrigin; }
    public double[]       GetPlaneNormal() { return planeNormal; }
    public double[]       GetPlaneUpAxis() { return planeUpAxis; }
    public double         GetPlaneRadius() { return planeRadius; }
    public int            GetPointDensity() { return pointDensity; }
    public String         GetColorTableName() { return colorTableName; }
    public ColorAttribute GetSingleColor() { return singleColor; }
    public boolean        GetVerboseFlag() { return verboseFlag; }
    public boolean        GetLegendFlag() { return legendFlag; }
    public boolean        GetLightingFlag() { return lightingFlag; }
    public double         GetRelTol() { return relTol; }
    public double         GetAbsTol() { return absTol; }
    public int            GetTerminationType() { return terminationType; }
    public int            GetIntegrationType() { return integrationType; }
    public boolean        GetShowStreamlines() { return showStreamlines; }
    public boolean        GetShowPoints() { return showPoints; }
    public int            GetNumberPlanes() { return numberPlanes; }
    public int            GetColorBy() { return colorBy; }
    public int            GetMaxToroidalWinding() { return maxToroidalWinding; }
    public int            GetOverrideToroidalWinding() { return overrideToroidalWinding; }
    public double         GetHitRate() { return hitRate; }
    public int            GetShowCurves() { return showCurves; }
    public int            GetAdjustPlane() { return adjustPlane; }
    public boolean        GetShowIslands() { return showIslands; }
    public int            GetOverlaps() { return overlaps; }
    public double         GetMin() { return min; }
    public double         GetMax() { return max; }
    public boolean        GetMinFlag() { return minFlag; }
    public boolean        GetMaxFlag() { return maxFlag; }
    public int            GetColorType() { return colorType; }
    public double[]       GetIntersectPlaneOrigin() { return intersectPlaneOrigin; }
    public double[]       GetIntersectPlaneNormal() { return intersectPlaneNormal; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(sourceType);
        if(WriteSelect(1, buf))
            buf.WriteDouble(maxStepLength);
        if(WriteSelect(2, buf))
            buf.WriteDouble(termination);
        if(WriteSelect(3, buf))
            buf.WriteDoubleArray(pointSource);
        if(WriteSelect(4, buf))
            buf.WriteDoubleArray(lineStart);
        if(WriteSelect(5, buf))
            buf.WriteDoubleArray(lineEnd);
        if(WriteSelect(6, buf))
            buf.WriteDoubleArray(planeOrigin);
        if(WriteSelect(7, buf))
            buf.WriteDoubleArray(planeNormal);
        if(WriteSelect(8, buf))
            buf.WriteDoubleArray(planeUpAxis);
        if(WriteSelect(9, buf))
            buf.WriteDouble(planeRadius);
        if(WriteSelect(10, buf))
            buf.WriteInt(pointDensity);
        if(WriteSelect(11, buf))
            buf.WriteString(colorTableName);
        if(WriteSelect(12, buf))
            singleColor.Write(buf);
        if(WriteSelect(13, buf))
            buf.WriteBool(verboseFlag);
        if(WriteSelect(14, buf))
            buf.WriteBool(legendFlag);
        if(WriteSelect(15, buf))
            buf.WriteBool(lightingFlag);
        if(WriteSelect(16, buf))
            buf.WriteDouble(relTol);
        if(WriteSelect(17, buf))
            buf.WriteDouble(absTol);
        if(WriteSelect(18, buf))
            buf.WriteInt(terminationType);
        if(WriteSelect(19, buf))
            buf.WriteInt(integrationType);
        if(WriteSelect(20, buf))
            buf.WriteBool(showStreamlines);
        if(WriteSelect(21, buf))
            buf.WriteBool(showPoints);
        if(WriteSelect(22, buf))
            buf.WriteInt(numberPlanes);
        if(WriteSelect(23, buf))
            buf.WriteInt(colorBy);
        if(WriteSelect(24, buf))
            buf.WriteInt(maxToroidalWinding);
        if(WriteSelect(25, buf))
            buf.WriteInt(overrideToroidalWinding);
        if(WriteSelect(26, buf))
            buf.WriteDouble(hitRate);
        if(WriteSelect(27, buf))
            buf.WriteInt(showCurves);
        if(WriteSelect(28, buf))
            buf.WriteInt(adjustPlane);
        if(WriteSelect(29, buf))
            buf.WriteBool(showIslands);
        if(WriteSelect(30, buf))
            buf.WriteInt(overlaps);
        if(WriteSelect(31, buf))
            buf.WriteDouble(min);
        if(WriteSelect(32, buf))
            buf.WriteDouble(max);
        if(WriteSelect(33, buf))
            buf.WriteBool(minFlag);
        if(WriteSelect(34, buf))
            buf.WriteBool(maxFlag);
        if(WriteSelect(35, buf))
            buf.WriteInt(colorType);
        if(WriteSelect(36, buf))
            buf.WriteDoubleArray(intersectPlaneOrigin);
        if(WriteSelect(37, buf))
            buf.WriteDoubleArray(intersectPlaneNormal);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetSourceType(buf.ReadInt());
            break;
        case 1:
            SetMaxStepLength(buf.ReadDouble());
            break;
        case 2:
            SetTermination(buf.ReadDouble());
            break;
        case 3:
            SetPointSource(buf.ReadDoubleArray());
            break;
        case 4:
            SetLineStart(buf.ReadDoubleArray());
            break;
        case 5:
            SetLineEnd(buf.ReadDoubleArray());
            break;
        case 6:
            SetPlaneOrigin(buf.ReadDoubleArray());
            break;
        case 7:
            SetPlaneNormal(buf.ReadDoubleArray());
            break;
        case 8:
            SetPlaneUpAxis(buf.ReadDoubleArray());
            break;
        case 9:
            SetPlaneRadius(buf.ReadDouble());
            break;
        case 10:
            SetPointDensity(buf.ReadInt());
            break;
        case 11:
            SetColorTableName(buf.ReadString());
            break;
        case 12:
            singleColor.Read(buf);
            Select(12);
            break;
        case 13:
            SetVerboseFlag(buf.ReadBool());
            break;
        case 14:
            SetLegendFlag(buf.ReadBool());
            break;
        case 15:
            SetLightingFlag(buf.ReadBool());
            break;
        case 16:
            SetRelTol(buf.ReadDouble());
            break;
        case 17:
            SetAbsTol(buf.ReadDouble());
            break;
        case 18:
            SetTerminationType(buf.ReadInt());
            break;
        case 19:
            SetIntegrationType(buf.ReadInt());
            break;
        case 20:
            SetShowStreamlines(buf.ReadBool());
            break;
        case 21:
            SetShowPoints(buf.ReadBool());
            break;
        case 22:
            SetNumberPlanes(buf.ReadInt());
            break;
        case 23:
            SetColorBy(buf.ReadInt());
            break;
        case 24:
            SetMaxToroidalWinding(buf.ReadInt());
            break;
        case 25:
            SetOverrideToroidalWinding(buf.ReadInt());
            break;
        case 26:
            SetHitRate(buf.ReadDouble());
            break;
        case 27:
            SetShowCurves(buf.ReadInt());
            break;
        case 28:
            SetAdjustPlane(buf.ReadInt());
            break;
        case 29:
            SetShowIslands(buf.ReadBool());
            break;
        case 30:
            SetOverlaps(buf.ReadInt());
            break;
        case 31:
            SetMin(buf.ReadDouble());
            break;
        case 32:
            SetMax(buf.ReadDouble());
            break;
        case 33:
            SetMinFlag(buf.ReadBool());
            break;
        case 34:
            SetMaxFlag(buf.ReadBool());
            break;
        case 35:
            SetColorType(buf.ReadInt());
            break;
        case 36:
            SetIntersectPlaneOrigin(buf.ReadDoubleArray());
            break;
        case 37:
            SetIntersectPlaneNormal(buf.ReadDoubleArray());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "sourceType = ";
        if(sourceType == SOURCETYPE_SPECIFIEDPOINT)
            str = str + "SOURCETYPE_SPECIFIEDPOINT";
        if(sourceType == SOURCETYPE_SPECIFIEDLINE)
            str = str + "SOURCETYPE_SPECIFIEDLINE";
        if(sourceType == SOURCETYPE_SPECIFIEDPLANE)
            str = str + "SOURCETYPE_SPECIFIEDPLANE";
        str = str + "\n";
        str = str + doubleToString("maxStepLength", maxStepLength, indent) + "\n";
        str = str + doubleToString("termination", termination, indent) + "\n";
        str = str + doubleArrayToString("pointSource", pointSource, indent) + "\n";
        str = str + doubleArrayToString("lineStart", lineStart, indent) + "\n";
        str = str + doubleArrayToString("lineEnd", lineEnd, indent) + "\n";
        str = str + doubleArrayToString("planeOrigin", planeOrigin, indent) + "\n";
        str = str + doubleArrayToString("planeNormal", planeNormal, indent) + "\n";
        str = str + doubleArrayToString("planeUpAxis", planeUpAxis, indent) + "\n";
        str = str + doubleToString("planeRadius", planeRadius, indent) + "\n";
        str = str + intToString("pointDensity", pointDensity, indent) + "\n";
        str = str + stringToString("colorTableName", colorTableName, indent) + "\n";
        str = str + indent + "singleColor = {" + singleColor.Red() + ", " + singleColor.Green() + ", " + singleColor.Blue() + ", " + singleColor.Alpha() + "}\n";
        str = str + boolToString("verboseFlag", verboseFlag, indent) + "\n";
        str = str + boolToString("legendFlag", legendFlag, indent) + "\n";
        str = str + boolToString("lightingFlag", lightingFlag, indent) + "\n";
        str = str + doubleToString("relTol", relTol, indent) + "\n";
        str = str + doubleToString("absTol", absTol, indent) + "\n";
        str = str + indent + "terminationType = ";
        if(terminationType == TERMINATIONTYPE_DISTANCE)
            str = str + "TERMINATIONTYPE_DISTANCE";
        if(terminationType == TERMINATIONTYPE_TIME)
            str = str + "TERMINATIONTYPE_TIME";
        if(terminationType == TERMINATIONTYPE_STEPS)
            str = str + "TERMINATIONTYPE_STEPS";
        if(terminationType == TERMINATIONTYPE_INTERSECTIONS)
            str = str + "TERMINATIONTYPE_INTERSECTIONS";
        str = str + "\n";
        str = str + indent + "integrationType = ";
        if(integrationType == INTEGRATIONTYPE_DORMANDPRINCE)
            str = str + "INTEGRATIONTYPE_DORMANDPRINCE";
        if(integrationType == INTEGRATIONTYPE_ADAMSBASHFORTH)
            str = str + "INTEGRATIONTYPE_ADAMSBASHFORTH";
        str = str + "\n";
        str = str + boolToString("showStreamlines", showStreamlines, indent) + "\n";
        str = str + boolToString("showPoints", showPoints, indent) + "\n";
        str = str + intToString("numberPlanes", numberPlanes, indent) + "\n";
        str = str + indent + "colorBy = ";
        if(colorBy == COLORBY_ORIGINALVALUE)
            str = str + "COLORBY_ORIGINALVALUE";
        if(colorBy == COLORBY_INPUTORDER)
            str = str + "COLORBY_INPUTORDER";
        if(colorBy == COLORBY_POINTINDEX)
            str = str + "COLORBY_POINTINDEX";
        if(colorBy == COLORBY_PLANE)
            str = str + "COLORBY_PLANE";
        if(colorBy == COLORBY_TOROIDALWINDINGORDER)
            str = str + "COLORBY_TOROIDALWINDINGORDER";
        if(colorBy == COLORBY_TOROIDALWINDINGPOINTORDER)
            str = str + "COLORBY_TOROIDALWINDINGPOINTORDER";
        if(colorBy == COLORBY_TOROIDALWINDINGS)
            str = str + "COLORBY_TOROIDALWINDINGS";
        if(colorBy == COLORBY_POLOIDALWINDINGS)
            str = str + "COLORBY_POLOIDALWINDINGS";
        if(colorBy == COLORBY_SAFETYFACTOR)
            str = str + "COLORBY_SAFETYFACTOR";
        str = str + "\n";
        str = str + intToString("maxToroidalWinding", maxToroidalWinding, indent) + "\n";
        str = str + intToString("overrideToroidalWinding", overrideToroidalWinding, indent) + "\n";
        str = str + doubleToString("hitRate", hitRate, indent) + "\n";
        str = str + indent + "showCurves = ";
        if(showCurves == SHOWMESHTYPE_CURVES)
            str = str + "SHOWMESHTYPE_CURVES";
        if(showCurves == SHOWMESHTYPE_SURFACES)
            str = str + "SHOWMESHTYPE_SURFACES";
        str = str + "\n";
        str = str + intToString("adjustPlane", adjustPlane, indent) + "\n";
        str = str + boolToString("showIslands", showIslands, indent) + "\n";
        str = str + indent + "overlaps = ";
        if(overlaps == OVERLAPTYPE_RAW)
            str = str + "OVERLAPTYPE_RAW";
        if(overlaps == OVERLAPTYPE_REMOVE)
            str = str + "OVERLAPTYPE_REMOVE";
        if(overlaps == OVERLAPTYPE_MERGE)
            str = str + "OVERLAPTYPE_MERGE";
        if(overlaps == OVERLAPTYPE_SMOOTH)
            str = str + "OVERLAPTYPE_SMOOTH";
        str = str + "\n";
        str = str + doubleToString("min", min, indent) + "\n";
        str = str + doubleToString("max", max, indent) + "\n";
        str = str + boolToString("minFlag", minFlag, indent) + "\n";
        str = str + boolToString("maxFlag", maxFlag, indent) + "\n";
        str = str + indent + "colorType = ";
        if(colorType == COLORINGMETHOD_COLORBYSINGLECOLOR)
            str = str + "COLORINGMETHOD_COLORBYSINGLECOLOR";
        if(colorType == COLORINGMETHOD_COLORBYCOLORTABLE)
            str = str + "COLORINGMETHOD_COLORBYCOLORTABLE";
        str = str + "\n";
        str = str + doubleArrayToString("intersectPlaneOrigin", intersectPlaneOrigin, indent) + "\n";
        str = str + doubleArrayToString("intersectPlaneNormal", intersectPlaneNormal, indent) + "\n";
        return str;
    }


    // Attributes
    private int            sourceType;
    private double         maxStepLength;
    private double         termination;
    private double[]       pointSource;
    private double[]       lineStart;
    private double[]       lineEnd;
    private double[]       planeOrigin;
    private double[]       planeNormal;
    private double[]       planeUpAxis;
    private double         planeRadius;
    private int            pointDensity;
    private String         colorTableName;
    private ColorAttribute singleColor;
    private boolean        verboseFlag;
    private boolean        legendFlag;
    private boolean        lightingFlag;
    private double         relTol;
    private double         absTol;
    private int            terminationType;
    private int            integrationType;
    private boolean        showStreamlines;
    private boolean        showPoints;
    private int            numberPlanes;
    private int            colorBy;
    private int            maxToroidalWinding;
    private int            overrideToroidalWinding;
    private double         hitRate;
    private int            showCurves;
    private int            adjustPlane;
    private boolean        showIslands;
    private int            overlaps;
    private double         min;
    private double         max;
    private boolean        minFlag;
    private boolean        maxFlag;
    private int            colorType;
    private double[]       intersectPlaneOrigin;
    private double[]       intersectPlaneNormal;
}

