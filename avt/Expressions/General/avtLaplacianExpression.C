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
//                           avtLaplacianExpression.C                        //
// ************************************************************************* //

#include <avtLaplacianExpression.h>

#include <snprintf.h>
#include <ExpressionException.h>

// ****************************************************************************
//  Method: avtLaplacianExpression constructor
//
//  Programmer: Hank Childs
//  Creation:   December 27, 2004
//
// ****************************************************************************

avtLaplacianExpression::avtLaplacianExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtLaplacianExpression destructor
//
//  Programmer: Hank Childs
//  Creation:   December 27, 2004
//
// ****************************************************************************

avtLaplacianExpression::~avtLaplacianExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtLaplacianExpression::GetMacro
//
//  Purpose:
//      Applies the macro to create a new expression corresponding to
//      the Laplacian.
//
//  Programmer: Hank Childs
//  Creation:   December 28, 2004
//
//  Modifications:
//
//    Cyrus Harrison, Sat Aug 11 18:45:53 PDT 2007
//    Add second argument for gradient algorithm selection
//
//    Hank Childs, Wed May  7 16:20:59 PDT 2008
//    Add support for rectilinear Laplacian, which only requires one layer
//    of data.
//
// ****************************************************************************

void
avtLaplacianExpression::GetMacro(std::vector<std::string> &args, 
                                 std::string &ne, Expression::ExprType &type)
{
    char new_expr[2048];
    size_t nargs = args.size();
    if(nargs == 1)
    {
        avtMeshType mt = GetInput()->GetInfo().GetAttributes().GetMeshType();
        if (mt == AVT_RECTILINEAR_MESH || mt == AVT_AMR_MESH)
        {
            SNPRINTF(new_expr, 2048, "rectilinear_laplacian(%s)", 
                                     args[0].c_str());
        }
        else
        {
            SNPRINTF(new_expr, 2048, "divergence(gradient(%s))", 
                                     args[0].c_str());
        }
    }
    else if (nargs == 2)
    {
        SNPRINTF(new_expr, 2048,
                "divergence(gradient(%s,%s))", 
                args[0].c_str(),args[1].c_str());
    }
    else
    {
        EXCEPTION2(ExpressionException, outputVariableName, 
                    " invalid laplacian syntax. "
                    "Expected arguments: "
                    "var, gradient_algorithm\n"
                    "[gradient_algorithm is optional]");
    }
    ne = new_expr;
    type = Expression::ScalarMeshVar;
}


