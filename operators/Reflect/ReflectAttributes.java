// ***************************************************************************
//
// Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: ReflectAttributes
//
// Purpose:
//    This class contains attributes for the reflect operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class ReflectAttributes extends AttributeSubject implements Plugin
{
    private static int ReflectAttributes_numAdditionalAtts = 8;

    // Enum values
    public final static int OCTANT_PXPYPZ = 0;
    public final static int OCTANT_NXPYPZ = 1;
    public final static int OCTANT_PXNYPZ = 2;
    public final static int OCTANT_NXNYPZ = 3;
    public final static int OCTANT_PXPYNZ = 4;
    public final static int OCTANT_NXPYNZ = 5;
    public final static int OCTANT_PXNYNZ = 6;
    public final static int OCTANT_NXNYNZ = 7;


    public ReflectAttributes()
    {
        super(ReflectAttributes_numAdditionalAtts);

        octant = OCTANT_PXPYPZ;
        useXBoundary = true;
        specifiedX = 0;
        useYBoundary = true;
        specifiedY = 0;
        useZBoundary = true;
        specifiedZ = 0;
        reflections = new int[8];
        reflections[0] = 1;
        reflections[1] = 0;
        reflections[2] = 1;
        reflections[3] = 0;
        reflections[4] = 0;
        reflections[5] = 0;
        reflections[6] = 0;
        reflections[7] = 0;
    }

    public ReflectAttributes(int nMoreFields)
    {
        super(ReflectAttributes_numAdditionalAtts + nMoreFields);

        octant = OCTANT_PXPYPZ;
        useXBoundary = true;
        specifiedX = 0;
        useYBoundary = true;
        specifiedY = 0;
        useZBoundary = true;
        specifiedZ = 0;
        reflections = new int[8];
        reflections[0] = 1;
        reflections[1] = 0;
        reflections[2] = 1;
        reflections[3] = 0;
        reflections[4] = 0;
        reflections[5] = 0;
        reflections[6] = 0;
        reflections[7] = 0;
    }

    public ReflectAttributes(ReflectAttributes obj)
    {
        super(obj);

        int i;

        octant = obj.octant;
        useXBoundary = obj.useXBoundary;
        specifiedX = obj.specifiedX;
        useYBoundary = obj.useYBoundary;
        specifiedY = obj.specifiedY;
        useZBoundary = obj.useZBoundary;
        specifiedZ = obj.specifiedZ;
        reflections = new int[8];
        for(i = 0; i < obj.reflections.length; ++i)
            reflections[i] = obj.reflections[i];


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return ReflectAttributes_numAdditionalAtts;
    }

    public boolean equals(ReflectAttributes obj)
    {
        int i;

        // Compare the reflections arrays.
        boolean reflections_equal = true;
        for(i = 0; i < 8 && reflections_equal; ++i)
            reflections_equal = (reflections[i] == obj.reflections[i]);

        // Create the return value
        return ((octant == obj.octant) &&
                (useXBoundary == obj.useXBoundary) &&
                (specifiedX == obj.specifiedX) &&
                (useYBoundary == obj.useYBoundary) &&
                (specifiedY == obj.specifiedY) &&
                (useZBoundary == obj.useZBoundary) &&
                (specifiedZ == obj.specifiedZ) &&
                reflections_equal);
    }

    public String GetName() { return "Reflect"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetOctant(int octant_)
    {
        octant = octant_;
        Select(0);
    }

    public void SetUseXBoundary(boolean useXBoundary_)
    {
        useXBoundary = useXBoundary_;
        Select(1);
    }

    public void SetSpecifiedX(double specifiedX_)
    {
        specifiedX = specifiedX_;
        Select(2);
    }

    public void SetUseYBoundary(boolean useYBoundary_)
    {
        useYBoundary = useYBoundary_;
        Select(3);
    }

    public void SetSpecifiedY(double specifiedY_)
    {
        specifiedY = specifiedY_;
        Select(4);
    }

    public void SetUseZBoundary(boolean useZBoundary_)
    {
        useZBoundary = useZBoundary_;
        Select(5);
    }

    public void SetSpecifiedZ(double specifiedZ_)
    {
        specifiedZ = specifiedZ_;
        Select(6);
    }

    public void SetReflections(int[] reflections_)
    {
        for(int i = 0; i < 8; ++i)
             reflections[i] = reflections_[i];
        Select(7);
    }

    // Property getting methods
    public int     GetOctant() { return octant; }
    public boolean GetUseXBoundary() { return useXBoundary; }
    public double  GetSpecifiedX() { return specifiedX; }
    public boolean GetUseYBoundary() { return useYBoundary; }
    public double  GetSpecifiedY() { return specifiedY; }
    public boolean GetUseZBoundary() { return useZBoundary; }
    public double  GetSpecifiedZ() { return specifiedZ; }
    public int[]   GetReflections() { return reflections; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(octant);
        if(WriteSelect(1, buf))
            buf.WriteBool(useXBoundary);
        if(WriteSelect(2, buf))
            buf.WriteDouble(specifiedX);
        if(WriteSelect(3, buf))
            buf.WriteBool(useYBoundary);
        if(WriteSelect(4, buf))
            buf.WriteDouble(specifiedY);
        if(WriteSelect(5, buf))
            buf.WriteBool(useZBoundary);
        if(WriteSelect(6, buf))
            buf.WriteDouble(specifiedZ);
        if(WriteSelect(7, buf))
            buf.WriteIntArray(reflections);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetOctant(buf.ReadInt());
            break;
        case 1:
            SetUseXBoundary(buf.ReadBool());
            break;
        case 2:
            SetSpecifiedX(buf.ReadDouble());
            break;
        case 3:
            SetUseYBoundary(buf.ReadBool());
            break;
        case 4:
            SetSpecifiedY(buf.ReadDouble());
            break;
        case 5:
            SetUseZBoundary(buf.ReadBool());
            break;
        case 6:
            SetSpecifiedZ(buf.ReadDouble());
            break;
        case 7:
            SetReflections(buf.ReadIntArray());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "octant = ";
        if(octant == OCTANT_PXPYPZ)
            str = str + "OCTANT_PXPYPZ";
        if(octant == OCTANT_NXPYPZ)
            str = str + "OCTANT_NXPYPZ";
        if(octant == OCTANT_PXNYPZ)
            str = str + "OCTANT_PXNYPZ";
        if(octant == OCTANT_NXNYPZ)
            str = str + "OCTANT_NXNYPZ";
        if(octant == OCTANT_PXPYNZ)
            str = str + "OCTANT_PXPYNZ";
        if(octant == OCTANT_NXPYNZ)
            str = str + "OCTANT_NXPYNZ";
        if(octant == OCTANT_PXNYNZ)
            str = str + "OCTANT_PXNYNZ";
        if(octant == OCTANT_NXNYNZ)
            str = str + "OCTANT_NXNYNZ";
        str = str + "\n";
        str = str + boolToString("useXBoundary", useXBoundary, indent) + "\n";
        str = str + doubleToString("specifiedX", specifiedX, indent) + "\n";
        str = str + boolToString("useYBoundary", useYBoundary, indent) + "\n";
        str = str + doubleToString("specifiedY", specifiedY, indent) + "\n";
        str = str + boolToString("useZBoundary", useZBoundary, indent) + "\n";
        str = str + doubleToString("specifiedZ", specifiedZ, indent) + "\n";
        str = str + intArrayToString("reflections", reflections, indent) + "\n";
        return str;
    }


    // Attributes
    private int     octant;
    private boolean useXBoundary;
    private double  specifiedX;
    private boolean useYBoundary;
    private double  specifiedY;
    private boolean useZBoundary;
    private double  specifiedZ;
    private int[]   reflections;
}

