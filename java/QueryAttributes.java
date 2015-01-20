// ***************************************************************************
//
// Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
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

import java.lang.Double;
import java.util.Vector;
import java.lang.Integer;

// ****************************************************************************
// Class: QueryAttributes
//
// Purpose:
//    This class contains attributes used for query.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class QueryAttributes extends AttributeSubject
{
    private static int QueryAttributes_numAdditionalAtts = 13;

    // Enum values
    public final static int VARTYPE_MESH = 0;
    public final static int VARTYPE_SCALAR = 1;
    public final static int VARTYPE_VECTOR = 2;
    public final static int VARTYPE_TENSOR = 3;
    public final static int VARTYPE_SYMMETRIC_TENSOR = 4;
    public final static int VARTYPE_ARRAY = 5;
    public final static int VARTYPE_LABEL = 6;
    public final static int VARTYPE_MATERIAL = 7;
    public final static int VARTYPE_SPECIES = 8;
    public final static int VARTYPE_CURVE = 9;
    public final static int VARTYPE_UNKNOWN = 10;

    public final static int DATATYPE_ACTUALDATA = 0;
    public final static int DATATYPE_ORIGINALDATA = 1;


    public QueryAttributes()
    {
        super(QueryAttributes_numAdditionalAtts);

        resultsMessage = new String("");
        resultsValue = new Vector();
        resultsValue.addElement(new Double(0));
        timeStep = 0;
        varTypes = new Vector();
        pipeIndex = -1;
        xUnits = new String("");
        yUnits = new String("");
        floatFormat = new String("%g");
        xmlResult = new String("");
        suppressOutput = false;
        queryInputParams = new MapNode();
        defaultName = new String("");
        defaultVars = new Vector();
    }

    public QueryAttributes(int nMoreFields)
    {
        super(QueryAttributes_numAdditionalAtts + nMoreFields);

        resultsMessage = new String("");
        resultsValue = new Vector();
        resultsValue.addElement(new Double(0));
        timeStep = 0;
        varTypes = new Vector();
        pipeIndex = -1;
        xUnits = new String("");
        yUnits = new String("");
        floatFormat = new String("%g");
        xmlResult = new String("");
        suppressOutput = false;
        queryInputParams = new MapNode();
        defaultName = new String("");
        defaultVars = new Vector();
    }

    public QueryAttributes(QueryAttributes obj)
    {
        super(QueryAttributes_numAdditionalAtts);

        int i;

        resultsMessage = new String(obj.resultsMessage);
        resultsValue = new Vector(obj.resultsValue.size());
        for(i = 0; i < obj.resultsValue.size(); ++i)
        {
            Double dv = (Double)obj.resultsValue.elementAt(i);
            resultsValue.addElement(new Double(dv.doubleValue()));
        }

        timeStep = obj.timeStep;
        varTypes = new Vector();
        for(i = 0; i < obj.varTypes.size(); ++i)
        {
            Integer iv = (Integer)obj.varTypes.elementAt(i);
            varTypes.addElement(new Integer(iv.intValue()));
        }
        pipeIndex = obj.pipeIndex;
        xUnits = new String(obj.xUnits);
        yUnits = new String(obj.yUnits);
        floatFormat = new String(obj.floatFormat);
        xmlResult = new String(obj.xmlResult);
        suppressOutput = obj.suppressOutput;
        queryInputParams = new MapNode(obj.queryInputParams);
        defaultName = new String(obj.defaultName);
        defaultVars = new Vector(obj.defaultVars.size());
        for(i = 0; i < obj.defaultVars.size(); ++i)
            defaultVars.addElement(new String((String)obj.defaultVars.elementAt(i)));


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return QueryAttributes_numAdditionalAtts;
    }

    public boolean equals(QueryAttributes obj)
    {
        int i;

        // Compare the elements in the resultsValue vector.
        boolean resultsValue_equal = (obj.resultsValue.size() == resultsValue.size());
        for(i = 0; (i < resultsValue.size()) && resultsValue_equal; ++i)
        {
            // Make references to Double from Object.
            Double resultsValue1 = (Double)resultsValue.elementAt(i);
            Double resultsValue2 = (Double)obj.resultsValue.elementAt(i);
            resultsValue_equal = resultsValue1.equals(resultsValue2);
        }
        // Compare the elements in the varTypes vector.
        boolean varTypes_equal = (obj.varTypes.size() == varTypes.size());
        for(i = 0; (i < varTypes.size()) && varTypes_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer varTypes1 = (Integer)varTypes.elementAt(i);
            Integer varTypes2 = (Integer)obj.varTypes.elementAt(i);
            varTypes_equal = varTypes1.equals(varTypes2);
        }
        // Create the return value
        return ((resultsMessage.equals(obj.resultsMessage)) &&
                resultsValue_equal &&
                (timeStep == obj.timeStep) &&
                varTypes_equal &&
                (pipeIndex == obj.pipeIndex) &&
                (xUnits.equals(obj.xUnits)) &&
                (yUnits.equals(obj.yUnits)) &&
                (floatFormat.equals(obj.floatFormat)) &&
                (xmlResult.equals(obj.xmlResult)) &&
                (suppressOutput == obj.suppressOutput) &&
                (queryInputParams.equals(obj.queryInputParams)) &&
                true /* can ignore defaultName */ &&
                true /* can ignore defaultVars */);
    }

    // Property setting methods
    public void SetResultsMessage(String resultsMessage_)
    {
        resultsMessage = resultsMessage_;
        Select(0);
    }

    public void SetResultsValue(Vector resultsValue_)
    {
        resultsValue = resultsValue_;
        Select(1);
    }

    public void SetTimeStep(int timeStep_)
    {
        timeStep = timeStep_;
        Select(2);
    }

    public void SetVarTypes(Vector varTypes_)
    {
        varTypes = varTypes_;
        Select(3);
    }

    public void SetPipeIndex(int pipeIndex_)
    {
        pipeIndex = pipeIndex_;
        Select(4);
    }

    public void SetXUnits(String xUnits_)
    {
        xUnits = xUnits_;
        Select(5);
    }

    public void SetYUnits(String yUnits_)
    {
        yUnits = yUnits_;
        Select(6);
    }

    public void SetFloatFormat(String floatFormat_)
    {
        floatFormat = floatFormat_;
        Select(7);
    }

    public void SetXmlResult(String xmlResult_)
    {
        xmlResult = xmlResult_;
        Select(8);
    }

    public void SetSuppressOutput(boolean suppressOutput_)
    {
        suppressOutput = suppressOutput_;
        Select(9);
    }

    public void SetQueryInputParams(MapNode queryInputParams_)
    {
        queryInputParams = queryInputParams_;
        Select(10);
    }

    public void SetDefaultName(String defaultName_)
    {
        defaultName = defaultName_;
        Select(11);
    }

    public void SetDefaultVars(Vector defaultVars_)
    {
        defaultVars = defaultVars_;
        Select(12);
    }

    // Property getting methods
    public String  GetResultsMessage() { return resultsMessage; }
    public Vector  GetResultsValue() { return resultsValue; }
    public int     GetTimeStep() { return timeStep; }
    public Vector  GetVarTypes() { return varTypes; }
    public int     GetPipeIndex() { return pipeIndex; }
    public String  GetXUnits() { return xUnits; }
    public String  GetYUnits() { return yUnits; }
    public String  GetFloatFormat() { return floatFormat; }
    public String  GetXmlResult() { return xmlResult; }
    public boolean GetSuppressOutput() { return suppressOutput; }
    public MapNode GetQueryInputParams() { return queryInputParams; }
    public String  GetDefaultName() { return defaultName; }
    public Vector  GetDefaultVars() { return defaultVars; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteString(resultsMessage);
        if(WriteSelect(1, buf))
            buf.WriteDoubleVector(resultsValue);
        if(WriteSelect(2, buf))
            buf.WriteInt(timeStep);
        if(WriteSelect(3, buf))
            buf.WriteIntVector(varTypes);
        if(WriteSelect(4, buf))
            buf.WriteInt(pipeIndex);
        if(WriteSelect(5, buf))
            buf.WriteString(xUnits);
        if(WriteSelect(6, buf))
            buf.WriteString(yUnits);
        if(WriteSelect(7, buf))
            buf.WriteString(floatFormat);
        if(WriteSelect(8, buf))
            buf.WriteString(xmlResult);
        if(WriteSelect(9, buf))
            buf.WriteBool(suppressOutput);
        if(WriteSelect(10, buf))
            queryInputParams.Write(buf);
        if(WriteSelect(11, buf))
            buf.WriteString(defaultName);
        if(WriteSelect(12, buf))
            buf.WriteStringVector(defaultVars);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetResultsMessage(buf.ReadString());
            break;
        case 1:
            SetResultsValue(buf.ReadDoubleVector());
            break;
        case 2:
            SetTimeStep(buf.ReadInt());
            break;
        case 3:
            SetVarTypes(buf.ReadIntVector());
            break;
        case 4:
            SetPipeIndex(buf.ReadInt());
            break;
        case 5:
            SetXUnits(buf.ReadString());
            break;
        case 6:
            SetYUnits(buf.ReadString());
            break;
        case 7:
            SetFloatFormat(buf.ReadString());
            break;
        case 8:
            SetXmlResult(buf.ReadString());
            break;
        case 9:
            SetSuppressOutput(buf.ReadBool());
            break;
        case 10:
            queryInputParams.Read(buf);
            break;
        case 11:
            SetDefaultName(buf.ReadString());
            break;
        case 12:
            SetDefaultVars(buf.ReadStringVector());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringToString("resultsMessage", resultsMessage, indent) + "\n";
        str = str + doubleVectorToString("resultsValue", resultsValue, indent) + "\n";
        str = str + intToString("timeStep", timeStep, indent) + "\n";
        str = str + intVectorToString("varTypes", varTypes, indent) + "\n";
        str = str + intToString("pipeIndex", pipeIndex, indent) + "\n";
        str = str + stringToString("xUnits", xUnits, indent) + "\n";
        str = str + stringToString("yUnits", yUnits, indent) + "\n";
        str = str + stringToString("floatFormat", floatFormat, indent) + "\n";
        str = str + stringToString("xmlResult", xmlResult, indent) + "\n";
        str = str + boolToString("suppressOutput", suppressOutput, indent) + "\n";
        str = str + indent + "queryInputParams = " + queryInputParams.toString(indent);
        str = str + stringToString("defaultName", defaultName, indent) + "\n";
        str = str + stringVectorToString("defaultVars", defaultVars, indent) + "\n";
        return str;
    }


    // Attributes
    private String  resultsMessage;
    private Vector  resultsValue; // vector of Double objects
    private int     timeStep;
    private Vector  varTypes; // vector of Integer objects
    private int     pipeIndex;
    private String  xUnits;
    private String  yUnits;
    private String  floatFormat;
    private String  xmlResult;
    private boolean suppressOutput;
    private MapNode queryInputParams;
    private String  defaultName;
    private Vector  defaultVars; // vector of String objects
}

