package llnl.visit;

import java.lang.Integer;
import java.util.Vector;

// ****************************************************************************
// Class: PickAttributes
//
// Purpose:
//    This class contains attributes used for pick.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Wed Nov 5 17:15:11 PST 2003
//
// Modifications:
//   
// ****************************************************************************

public class PickAttributes extends AttributeSubject
{
    // Constants
    public final static int PICKTYPE_ZONE = 0;
    public final static int PICKTYPE_NODE = 1;


    public PickAttributes()
    {
        super(26);

        clearWindow = false;
        fulfilled = false;
        pickLetter = new String("(null)");
        elementNumber = -1;
        timeStep = -1;
        domain = -1;
        dimension = -1;
        databaseName = new String("(null)");
        activeVariable = new String("(null)");
        pickPoint = new float[3];
        pickPoint[0] = 0f;
        pickPoint[1] = 0f;
        pickPoint[2] = 0f;
        cellPoint = new float[3];
        cellPoint[0] = 0f;
        cellPoint[1] = 0f;
        cellPoint[2] = 0f;
        incidentElements = new Vector();
        variables = new Vector();
        variables.addElement(new String("default"));
        varInfo = new Vector();
        useNodeCoords = false;
        logicalCoords = false;
        nodeCoords = new Vector();
        rayPoint1 = new float[3];
        rayPoint1[0] = 0f;
        rayPoint1[1] = 0f;
        rayPoint1[2] = 0f;
        rayPoint2 = new float[3];
        rayPoint2[0] = 0f;
        rayPoint2[1] = 0f;
        rayPoint2[2] = 0f;
        needTransformMessage = false;
        pickType = PICKTYPE_ZONE;
        meshInfo = new String("(null)");
        realElementNumber = -1;
        realIncidentElements = new Vector();
        nodePoint = new float[3];
        nodePoint[0] = 0f;
        nodePoint[1] = 0f;
        nodePoint[2] = 0f;
        plotBounds = new float[6];
        plotBounds[0] = 0f;
        plotBounds[1] = 0f;
        plotBounds[2] = 0f;
        plotBounds[3] = 0f;
        plotBounds[4] = 0f;
        plotBounds[5] = 0f;
    }

    public PickAttributes(PickAttributes obj)
    {
        super(26);

        int i;

        clearWindow = obj.clearWindow;
        fulfilled = obj.fulfilled;
        pickLetter = new String(obj.pickLetter);
        elementNumber = obj.elementNumber;
        timeStep = obj.timeStep;
        domain = obj.domain;
        dimension = obj.dimension;
        databaseName = new String(obj.databaseName);
        activeVariable = new String(obj.activeVariable);
        pickPoint = new float[3];
        pickPoint[0] = obj.pickPoint[0];
        pickPoint[1] = obj.pickPoint[1];
        pickPoint[2] = obj.pickPoint[2];

        cellPoint = new float[3];
        cellPoint[0] = obj.cellPoint[0];
        cellPoint[1] = obj.cellPoint[1];
        cellPoint[2] = obj.cellPoint[2];

        incidentElements = new Vector();
        for(i = 0; i < obj.incidentElements.size(); ++i)
        {
            Integer iv = (Integer)obj.incidentElements.elementAt(i);
            incidentElements.addElement(new Integer(iv.intValue()));
        }
        variables = new Vector(obj.variables.size());
        for(i = 0; i < obj.variables.size(); ++i)
            variables.addElement(new String((String)obj.variables.elementAt(i)));

        // *** Copy the varInfo field ***
        varInfo = new Vector(obj.varInfo.size());
        for(i = 0; i < obj.varInfo.size(); ++i)
        {
            PickVarInfo newObj = (PickVarInfo)varInfo.elementAt(i);
            varInfo.addElement(new PickVarInfo(newObj));
        }

        useNodeCoords = obj.useNodeCoords;
        logicalCoords = obj.logicalCoords;
        nodeCoords = new Vector(obj.nodeCoords.size());
        for(i = 0; i < obj.nodeCoords.size(); ++i)
            nodeCoords.addElement(new String((String)obj.nodeCoords.elementAt(i)));

        rayPoint1 = new float[3];
        rayPoint1[0] = obj.rayPoint1[0];
        rayPoint1[1] = obj.rayPoint1[1];
        rayPoint1[2] = obj.rayPoint1[2];

        rayPoint2 = new float[3];
        rayPoint2[0] = obj.rayPoint2[0];
        rayPoint2[1] = obj.rayPoint2[1];
        rayPoint2[2] = obj.rayPoint2[2];

        needTransformMessage = obj.needTransformMessage;
        pickType = obj.pickType;
        meshInfo = new String(obj.meshInfo);
        realElementNumber = obj.realElementNumber;
        realIncidentElements = new Vector();
        for(i = 0; i < obj.realIncidentElements.size(); ++i)
        {
            Integer iv = (Integer)obj.realIncidentElements.elementAt(i);
            realIncidentElements.addElement(new Integer(iv.intValue()));
        }
        nodePoint = new float[3];
        nodePoint[0] = obj.nodePoint[0];
        nodePoint[1] = obj.nodePoint[1];
        nodePoint[2] = obj.nodePoint[2];

        plotBounds = new float[6];
        for(i = 0; i < obj.plotBounds.length; ++i)
            plotBounds[i] = obj.plotBounds[i];


        SelectAll();
    }

    public boolean equals(PickAttributes obj)
    {
        int i;

        // Compare the pickPoint arrays.
        boolean pickPoint_equal = true;
        for(i = 0; i < 3 && pickPoint_equal; ++i)
            pickPoint_equal = (pickPoint[i] == obj.pickPoint[i]);

        // Compare the cellPoint arrays.
        boolean cellPoint_equal = true;
        for(i = 0; i < 3 && cellPoint_equal; ++i)
            cellPoint_equal = (cellPoint[i] == obj.cellPoint[i]);

        boolean varInfo_equal = (obj.varInfo.size() == varInfo.size());
        for(i = 0; (i < varInfo.size()) && varInfo_equal; ++i)
        {
            // Make references to PickVarInfo from Object.
            PickVarInfo varInfo1 = (PickVarInfo)varInfo.elementAt(i);
            PickVarInfo varInfo2 = (PickVarInfo)obj.varInfo.elementAt(i);
            varInfo_equal = varInfo1.equals(varInfo2);
        }

        // Compare the rayPoint1 arrays.
        boolean rayPoint1_equal = true;
        for(i = 0; i < 3 && rayPoint1_equal; ++i)
            rayPoint1_equal = (rayPoint1[i] == obj.rayPoint1[i]);

        // Compare the rayPoint2 arrays.
        boolean rayPoint2_equal = true;
        for(i = 0; i < 3 && rayPoint2_equal; ++i)
            rayPoint2_equal = (rayPoint2[i] == obj.rayPoint2[i]);

        // Compare the nodePoint arrays.
        boolean nodePoint_equal = true;
        for(i = 0; i < 3 && nodePoint_equal; ++i)
            nodePoint_equal = (nodePoint[i] == obj.nodePoint[i]);

        // Compare the plotBounds arrays.
        boolean plotBounds_equal = true;
        for(i = 0; i < 6 && plotBounds_equal; ++i)
            plotBounds_equal = (plotBounds[i] == obj.plotBounds[i]);

        // Create the return value
        return ((clearWindow == obj.clearWindow) &&
                (fulfilled == obj.fulfilled) &&
                (pickLetter == obj.pickLetter) &&
                (elementNumber == obj.elementNumber) &&
                (timeStep == obj.timeStep) &&
                (domain == obj.domain) &&
                (dimension == obj.dimension) &&
                (databaseName == obj.databaseName) &&
                (activeVariable == obj.activeVariable) &&
                pickPoint_equal &&
                cellPoint_equal &&
                (incidentElements == obj.incidentElements) &&
                (variables == obj.variables) &&
                varInfo_equal &&
                (useNodeCoords == obj.useNodeCoords) &&
                (logicalCoords == obj.logicalCoords) &&
                (nodeCoords == obj.nodeCoords) &&
                rayPoint1_equal &&
                rayPoint2_equal &&
                (needTransformMessage == obj.needTransformMessage) &&
                (pickType == obj.pickType) &&
                (meshInfo == obj.meshInfo) &&
                (realElementNumber == obj.realElementNumber) &&
                (realIncidentElements == obj.realIncidentElements) &&
                nodePoint_equal &&
                plotBounds_equal);
    }

    // Property setting methods
    public void SetClearWindow(boolean clearWindow_)
    {
        clearWindow = clearWindow_;
        Select(0);
    }

    public void SetFulfilled(boolean fulfilled_)
    {
        fulfilled = fulfilled_;
        Select(1);
    }

    public void SetPickLetter(String pickLetter_)
    {
        pickLetter = pickLetter_;
        Select(2);
    }

    public void SetElementNumber(int elementNumber_)
    {
        elementNumber = elementNumber_;
        Select(3);
    }

    public void SetTimeStep(int timeStep_)
    {
        timeStep = timeStep_;
        Select(4);
    }

    public void SetDomain(int domain_)
    {
        domain = domain_;
        Select(5);
    }

    public void SetDimension(int dimension_)
    {
        dimension = dimension_;
        Select(6);
    }

    public void SetDatabaseName(String databaseName_)
    {
        databaseName = databaseName_;
        Select(7);
    }

    public void SetActiveVariable(String activeVariable_)
    {
        activeVariable = activeVariable_;
        Select(8);
    }

    public void SetPickPoint(float[] pickPoint_)
    {
        pickPoint[0] = pickPoint_[0];
        pickPoint[1] = pickPoint_[1];
        pickPoint[2] = pickPoint_[2];
        Select(9);
    }

    public void SetPickPoint(float e0, float e1, float e2)
    {
        pickPoint[0] = e0;
        pickPoint[1] = e1;
        pickPoint[2] = e2;
        Select(9);
    }

    public void SetCellPoint(float[] cellPoint_)
    {
        cellPoint[0] = cellPoint_[0];
        cellPoint[1] = cellPoint_[1];
        cellPoint[2] = cellPoint_[2];
        Select(10);
    }

    public void SetCellPoint(float e0, float e1, float e2)
    {
        cellPoint[0] = e0;
        cellPoint[1] = e1;
        cellPoint[2] = e2;
        Select(10);
    }

    public void SetIncidentElements(Vector incidentElements_)
    {
        incidentElements = incidentElements_;
        Select(11);
    }

    public void SetVariables(Vector variables_)
    {
        variables = variables_;
        Select(12);
    }

    public void SetUseNodeCoords(boolean useNodeCoords_)
    {
        useNodeCoords = useNodeCoords_;
        Select(14);
    }

    public void SetLogicalCoords(boolean logicalCoords_)
    {
        logicalCoords = logicalCoords_;
        Select(15);
    }

    public void SetNodeCoords(Vector nodeCoords_)
    {
        nodeCoords = nodeCoords_;
        Select(16);
    }

    public void SetRayPoint1(float[] rayPoint1_)
    {
        rayPoint1[0] = rayPoint1_[0];
        rayPoint1[1] = rayPoint1_[1];
        rayPoint1[2] = rayPoint1_[2];
        Select(17);
    }

    public void SetRayPoint1(float e0, float e1, float e2)
    {
        rayPoint1[0] = e0;
        rayPoint1[1] = e1;
        rayPoint1[2] = e2;
        Select(17);
    }

    public void SetRayPoint2(float[] rayPoint2_)
    {
        rayPoint2[0] = rayPoint2_[0];
        rayPoint2[1] = rayPoint2_[1];
        rayPoint2[2] = rayPoint2_[2];
        Select(18);
    }

    public void SetRayPoint2(float e0, float e1, float e2)
    {
        rayPoint2[0] = e0;
        rayPoint2[1] = e1;
        rayPoint2[2] = e2;
        Select(18);
    }

    public void SetNeedTransformMessage(boolean needTransformMessage_)
    {
        needTransformMessage = needTransformMessage_;
        Select(19);
    }

    public void SetPickType(int pickType_)
    {
        pickType = pickType_;
        Select(20);
    }

    public void SetMeshInfo(String meshInfo_)
    {
        meshInfo = meshInfo_;
        Select(21);
    }

    public void SetRealElementNumber(int realElementNumber_)
    {
        realElementNumber = realElementNumber_;
        Select(22);
    }

    public void SetRealIncidentElements(Vector realIncidentElements_)
    {
        realIncidentElements = realIncidentElements_;
        Select(23);
    }

    public void SetNodePoint(float[] nodePoint_)
    {
        nodePoint[0] = nodePoint_[0];
        nodePoint[1] = nodePoint_[1];
        nodePoint[2] = nodePoint_[2];
        Select(24);
    }

    public void SetNodePoint(float e0, float e1, float e2)
    {
        nodePoint[0] = e0;
        nodePoint[1] = e1;
        nodePoint[2] = e2;
        Select(24);
    }

    public void SetPlotBounds(float[] plotBounds_)
    {
        for(int i = 0; i < 6; ++i)
             plotBounds[i] = plotBounds_[i];
        Select(25);
    }

    // Property getting methods
    public boolean GetClearWindow() { return clearWindow; }
    public boolean GetFulfilled() { return fulfilled; }
    public String  GetPickLetter() { return pickLetter; }
    public int     GetElementNumber() { return elementNumber; }
    public int     GetTimeStep() { return timeStep; }
    public int     GetDomain() { return domain; }
    public int     GetDimension() { return dimension; }
    public String  GetDatabaseName() { return databaseName; }
    public String  GetActiveVariable() { return activeVariable; }
    public float[] GetPickPoint() { return pickPoint; }
    public float[] GetCellPoint() { return cellPoint; }
    public Vector  GetIncidentElements() { return incidentElements; }
    public Vector  GetVariables() { return variables; }
    public Vector  GetVarInfo() { return varInfo; }
    public boolean GetUseNodeCoords() { return useNodeCoords; }
    public boolean GetLogicalCoords() { return logicalCoords; }
    public Vector  GetNodeCoords() { return nodeCoords; }
    public float[] GetRayPoint1() { return rayPoint1; }
    public float[] GetRayPoint2() { return rayPoint2; }
    public boolean GetNeedTransformMessage() { return needTransformMessage; }
    public int     GetPickType() { return pickType; }
    public String  GetMeshInfo() { return meshInfo; }
    public int     GetRealElementNumber() { return realElementNumber; }
    public Vector  GetRealIncidentElements() { return realIncidentElements; }
    public float[] GetNodePoint() { return nodePoint; }
    public float[] GetPlotBounds() { return plotBounds; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(clearWindow);
        if(WriteSelect(1, buf))
            buf.WriteBool(fulfilled);
        if(WriteSelect(2, buf))
            buf.WriteString(pickLetter);
        if(WriteSelect(3, buf))
            buf.WriteInt(elementNumber);
        if(WriteSelect(4, buf))
            buf.WriteInt(timeStep);
        if(WriteSelect(5, buf))
            buf.WriteInt(domain);
        if(WriteSelect(6, buf))
            buf.WriteInt(dimension);
        if(WriteSelect(7, buf))
            buf.WriteString(databaseName);
        if(WriteSelect(8, buf))
            buf.WriteString(activeVariable);
        if(WriteSelect(9, buf))
            buf.WriteFloatArray(pickPoint);
        if(WriteSelect(10, buf))
            buf.WriteFloatArray(cellPoint);
        if(WriteSelect(11, buf))
            buf.WriteIntVector(incidentElements);
        if(WriteSelect(12, buf))
            buf.WriteStringVector(variables);
        if(WriteSelect(13, buf))
        {
            buf.WriteInt(varInfo.size());
            for(int i = 0; i < varInfo.size(); ++i)
            {
                PickVarInfo tmp = (PickVarInfo)varInfo.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(14, buf))
            buf.WriteBool(useNodeCoords);
        if(WriteSelect(15, buf))
            buf.WriteBool(logicalCoords);
        if(WriteSelect(16, buf))
            buf.WriteStringVector(nodeCoords);
        if(WriteSelect(17, buf))
            buf.WriteFloatArray(rayPoint1);
        if(WriteSelect(18, buf))
            buf.WriteFloatArray(rayPoint2);
        if(WriteSelect(19, buf))
            buf.WriteBool(needTransformMessage);
        if(WriteSelect(20, buf))
            buf.WriteInt(pickType);
        if(WriteSelect(21, buf))
            buf.WriteString(meshInfo);
        if(WriteSelect(22, buf))
            buf.WriteInt(realElementNumber);
        if(WriteSelect(23, buf))
            buf.WriteIntVector(realIncidentElements);
        if(WriteSelect(24, buf))
            buf.WriteFloatArray(nodePoint);
        if(WriteSelect(25, buf))
            buf.WriteFloatArray(plotBounds);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetClearWindow(buf.ReadBool());
                break;
            case 1:
                SetFulfilled(buf.ReadBool());
                break;
            case 2:
                SetPickLetter(buf.ReadString());
                break;
            case 3:
                SetElementNumber(buf.ReadInt());
                break;
            case 4:
                SetTimeStep(buf.ReadInt());
                break;
            case 5:
                SetDomain(buf.ReadInt());
                break;
            case 6:
                SetDimension(buf.ReadInt());
                break;
            case 7:
                SetDatabaseName(buf.ReadString());
                break;
            case 8:
                SetActiveVariable(buf.ReadString());
                break;
            case 9:
                SetPickPoint(buf.ReadFloatArray());
                break;
            case 10:
                SetCellPoint(buf.ReadFloatArray());
                break;
            case 11:
                SetIncidentElements(buf.ReadIntVector());
                break;
            case 12:
                SetVariables(buf.ReadStringVector());
                break;
            case 13:
                {
                    int len = buf.ReadInt();
                    varInfo.clear();
                    for(int j = 0; j < len; ++j)
                    {
                        PickVarInfo tmp = new PickVarInfo();
                        tmp.Read(buf);
                        varInfo.addElement(tmp);
                    }
                }
                Select(13);
                break;
            case 14:
                SetUseNodeCoords(buf.ReadBool());
                break;
            case 15:
                SetLogicalCoords(buf.ReadBool());
                break;
            case 16:
                SetNodeCoords(buf.ReadStringVector());
                break;
            case 17:
                SetRayPoint1(buf.ReadFloatArray());
                break;
            case 18:
                SetRayPoint2(buf.ReadFloatArray());
                break;
            case 19:
                SetNeedTransformMessage(buf.ReadBool());
                break;
            case 20:
                SetPickType(buf.ReadInt());
                break;
            case 21:
                SetMeshInfo(buf.ReadString());
                break;
            case 22:
                SetRealElementNumber(buf.ReadInt());
                break;
            case 23:
                SetRealIncidentElements(buf.ReadIntVector());
                break;
            case 24:
                SetNodePoint(buf.ReadFloatArray());
                break;
            case 25:
                SetPlotBounds(buf.ReadFloatArray());
                break;
            }
        }
    }

    // Attributegroup convenience methods
    public void AddPickVarInfo(PickVarInfo obj)
    {
        varInfo.addElement(new PickVarInfo(obj));
        Select(13);
    }

    public void ClearPickVarInfos()
    {
        varInfo.clear();
        Select(13);
    }

    public void RemovePickVarInfo(int index)
    {
        if(index >= 0 && index < varInfo.size())
        {
            varInfo.remove(index);
            Select(13);
        }
    }

    public int GetNumPickVarInfos()
    {
        return varInfo.size();
    }

    public PickVarInfo GetPickVarInfo(int i)
    {
        PickVarInfo tmp = (PickVarInfo)varInfo.elementAt(i);
        return tmp;
    }


    // Attributes
    private boolean clearWindow;
    private boolean fulfilled;
    private String  pickLetter;
    private int     elementNumber;
    private int     timeStep;
    private int     domain;
    private int     dimension;
    private String  databaseName;
    private String  activeVariable;
    private float[] pickPoint;
    private float[] cellPoint;
    private Vector  incidentElements; // vector of Integer objects
    private Vector  variables; // vector of String objects
    private Vector  varInfo; // vector of PickVarInfo objects
    private boolean useNodeCoords;
    private boolean logicalCoords;
    private Vector  nodeCoords; // vector of String objects
    private float[] rayPoint1;
    private float[] rayPoint2;
    private boolean needTransformMessage;
    private int     pickType;
    private String  meshInfo;
    private int     realElementNumber;
    private Vector  realIncidentElements; // vector of Integer objects
    private float[] nodePoint;
    private float[] plotBounds;
}

