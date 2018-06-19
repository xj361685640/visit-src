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

package llnl.visit;

import java.util.Vector;
import java.lang.Integer;

// ****************************************************************************
// Class: SILAttributes
//
// Purpose:
//    This class contains the information needed to represent a SIL.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class SILAttributes extends AttributeSubject
{
    private static int SILAttributes_numAdditionalAtts = 12;

    public SILAttributes()
    {
        super(SILAttributes_numAdditionalAtts);

        nSets = 0;
        setNames = new Vector();
        setIds = new Vector();
        wholeList = new Vector();
        nCollections = 0;
        category = new Vector();
        role = new Vector();
        superset = new Vector();
        nspace = new Vector();
        matrices = new Vector();
        arrays = new Vector();
        order = new Vector();
    }

    public SILAttributes(int nMoreFields)
    {
        super(SILAttributes_numAdditionalAtts + nMoreFields);

        nSets = 0;
        setNames = new Vector();
        setIds = new Vector();
        wholeList = new Vector();
        nCollections = 0;
        category = new Vector();
        role = new Vector();
        superset = new Vector();
        nspace = new Vector();
        matrices = new Vector();
        arrays = new Vector();
        order = new Vector();
    }

    public SILAttributes(SILAttributes obj)
    {
        super(obj);

        int i;

        nSets = obj.nSets;
        setNames = new Vector(obj.setNames.size());
        for(i = 0; i < obj.setNames.size(); ++i)
            setNames.addElement(new String((String)obj.setNames.elementAt(i)));

        setIds = new Vector();
        for(i = 0; i < obj.setIds.size(); ++i)
        {
            Integer iv = (Integer)obj.setIds.elementAt(i);
            setIds.addElement(new Integer(iv.intValue()));
        }
        wholeList = new Vector();
        for(i = 0; i < obj.wholeList.size(); ++i)
        {
            Integer iv = (Integer)obj.wholeList.elementAt(i);
            wholeList.addElement(new Integer(iv.intValue()));
        }
        nCollections = obj.nCollections;
        category = new Vector(obj.category.size());
        for(i = 0; i < obj.category.size(); ++i)
            category.addElement(new String((String)obj.category.elementAt(i)));

        role = new Vector();
        for(i = 0; i < obj.role.size(); ++i)
        {
            Integer iv = (Integer)obj.role.elementAt(i);
            role.addElement(new Integer(iv.intValue()));
        }
        superset = new Vector();
        for(i = 0; i < obj.superset.size(); ++i)
        {
            Integer iv = (Integer)obj.superset.elementAt(i);
            superset.addElement(new Integer(iv.intValue()));
        }
        // *** Copy the nspace field ***
        nspace = new Vector(obj.nspace.size());
        for(i = 0; i < obj.nspace.size(); ++i)
        {
            NamespaceAttributes oldObj = (NamespaceAttributes)obj.nspace.elementAt(i);
            nspace.addElement(new NamespaceAttributes(oldObj));
        }

        // *** Copy the matrices field ***
        matrices = new Vector(obj.matrices.size());
        for(i = 0; i < obj.matrices.size(); ++i)
        {
            SILMatrixAttributes oldObj = (SILMatrixAttributes)obj.matrices.elementAt(i);
            matrices.addElement(new SILMatrixAttributes(oldObj));
        }

        // *** Copy the arrays field ***
        arrays = new Vector(obj.arrays.size());
        for(i = 0; i < obj.arrays.size(); ++i)
        {
            SILArrayAttributes oldObj = (SILArrayAttributes)obj.arrays.elementAt(i);
            arrays.addElement(new SILArrayAttributes(oldObj));
        }

        order = new Vector();
        for(i = 0; i < obj.order.size(); ++i)
        {
            Integer iv = (Integer)obj.order.elementAt(i);
            order.addElement(new Integer(iv.intValue()));
        }

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return SILAttributes_numAdditionalAtts;
    }

    public boolean equals(SILAttributes obj)
    {
        int i;

        // Compare the elements in the setNames vector.
        boolean setNames_equal = (obj.setNames.size() == setNames.size());
        for(i = 0; (i < setNames.size()) && setNames_equal; ++i)
        {
            // Make references to String from Object.
            String setNames1 = (String)setNames.elementAt(i);
            String setNames2 = (String)obj.setNames.elementAt(i);
            setNames_equal = setNames1.equals(setNames2);
        }
        // Compare the elements in the setIds vector.
        boolean setIds_equal = (obj.setIds.size() == setIds.size());
        for(i = 0; (i < setIds.size()) && setIds_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer setIds1 = (Integer)setIds.elementAt(i);
            Integer setIds2 = (Integer)obj.setIds.elementAt(i);
            setIds_equal = setIds1.equals(setIds2);
        }
        // Compare the elements in the wholeList vector.
        boolean wholeList_equal = (obj.wholeList.size() == wholeList.size());
        for(i = 0; (i < wholeList.size()) && wholeList_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer wholeList1 = (Integer)wholeList.elementAt(i);
            Integer wholeList2 = (Integer)obj.wholeList.elementAt(i);
            wholeList_equal = wholeList1.equals(wholeList2);
        }
        // Compare the elements in the category vector.
        boolean category_equal = (obj.category.size() == category.size());
        for(i = 0; (i < category.size()) && category_equal; ++i)
        {
            // Make references to String from Object.
            String category1 = (String)category.elementAt(i);
            String category2 = (String)obj.category.elementAt(i);
            category_equal = category1.equals(category2);
        }
        // Compare the elements in the role vector.
        boolean role_equal = (obj.role.size() == role.size());
        for(i = 0; (i < role.size()) && role_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer role1 = (Integer)role.elementAt(i);
            Integer role2 = (Integer)obj.role.elementAt(i);
            role_equal = role1.equals(role2);
        }
        // Compare the elements in the superset vector.
        boolean superset_equal = (obj.superset.size() == superset.size());
        for(i = 0; (i < superset.size()) && superset_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer superset1 = (Integer)superset.elementAt(i);
            Integer superset2 = (Integer)obj.superset.elementAt(i);
            superset_equal = superset1.equals(superset2);
        }
        // Compare the elements in the nspace vector.
        boolean nspace_equal = (obj.nspace.size() == nspace.size());
        for(i = 0; (i < nspace.size()) && nspace_equal; ++i)
        {
            // Make references to NamespaceAttributes from Object.
            NamespaceAttributes nspace1 = (NamespaceAttributes)nspace.elementAt(i);
            NamespaceAttributes nspace2 = (NamespaceAttributes)obj.nspace.elementAt(i);
            nspace_equal = nspace1.equals(nspace2);
        }
        // Compare the elements in the matrices vector.
        boolean matrices_equal = (obj.matrices.size() == matrices.size());
        for(i = 0; (i < matrices.size()) && matrices_equal; ++i)
        {
            // Make references to SILMatrixAttributes from Object.
            SILMatrixAttributes matrices1 = (SILMatrixAttributes)matrices.elementAt(i);
            SILMatrixAttributes matrices2 = (SILMatrixAttributes)obj.matrices.elementAt(i);
            matrices_equal = matrices1.equals(matrices2);
        }
        // Compare the elements in the arrays vector.
        boolean arrays_equal = (obj.arrays.size() == arrays.size());
        for(i = 0; (i < arrays.size()) && arrays_equal; ++i)
        {
            // Make references to SILArrayAttributes from Object.
            SILArrayAttributes arrays1 = (SILArrayAttributes)arrays.elementAt(i);
            SILArrayAttributes arrays2 = (SILArrayAttributes)obj.arrays.elementAt(i);
            arrays_equal = arrays1.equals(arrays2);
        }
        // Compare the elements in the order vector.
        boolean order_equal = (obj.order.size() == order.size());
        for(i = 0; (i < order.size()) && order_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer order1 = (Integer)order.elementAt(i);
            Integer order2 = (Integer)obj.order.elementAt(i);
            order_equal = order1.equals(order2);
        }
        // Create the return value
        return ((nSets == obj.nSets) &&
                setNames_equal &&
                setIds_equal &&
                wholeList_equal &&
                (nCollections == obj.nCollections) &&
                category_equal &&
                role_equal &&
                superset_equal &&
                nspace_equal &&
                matrices_equal &&
                arrays_equal &&
                order_equal);
    }

    // Property setting methods
    public void SetNSets(int nSets_)
    {
        nSets = nSets_;
        Select(0);
    }

    public void SetSetNames(Vector setNames_)
    {
        setNames = setNames_;
        Select(1);
    }

    public void SetSetIds(Vector setIds_)
    {
        setIds = setIds_;
        Select(2);
    }

    public void SetWholeList(Vector wholeList_)
    {
        wholeList = wholeList_;
        Select(3);
    }

    public void SetNCollections(int nCollections_)
    {
        nCollections = nCollections_;
        Select(4);
    }

    public void SetCategory(Vector category_)
    {
        category = category_;
        Select(5);
    }

    public void SetRole(Vector role_)
    {
        role = role_;
        Select(6);
    }

    public void SetSuperset(Vector superset_)
    {
        superset = superset_;
        Select(7);
    }

    public void SetOrder(Vector order_)
    {
        order = order_;
        Select(11);
    }

    // Property getting methods
    public int    GetNSets() { return nSets; }
    public Vector GetSetNames() { return setNames; }
    public Vector GetSetIds() { return setIds; }
    public Vector GetWholeList() { return wholeList; }
    public int    GetNCollections() { return nCollections; }
    public Vector GetCategory() { return category; }
    public Vector GetRole() { return role; }
    public Vector GetSuperset() { return superset; }
    public Vector GetNspace() { return nspace; }
    public Vector GetMatrices() { return matrices; }
    public Vector GetArrays() { return arrays; }
    public Vector GetOrder() { return order; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(nSets);
        if(WriteSelect(1, buf))
            buf.WriteStringVector(setNames);
        if(WriteSelect(2, buf))
            buf.WriteIntVector(setIds);
        if(WriteSelect(3, buf))
            buf.WriteIntVector(wholeList);
        if(WriteSelect(4, buf))
            buf.WriteInt(nCollections);
        if(WriteSelect(5, buf))
            buf.WriteStringVector(category);
        if(WriteSelect(6, buf))
            buf.WriteIntVector(role);
        if(WriteSelect(7, buf))
            buf.WriteIntVector(superset);
        if(WriteSelect(8, buf))
        {
            buf.WriteInt(nspace.size());
            for(int i = 0; i < nspace.size(); ++i)
            {
                NamespaceAttributes tmp = (NamespaceAttributes)nspace.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(9, buf))
        {
            buf.WriteInt(matrices.size());
            for(int i = 0; i < matrices.size(); ++i)
            {
                SILMatrixAttributes tmp = (SILMatrixAttributes)matrices.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(10, buf))
        {
            buf.WriteInt(arrays.size());
            for(int i = 0; i < arrays.size(); ++i)
            {
                SILArrayAttributes tmp = (SILArrayAttributes)arrays.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(11, buf))
            buf.WriteIntVector(order);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetNSets(buf.ReadInt());
            break;
        case 1:
            SetSetNames(buf.ReadStringVector());
            break;
        case 2:
            SetSetIds(buf.ReadIntVector());
            break;
        case 3:
            SetWholeList(buf.ReadIntVector());
            break;
        case 4:
            SetNCollections(buf.ReadInt());
            break;
        case 5:
            SetCategory(buf.ReadStringVector());
            break;
        case 6:
            SetRole(buf.ReadIntVector());
            break;
        case 7:
            SetSuperset(buf.ReadIntVector());
            break;
        case 8:
            {
                int len = buf.ReadInt();
                nspace.clear();
                for(int j = 0; j < len; ++j)
                {
                    NamespaceAttributes tmp = new NamespaceAttributes();
                    tmp.Read(buf);
                    nspace.addElement(tmp);
                }
            }
            Select(8);
            break;
        case 9:
            {
                int len = buf.ReadInt();
                matrices.clear();
                for(int j = 0; j < len; ++j)
                {
                    SILMatrixAttributes tmp = new SILMatrixAttributes();
                    tmp.Read(buf);
                    matrices.addElement(tmp);
                }
            }
            Select(9);
            break;
        case 10:
            {
                int len = buf.ReadInt();
                arrays.clear();
                for(int j = 0; j < len; ++j)
                {
                    SILArrayAttributes tmp = new SILArrayAttributes();
                    tmp.Read(buf);
                    arrays.addElement(tmp);
                }
            }
            Select(10);
            break;
        case 11:
            SetOrder(buf.ReadIntVector());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + intToString("nSets", nSets, indent) + "\n";
        str = str + stringVectorToString("setNames", setNames, indent) + "\n";
        str = str + intVectorToString("setIds", setIds, indent) + "\n";
        str = str + intVectorToString("wholeList", wholeList, indent) + "\n";
        str = str + intToString("nCollections", nCollections, indent) + "\n";
        str = str + stringVectorToString("category", category, indent) + "\n";
        str = str + intVectorToString("role", role, indent) + "\n";
        str = str + intVectorToString("superset", superset, indent) + "\n";
        str = str + indent + "nspace = {\n";
        for(int i = 0; i < nspace.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)nspace.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < nspace.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + indent + "matrices = {\n";
        for(int i = 0; i < matrices.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)matrices.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < matrices.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + indent + "arrays = {\n";
        for(int i = 0; i < arrays.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)arrays.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < arrays.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + intVectorToString("order", order, indent) + "\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddNspace(NamespaceAttributes obj)
    {
        nspace.addElement(new NamespaceAttributes(obj));
        Select(8);
    }

    public void ClearNspaces()
    {
        nspace.clear();
        Select(8);
    }

    public void RemoveNspace(int index)
    {
        if(index >= 0 && index < nspace.size())
        {
            nspace.remove(index);
            Select(8);
        }
    }

    public int GetNumNspaces()
    {
        return nspace.size();
    }

    public NamespaceAttributes GetNspace(int i)
    {
        NamespaceAttributes tmp = (NamespaceAttributes)nspace.elementAt(i);
        return tmp;
    }

    public void AddMatrices(SILMatrixAttributes obj)
    {
        matrices.addElement(new SILMatrixAttributes(obj));
        Select(9);
    }

    public void ClearMatrices()
    {
        matrices.clear();
        Select(9);
    }

    public void RemoveMatrices(int index)
    {
        if(index >= 0 && index < matrices.size())
        {
            matrices.remove(index);
            Select(9);
        }
    }

    public int GetNumMatrices()
    {
        return matrices.size();
    }

    public SILMatrixAttributes GetMatrices(int i)
    {
        SILMatrixAttributes tmp = (SILMatrixAttributes)matrices.elementAt(i);
        return tmp;
    }

    public void AddArrays(SILArrayAttributes obj)
    {
        arrays.addElement(new SILArrayAttributes(obj));
        Select(10);
    }

    public void ClearArrays()
    {
        arrays.clear();
        Select(10);
    }

    public void RemoveArrays(int index)
    {
        if(index >= 0 && index < arrays.size())
        {
            arrays.remove(index);
            Select(10);
        }
    }

    public int GetNumArrays()
    {
        return arrays.size();
    }

    public SILArrayAttributes GetArrays(int i)
    {
        SILArrayAttributes tmp = (SILArrayAttributes)arrays.elementAt(i);
        return tmp;
    }


    // Attributes
    private int    nSets;
    private Vector setNames; // vector of String objects
    private Vector setIds; // vector of Integer objects
    private Vector wholeList; // vector of Integer objects
    private int    nCollections;
    private Vector category; // vector of String objects
    private Vector role; // vector of Integer objects
    private Vector superset; // vector of Integer objects
    private Vector nspace; // vector of NamespaceAttributes objects
    private Vector matrices; // vector of SILMatrixAttributes objects
    private Vector arrays; // vector of SILArrayAttributes objects
    private Vector order; // vector of Integer objects
}

