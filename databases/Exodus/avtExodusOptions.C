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
//                           avtExodusOptions.C                              //
// ************************************************************************* //

#include <avtExodusOptions.h>
#include <snprintf.h>
#include <DBOptionsAttributes.h>

#include <vector>
#include <string>

using std::vector;
using std::string;
using namespace ExodusDBOptions;

// ****************************************************************************
//  Function: GetExodusReadOptions
//
//  Purpose:
//      Creates the options for Exodus readers.
//
//  Programmer: miller -- generated by xml2avt
//  Mark C. Miller, Tue Dec  9 10:04:22 PST 2014
//
//    Mark C. Miller, Wed Feb 11 17:05:25 PST 2015
//    Elaborated on help string for defining expressions.
// ****************************************************************************

DBOptionsAttributes *
GetExodusReadOptions(void)
{
    DBOptionsAttributes *rv = new DBOptionsAttributes;

    rv->SetBool(EXODUS_DETECT_COMPOUND_VARS, true);

    vector<string> materialConvention;
    materialConvention.push_back("None");   // 0
    materialConvention.push_back("ALEGRA"); // 1
    materialConvention.push_back("CTH");    // 2
    materialConvention.push_back("Custom"); // 3
    rv->SetEnum(EXODUS_MATERIAL_CONVENTION, 0); // None
    rv->SetEnumStrings(EXODUS_MATERIAL_CONVENTION, materialConvention);
    rv->SetInt(EXODUS_MATERIAL_COUNT, -1);
    rv->SetString(EXODUS_VOLFRAC_NAMESCHEME, "");
    rv->SetString(EXODUS_MATSPEC_NAMESCHEME, "");

    char helpStr[4096];
    SNPRINTF(helpStr, sizeof(helpStr),
        "<p><b>%s</b>: Checking this option will cause the plugin to try to guess that similarly "
        "named variables are the scalar components of an aggregate type such as a vector, "
        "tensor or array variable. The plugin will then automatically define expressions "
        "for these aggregate typed variables. Note that this is just a convenience to free "
        "users from having to define expressions manally within their VisIt session."
        "<p> "
        "<p><b>%s</b>: Ordinarily, the plugin will determine the material count from the "
        "material convention nameschemes. However, if it is having trouble getting the "
        "correct count, you can specify it manually with this option. "
        "<p><b>%s</b>: A few pre-defined conventions for handling mixed materials from Exodus files "
        "are supported. In addition, you can define your own custom conventions as well. "
        "For a custom convention, you must define the <i>namescheme</i> that will produce "
        "the names of the scalar variables holding material volume fractions. Optionally, "
        "you can specify a <i>namescheme</i> to produce the names of the scalar variables "
        "holding material-specific values given the name of a non-material-specific variable. "
        "For more information on nameschemes, please consult the description of DBMakeNamescheme "
        "in the <a href=\"https://wci.llnl.gov/content/assets/docs/simulation/computer-codes/"
        "silo/LLNL-SM-654357.pdf\">Silo user's manual</a>. The nameschemes used here are identical "
        "to those described in the Silo user's manual with one extension. The conversion specifier %%V "
        "is used to denote the basename (non-material-specific) name of a set of scalar variables "
        "holding material specific values."
        "<p> "
        "<p>The ALEGRA nameschemes for volume fraction and material specific variables  are "
        "\"%s\" and \"%s\"."
        "<p> "
        "<p>The CTH nameschemes are \"%s\" and \"%s\"."
        "<p> "
        "<p>Finally, it is assumed materials are identified starting from one (1). The special "
        "material id of zero (0) is used to denote void.",
            EXODUS_DETECT_COMPOUND_VARS,
            EXODUS_MATERIAL_COUNT, 
            EXODUS_MATERIAL_CONVENTION,
            EXODUS_VOLFRAC_NAMESCHEME_ALEGRA,
            EXODUS_MATSPEC_NAMESCHEME_ALEGRA,
            EXODUS_VOLFRAC_NAMESCHEME_CTH,
            EXODUS_MATSPEC_NAMESCHEME_CTH);
    rv->SetHelp(helpStr);

    return rv;
}


// ****************************************************************************
//  Function: GetExodusWriteOptions
//
//  Purpose:
//      Creates the options for Exodus writers.
//
//  Programmer: miller -- generated by xml2avt
//  Mark C. Miller, Tue Dec  9 10:04:22 PST 2014
//
// ****************************************************************************

DBOptionsAttributes *
GetExodusWriteOptions(void)
{
    DBOptionsAttributes *rv = new DBOptionsAttributes;
    return rv;
}
