// ***************************************************************************
//
// Copyright (c) 2000 - 2008, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-400142
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
// Class: PluginManagerAttributes
//
// Purpose:
//    This class contains attributes for managing plugins.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class PluginManagerAttributes extends AttributeSubject
{
    public PluginManagerAttributes()
    {
        super(5);

        name = new Vector();
        type = new Vector();
        version = new Vector();
        id = new Vector();
        enabled = new Vector();
    }

    public PluginManagerAttributes(PluginManagerAttributes obj)
    {
        super(5);

        int i;

        name = new Vector(obj.name.size());
        for(i = 0; i < obj.name.size(); ++i)
            name.addElement(new String((String)obj.name.elementAt(i)));

        type = new Vector(obj.type.size());
        for(i = 0; i < obj.type.size(); ++i)
            type.addElement(new String((String)obj.type.elementAt(i)));

        version = new Vector(obj.version.size());
        for(i = 0; i < obj.version.size(); ++i)
            version.addElement(new String((String)obj.version.elementAt(i)));

        id = new Vector(obj.id.size());
        for(i = 0; i < obj.id.size(); ++i)
            id.addElement(new String((String)obj.id.elementAt(i)));

        enabled = new Vector();
        for(i = 0; i < obj.enabled.size(); ++i)
        {
            Integer iv = (Integer)obj.enabled.elementAt(i);
            enabled.addElement(new Integer(iv.intValue()));
        }

        SelectAll();
    }

    public boolean equals(PluginManagerAttributes obj)
    {
        int i;

        // Compare the elements in the name vector.
        boolean name_equal = (obj.name.size() == name.size());
        for(i = 0; (i < name.size()) && name_equal; ++i)
        {
            // Make references to String from Object.
            String name1 = (String)name.elementAt(i);
            String name2 = (String)obj.name.elementAt(i);
            name_equal = name1.equals(name2);
        }
        // Compare the elements in the type vector.
        boolean type_equal = (obj.type.size() == type.size());
        for(i = 0; (i < type.size()) && type_equal; ++i)
        {
            // Make references to String from Object.
            String type1 = (String)type.elementAt(i);
            String type2 = (String)obj.type.elementAt(i);
            type_equal = type1.equals(type2);
        }
        // Compare the elements in the version vector.
        boolean version_equal = (obj.version.size() == version.size());
        for(i = 0; (i < version.size()) && version_equal; ++i)
        {
            // Make references to String from Object.
            String version1 = (String)version.elementAt(i);
            String version2 = (String)obj.version.elementAt(i);
            version_equal = version1.equals(version2);
        }
        // Compare the elements in the id vector.
        boolean id_equal = (obj.id.size() == id.size());
        for(i = 0; (i < id.size()) && id_equal; ++i)
        {
            // Make references to String from Object.
            String id1 = (String)id.elementAt(i);
            String id2 = (String)obj.id.elementAt(i);
            id_equal = id1.equals(id2);
        }
        // Compare the elements in the enabled vector.
        boolean enabled_equal = (obj.enabled.size() == enabled.size());
        for(i = 0; (i < enabled.size()) && enabled_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer enabled1 = (Integer)enabled.elementAt(i);
            Integer enabled2 = (Integer)obj.enabled.elementAt(i);
            enabled_equal = enabled1.equals(enabled2);
        }
        // Create the return value
        return (name_equal &&
                type_equal &&
                version_equal &&
                id_equal &&
                enabled_equal);
    }

    // Property setting methods
    public void SetName(Vector name_)
    {
        name = name_;
        Select(0);
    }

    public void SetType(Vector type_)
    {
        type = type_;
        Select(1);
    }

    public void SetVersion(Vector version_)
    {
        version = version_;
        Select(2);
    }

    public void SetId(Vector id_)
    {
        id = id_;
        Select(3);
    }

    public void SetEnabled(Vector enabled_)
    {
        enabled = enabled_;
        Select(4);
    }

    // Property getting methods
    public Vector GetName() { return name; }
    public Vector GetType() { return type; }
    public Vector GetVersion() { return version; }
    public Vector GetId() { return id; }
    public Vector GetEnabled() { return enabled; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteStringVector(name);
        if(WriteSelect(1, buf))
            buf.WriteStringVector(type);
        if(WriteSelect(2, buf))
            buf.WriteStringVector(version);
        if(WriteSelect(3, buf))
            buf.WriteStringVector(id);
        if(WriteSelect(4, buf))
            buf.WriteIntVector(enabled);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetName(buf.ReadStringVector());
                break;
            case 1:
                SetType(buf.ReadStringVector());
                break;
            case 2:
                SetVersion(buf.ReadStringVector());
                break;
            case 3:
                SetId(buf.ReadStringVector());
                break;
            case 4:
                SetEnabled(buf.ReadIntVector());
                break;
            }
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringVectorToString("name", name, indent) + "\n";
        str = str + stringVectorToString("type", type, indent) + "\n";
        str = str + stringVectorToString("version", version, indent) + "\n";
        str = str + stringVectorToString("id", id, indent) + "\n";
        str = str + intVectorToString("enabled", enabled, indent) + "\n";
        return str;
    }


    // Attributes
    private Vector name; // vector of String objects
    private Vector type; // vector of String objects
    private Vector version; // vector of String objects
    private Vector id; // vector of String objects
    private Vector enabled; // vector of Integer objects
}

