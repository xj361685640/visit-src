/*****************************************************************************
*
* Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                        PoincareScriptingPluginInfo.C
// ************************************************************************* //
#include <PyPoincareAttributes.h>
#include <PoincarePluginInfo.h>

VISIT_OPERATOR_PLUGIN_ENTRY(Poincare,Scripting)

// ****************************************************************************
// Method: PoincareScriptingPluginInfo::InitializePlugin
//
// Purpose: 
//   Calls the initialization function for the plugin.
//
// Arguments:
//   subj    : A pointer to the plugin's state object.
//   data    : A pointer to data to be used by the observer function.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
PoincareScriptingPluginInfo::InitializePlugin(AttributeSubject *subj,
    void *data)
{
    PyPoincareAttributes_StartUp((PoincareAttributes *)subj, data);
}

// ****************************************************************************
// Method: PoincareScriptingPluginInfo::GetMethodTable
//
// Purpose: 
//   Returns a pointer to the plugin's Python method table. These methods are
//   added to the top-level visit module's methods.
//
// Arguments:
//   nMethods : Returns the number of methods in the method table.
//
// Returns:    A pointer to the method table.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void *
PoincareScriptingPluginInfo::GetMethodTable(int *nMethods)
{
    return PyPoincareAttributes_GetMethodTable(nMethods);
}

// ****************************************************************************
// Method: PoincareScriptingPluginInfo::TypesMatch
//
// Purpose: 
//   Returns whether or not the input PyObject is Poincare plot attributes.
//
// Arguments:
//   pyobject : A PyObject cast to void*.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
PoincareScriptingPluginInfo::TypesMatch(void *pyobject)
{
    return PyPoincareAttributes_Check((PyObject *)pyobject);
}

// ****************************************************************************
// Method: PoincareScriptingPluginInfo::GetLogString
//
// Purpose: 
//   Gets a string representation of the current attributes.
//
// Arguments:
//   val : Whether or not to log state information.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

char *
PoincareScriptingPluginInfo::GetLogString()
{
    std::string s(PyPoincareAttributes_GetLogString());
    char *v = new char[s.size() + 1];
    strcpy(v, s.c_str());
    return v;
}

// ****************************************************************************
// Method: PoincareScriptingPluginInfo::SetDefaults
//
// Purpose: 
//   Used to set the default values for a plugin's state object.
//
// Arguments:
//   atts : The new state.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
PoincareScriptingPluginInfo::SetDefaults(const AttributeSubject *atts)
{
    PyPoincareAttributes_SetDefaults((const PoincareAttributes *)atts);
}
