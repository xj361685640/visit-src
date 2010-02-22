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

import java.lang.Double;
import java.util.Vector;

// ****************************************************************************
// Class: PlotInfoAttributes
//
// Purpose:
//    contains info set by the executed plot.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class PlotInfoAttributes extends AttributeSubject
{
    public PlotInfoAttributes()
    {
        super(1);

        outputArray = new Vector();
    }

    public PlotInfoAttributes(PlotInfoAttributes obj)
    {
        super(1);

        int i;

        outputArray = new Vector(obj.outputArray.size());
        for(i = 0; i < obj.outputArray.size(); ++i)
        {
            Double dv = (Double)obj.outputArray.elementAt(i);
            outputArray.addElement(new Double(dv.doubleValue()));
        }


        SelectAll();
    }

    public boolean equals(PlotInfoAttributes obj)
    {
        int i;

        // Compare the elements in the outputArray vector.
        boolean outputArray_equal = (obj.outputArray.size() == outputArray.size());
        for(i = 0; (i < outputArray.size()) && outputArray_equal; ++i)
        {
            // Make references to Double from Object.
            Double outputArray1 = (Double)outputArray.elementAt(i);
            Double outputArray2 = (Double)obj.outputArray.elementAt(i);
            outputArray_equal = outputArray1.equals(outputArray2);
        }
        // Create the return value
        return (outputArray_equal);
    }

    // Property setting methods
    public void SetOutputArray(Vector outputArray_)
    {
        outputArray = outputArray_;
        Select(0);
    }

    // Property getting methods
    public Vector GetOutputArray() { return outputArray; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteDoubleVector(outputArray);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        buf.ReadByte();
        SetOutputArray(buf.ReadDoubleVector());
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + doubleVectorToString("outputArray", outputArray, indent) + "\n";
        return str;
    }


    // Attributes
    private Vector outputArray; // vector of Double objects
}

