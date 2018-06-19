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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: ProjectAttributes
//
// Purpose:
//    Project data from three to two dimensions
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class ProjectAttributes extends AttributeSubject implements Plugin
{
    // Enum values
    public final static int PROJECTIONTYPE_XYCARTESIAN = 0;
    public final static int PROJECTIONTYPE_ZRCYLINDRICAL = 1;


    public ProjectAttributes()
    {
        super(1);

        projectionType = PROJECTIONTYPE_XYCARTESIAN;
    }

    public ProjectAttributes(ProjectAttributes obj)
    {
        super(1);

        projectionType = obj.projectionType;

        SelectAll();
    }

    public boolean equals(ProjectAttributes obj)
    {
        // Create the return value
        return ((projectionType == obj.projectionType));
    }

    public String GetName() { return "Project"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetProjectionType(int projectionType_)
    {
        projectionType = projectionType_;
        Select(0);
    }

    // Property getting methods
    public int GetProjectionType() { return projectionType; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(projectionType);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        buf.ReadByte();
        SetProjectionType(buf.ReadInt());
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "projectionType = ";
        if(projectionType == PROJECTIONTYPE_XYCARTESIAN)
            str = str + "PROJECTIONTYPE_XYCARTESIAN";
        if(projectionType == PROJECTIONTYPE_ZRCYLINDRICAL)
            str = str + "PROJECTIONTYPE_ZRCYLINDRICAL";
        str = str + "\n";
        return str;
    }


    // Attributes
    private int projectionType;
}

