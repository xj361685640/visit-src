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
//                      avtArrayComponentwiseProductExpression.C                       //
// ************************************************************************* //

#include <avtArrayComponentwiseProductExpression.h>

#include <vtkDataArray.h>
#include <vtkDataArray.h>

#include <ExpressionException.h>


// ****************************************************************************
//  Method: avtArrayComponentwiseProductExpression constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtArrayComponentwiseProductExpression::avtArrayComponentwiseProductExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtArrayComponentwiseProductExpression destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtArrayComponentwiseProductExpression::~avtArrayComponentwiseProductExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtArrayComponentwiseProductExpression::DoOperation
//
//  Purpose:
//      Componentwise product of  two arrays into a third array.
//
//  Arguments:
//      in1           The first input data array.
//      in2           The second input data array.
//      out           The output data array.
//      ncomponents   The number of components ('1' for scalar, '2' or '3' for
//                    vectors, etc.)
//      ntuples       The number of tuples (ie 'npoints' or 'ncells')
//
//  Programmer: Gunther H. Weber (based on avtBinaryAddExpression by Sean Ahern)
//  Creation:   March 2, 2015
//
//  Modifications:
//
// ****************************************************************************

void
avtArrayComponentwiseProductExpression::DoOperation(vtkDataArray *in1, vtkDataArray *in2,
                                vtkDataArray *out, int ncomponents,int ntuples)
{
    bool var1IsSingleton = (in1->GetNumberOfTuples() == 1);
    bool var2IsSingleton = (in2->GetNumberOfTuples() == 1);
    int in1ncomps = in1->GetNumberOfComponents();
    int in2ncomps = in2->GetNumberOfComponents();
    if (in1ncomps == in2ncomps)
    {
        for (int i = 0 ; i < ntuples ; i++)
        {
            vtkIdType tup1 = (var1IsSingleton ? 0 : i);
            vtkIdType tup2 = (var2IsSingleton ? 0 : i);
            for (int j = 0 ; j < in1ncomps ; j++)
            {
                double val1 = in1->GetComponent(tup1, j);
                double val2 = in2->GetComponent(tup2, j);
                out->SetComponent(i, j, val1 * val2);
            }
        }
    }
    else if (in1ncomps > 1 && in2ncomps == 1)
    {
        for (int i = 0 ; i < ntuples ; i++)
        {
            vtkIdType tup1 = (var1IsSingleton ? 0 : i);
            vtkIdType tup2 = (var2IsSingleton ? 0 : i);
            double val2 = in2->GetTuple1(tup2);
            for (int j = 0 ; j < in1ncomps ; j++)
            {
                double val1 = in1->GetComponent(tup1, j);
                out->SetComponent(i, j, val1 * val2);
            }
        }
    }
    else if (in1ncomps == 1 && in2ncomps > 1)
    {
        for (int i = 0 ; i < ntuples ; i++)
        {
            vtkIdType tup1 = (var1IsSingleton ? 0 : i);
            vtkIdType tup2 = (var2IsSingleton ? 0 : i);
            double val1 = in1->GetTuple1(tup1);
            for (int j = 0 ; j < in2ncomps ; j++)
            {
                double val2 = in2->GetComponent(tup2, j);
                out->SetComponent(i, j, val1 * val2);
            }
        }
    }
    else
    {
        EXCEPTION2(ExpressionException, outputVariableName,
                   "Don't know how to compute componentwise prodcut for arrays of differing dimensions.");
    }
}


// ****************************************************************************
//  Method:  avtArrayComponentwiseProductExpression::GetVariableType
//
//  Purpose:
//    Better support for array variables.  We actually return the output
//    type to be the same as the input type (assuming they are the same,
//    or if one has 1 compoent).
//
//  Note:
//    This can't yet be pulled up into avtBinaryMathExpression because
//    mult and div do non-elementwise operations.  If that changes,
//    we should pull this up.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    March 18, 2009
//
// ****************************************************************************

avtVarType
avtArrayComponentwiseProductExpression::GetVariableType()
{
    avtDataAttributes &atts = GetInput()->GetInfo().GetAttributes();
    if (varnames.size() != 2)
        return AVT_UNKNOWN_TYPE;

    if (!atts.ValidVariable(varnames[0]) ||
        !atts.ValidVariable(varnames[1]))
        return AVT_UNKNOWN_TYPE;

    int ncomp1 = atts.GetVariableDimension(varnames[0]);
    int ncomp2 = atts.GetVariableDimension(varnames[1]);
    avtVarType type1 = atts.GetVariableType(varnames[0]);
    avtVarType type2 = atts.GetVariableType(varnames[1]);

    if (type1 == type2)
    {
        return type1;
    }
    else if (ncomp1 == 1)
    {
        return type2;
    }
    else if (ncomp2 == 1)
    {
        return type1;
    }
    else
    {
        return AVT_UNKNOWN_TYPE;
    }
}
