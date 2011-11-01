// ***************************************************************************
//
// Copyright (c) 2000 - 2011, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
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
// Class: ColorAttributeList
//
// Purpose:
//    This class contains a list of ColorAttributes.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class ColorAttributeList extends AttributeSubject
{
    private static int ColorAttributeList_numAdditionalAtts = 1;

    public ColorAttributeList()
    {
        super(ColorAttributeList_numAdditionalAtts);

        colors = new Vector();
    }

    public ColorAttributeList(int nMoreFields)
    {
        super(ColorAttributeList_numAdditionalAtts + nMoreFields);

        colors = new Vector();
    }

    public ColorAttributeList(ColorAttributeList obj)
    {
        super(ColorAttributeList_numAdditionalAtts);

        int i;

        // *** Copy the colors field ***
        colors = new Vector(obj.colors.size());
        for(i = 0; i < obj.colors.size(); ++i)
        {
            ColorAttribute oldObj = (ColorAttribute)obj.colors.elementAt(i);
            colors.addElement(new ColorAttribute(oldObj));
        }


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return ColorAttributeList_numAdditionalAtts;
    }

    public boolean equals(ColorAttributeList obj)
    {
        int i;

        // Compare the elements in the colors vector.
        boolean colors_equal = (obj.colors.size() == colors.size());
        for(i = 0; (i < colors.size()) && colors_equal; ++i)
        {
            // Make references to ColorAttribute from Object.
            ColorAttribute colors1 = (ColorAttribute)colors.elementAt(i);
            ColorAttribute colors2 = (ColorAttribute)obj.colors.elementAt(i);
            colors_equal = colors1.equals(colors2);
        }
        // Create the return value
        return (colors_equal);
    }

    // Property setting methods
    // Property getting methods
    public Vector GetColors() { return colors; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
        {
            buf.WriteInt(colors.size());
            for(int i = 0; i < colors.size(); ++i)
            {
                ColorAttribute tmp = (ColorAttribute)colors.elementAt(i);
                tmp.Write(buf);
            }
        }
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        {
            int len = buf.ReadInt();
            colors.clear();
            for(int j = 0; j < len; ++j)
            {
                ColorAttribute tmp = new ColorAttribute();
                tmp.Read(buf);
                colors.addElement(tmp);
            }
        }
        Select(0);
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "colors = {\n";
        for(int i = 0; i < colors.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)colors.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < colors.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddColors(ColorAttribute obj)
    {
        colors.addElement(new ColorAttribute(obj));
        Select(0);
    }

    public void ClearColors()
    {
        colors.clear();
        Select(0);
    }

    public void RemoveColors(int index)
    {
        if(index >= 0 && index < colors.size())
        {
            colors.remove(index);
            Select(0);
        }
    }

    public int GetNumColors()
    {
        return colors.size();
    }

    public ColorAttribute GetColors(int i)
    {
        ColorAttribute tmp = (ColorAttribute)colors.elementAt(i);
        return tmp;
    }


    // Attributes
    private Vector colors; // vector of ColorAttribute objects
}

