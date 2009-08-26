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

package llnl.visit;

import java.util.Vector;

// ****************************************************************************
// Class: AnnotationObjectList
//
// Purpose:
//    Contains a list of AnnotationObjectAttributes
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class AnnotationObjectList extends AttributeSubject
{
    private static int numAdditionalAttributes = 1;

    public AnnotationObjectList()
    {
        super(numAdditionalAttributes);

        annotation = new Vector();
    }

    public AnnotationObjectList(int nMoreFields)
    {
        super(numAdditionalAttributes + nMoreFields);

        annotation = new Vector();
    }

    public AnnotationObjectList(AnnotationObjectList obj)
    {
        super(numAdditionalAttributes);

        int i;

        // *** Copy the annotation field ***
        annotation = new Vector(obj.annotation.size());
        for(i = 0; i < obj.annotation.size(); ++i)
        {
            AnnotationObject newObj = (AnnotationObject)annotation.elementAt(i);
            annotation.addElement(new AnnotationObject(newObj));
        }


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

    public boolean equals(AnnotationObjectList obj)
    {
        int i;

        // Compare the elements in the annotation vector.
        boolean annotation_equal = (obj.annotation.size() == annotation.size());
        for(i = 0; (i < annotation.size()) && annotation_equal; ++i)
        {
            // Make references to AnnotationObject from Object.
            AnnotationObject annotation1 = (AnnotationObject)annotation.elementAt(i);
            AnnotationObject annotation2 = (AnnotationObject)obj.annotation.elementAt(i);
            annotation_equal = annotation1.equals(annotation2);
        }
        // Create the return value
        return (annotation_equal);
    }

    // Property setting methods
    // Property getting methods
    public Vector GetAnnotation() { return annotation; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
        {
            buf.WriteInt(annotation.size());
            for(int i = 0; i < annotation.size(); ++i)
            {
                AnnotationObject tmp = (AnnotationObject)annotation.elementAt(i);
                tmp.Write(buf);
            }
        }
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        {
            int len = buf.ReadInt();
            annotation.clear();
            for(int j = 0; j < len; ++j)
            {
                AnnotationObject tmp = new AnnotationObject();
                tmp.Read(buf);
                annotation.addElement(tmp);
            }
        }
        Select(0);
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "annotation = {\n";
        for(int i = 0; i < annotation.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)annotation.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < annotation.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddAnnotation(AnnotationObject obj)
    {
        annotation.addElement(new AnnotationObject(obj));
        Select(0);
    }

    public void ClearAnnotations()
    {
        annotation.clear();
        Select(0);
    }

    public void RemoveAnnotation(int index)
    {
        if(index >= 0 && index < annotation.size())
        {
            annotation.remove(index);
            Select(0);
        }
    }

    public int GetNumAnnotations()
    {
        return annotation.size();
    }

    public AnnotationObject GetAnnotation(int i)
    {
        AnnotationObject tmp = (AnnotationObject)annotation.elementAt(i);
        return tmp;
    }


    /**
     * Returned the annotation object with the specified name
     *
     * @param name Name of the annotation object we want to return.
     * @return The named annotationn object or null.
     */
    public AnnotationObject GetAnnotation(String name)
    {
        for(int i = 0; i < annotation.size(); ++i)
        {
            AnnotationObject a = (AnnotationObject)annotation.elementAt(i);
            if(a.GetObjectName().equals(name))
                return a;
        }
        return null;
    }

    /**
     * Sets the options for the named time slider annotation object.
     *
     * @param annotName Name of the time slider annotation that we want to modify.
     * @param x X location of the lower left corner in the visualization window [0.,1.]
     * @param y Y location of the lower left corner in the visualization window [0.,1.]
     * @param width Width of the annotation [0.,1.]
     * @param height Height of the annotation [0.,1.]
     * @param label Label to be used in the time slider
     * @param timeFormat C-style format string for the time number, such as "%1.3f"
     * @param startColor Color used for the left progress part of the time slider.
     * @param endColor Color used for the right part of the time slider progress.
     * @param textColor Color used for the text if we're not using the fg color.
     * @param useForegroundColor True to use the foreground color as the text color
     * @param timeDisplay 0=All frames, 1=Frames for plot, 2=States for plot
     * @param visible Whether the annotation is visible.
     * @param rounded Whether the ends of the progress bar are rounded
     * @param shaded Whether the progress bar is shaded 
     */
    public void SetTimeSliderOptions(String annotName, 
        double x, double y, double width, double height,
        String label, String timeFormat, 
        ColorAttribute startColor, ColorAttribute endColor, 
        ColorAttribute textColor, boolean useForegroundColor, 
        int timeDisplay,
        boolean visible, boolean rounded, boolean shaded)
    {
        AnnotationObject annot = GetAnnotation(annotName);
        if(annot != null)
        {
            annot.SetPosition(x, y, 0.);
            annot.SetPosition2(width, height, 0.);
            Vector sArgs = new Vector();
            sArgs.addElement(new String(label));
            sArgs.addElement(new String(timeFormat));
            annot.SetText(sArgs);
            annot.SetColor1(startColor);
            annot.SetColor2(endColor);
            annot.SetTextColor(textColor);
            annot.SetUseForegroundForTextColor(useForegroundColor);
            annot.SetVisible(visible);
            int flags = (timeDisplay << 2) | (shaded ? 2 : 0) | (rounded ? 1 : 0);
            annot.SetIntAttribute1(flags);
        }
    }

    /**
     * Sets the options for the named 2D text annotation object.
     *
     * @param annotName Name of the text annotation that we want to modify.
     * @param x X location of the lower left corner in the visualization window [0.,1.]
     * @param y Y location of the lower left corner in the visualization window [0.,1.]
     * @param width Width of the annotation [0.,1.]
     * @param text Text to be displayed
     * @param textColor Color used for the text if we're not using the fg color.
     * @param useForegroundColor True to use the foreground color as the text color
     * @param fontFamily 0=Arial, 1=Courier, 2=Times
     * @param bold Whether the font is bold
     * @param italic Whether the font is italic
     * @param shadow Whether the font has a shadow.
     * @param visible Whether the annotation is visible.
     */
    public void SetText2DOptions(String annotName, 
        double x, double y, double width,
        String text, 
        ColorAttribute textColor, boolean useForegroundColor, 
        int fontFamily, boolean bold, boolean italic, boolean shadow,
        boolean visible)
    {
        AnnotationObject annot = GetAnnotation(annotName);
        if(annot != null)
        {
            annot.SetPosition(x, y, 0.);
            annot.SetPosition2(width, annot.GetPosition2()[1], annot.GetPosition2()[2]);
            Vector sArgs = new Vector();
            sArgs.addElement(new String(text));
            annot.SetText(sArgs);
            annot.SetTextColor(textColor);
            annot.SetUseForegroundForTextColor(useForegroundColor);
            annot.SetFontFamily(fontFamily);
            annot.SetFontBold(bold);
            annot.SetFontItalic(italic);
            annot.SetFontShadow(shadow);
            annot.SetVisible(visible);
        }
    }

    /**
     * Sets the options for the named 3D text annotation object.
     *
     * @param annotName Name of the text annotation that we want to modify.
     * @param x X location of the text
     * @param y Y location of the text
     * @param z Z location of the text
     * @param text Text to be displayed
     * @param heightMode 0=relative, 1=fixed
     * @param fixedHeight Height to use when heightMode==0
     * @param relativeHeight Height to use when heightMode==1. Percent of original height [1,100]
     * @param facesCamera Whether the text should face the camera.
     * @param rotX X rotation in degrees.
     * @param rotY Y rotation in degrees.
     * @param rotZ Z rotation in degrees.
     * @param textColor Color used for the text if we're not using the fg color.
     * @param useForegroundColor True to use the foreground color as the text color
     * @param visible Whether the annotation is visible.
     */
    public void SetText3DOptions(String annotName, 
        double x, double y, double z,
        String text,
        boolean heightMode, double fixedHeight, int relativeHeight,
        boolean facesCamera,
        double rotX, double rotY, double rotZ,
        ColorAttribute textColor, boolean useForegroundColor, 
        boolean visible)
    {
        AnnotationObject annot = GetAnnotation(annotName);
        if(annot != null)
        {
            annot.SetPosition(x, y, z);
            annot.SetPosition2(rotX, rotY, rotZ);
            Vector sArgs = new Vector();
            sArgs.addElement(new String(text));
            annot.SetText(sArgs);
            annot.SetTextColor(textColor);
            annot.SetUseForegroundForTextColor(useForegroundColor);
            annot.SetIntAttribute1(relativeHeight);
            annot.SetDoubleAttribute1(fixedHeight);
            annot.SetFontItalic(heightMode);
            annot.SetFontBold(facesCamera);
            annot.SetVisible(visible);
        }
    }

    /**
     * Sets the options for the named 2D line annotation object.
     *
     * @param annotName Name of the text annotation that we want to modify.
     * @param x0 X location of the start point in the visualization window [0.,1.]
     * @param y0 Y location of the start point in the visualization window [0.,1.]
     * @param x1 X location of the end point in the visualization window [0.,1.]
     * @param y1 Y location of the end point in the visualization window [0.,1.]
     * @param lineWidth Width of the line.
     * @param startArrow 0=None, 1=Line, 2=Solid
     * @param endArrow 0=None, 1=Line, 2=Solid
     * @param color Color used for the line if we're not using the fg color.
     * @param useForegroundColor True to use the foreground color as the text color
     * @param visible Whether the annotation is visible.
     */
    public void SetLine2DOptions(String annotName, 
        double x0, double y0, double x1, double y1,
        int lineWidth,
        int startArrow, int endArrow,
        ColorAttribute color, boolean useForegroundColor, 
        boolean visible)
    {
        AnnotationObject annot = GetAnnotation(annotName);
        if(annot != null)
        {
            annot.SetPosition(x0, y0, 0.);
            annot.SetPosition2(x1, y1, 0.);
            annot.SetColor1(color);
            annot.SetColor2(new ColorAttribute(lineWidth, startArrow, endArrow, 255));
            annot.SetUseForegroundForTextColor(useForegroundColor);
            annot.SetVisible(visible);
        }
    }

    /**
     * Sets the options for the named image annotation object.
     *
     * @param annotName Name of the text annotation that we want to modify.
     * @param filename Filename that contains the image.
     * @param x X location of the start point in the visualization window [0.,1.]
     * @param y Y location of the start point in the visualization window [0.,1.]
     * @param xScale X scale.
     * @param yScale Y scale.
     * @param scalesLinked Keeps the scales linked.
     * @param transColor The color to remove from the image so it becomes clear.
     * @param removeTransColor Tells VisIt to remove the transparent color.
     * @param opacity Overal opacity of the image.
     * @param visible Whether the annotation is visible.
     */
    public void SetImageOptions(String annotName, 
        String filename,
        double x, double y,
        double xScale, double yScale, boolean scalesLinked,
        ColorAttribute transColor, boolean removeTransColor, 
        double opacity,
        boolean visible)
    {
        AnnotationObject annot = GetAnnotation(annotName);
        if(annot != null)
        {
            Vector sArgs = new Vector();
            sArgs.addElement(new String(filename));
            annot.SetText(sArgs);
            annot.SetPosition(x, y, 0.);
            annot.SetPosition2(xScale * 100., yScale * 100., 0.);
            ColorAttribute c = new ColorAttribute(
                transColor.Red(), 
                transColor.Green(), 
                transColor.Blue(),
                (int)(opacity * 255.));
            annot.SetColor1(c);
            annot.SetFontShadow(scalesLinked);
            annot.SetIntAttribute1(removeTransColor?1:0);
            annot.SetVisible(visible);
        }
    }

    // Attributes
    private Vector annotation; // vector of AnnotationObject objects
}

