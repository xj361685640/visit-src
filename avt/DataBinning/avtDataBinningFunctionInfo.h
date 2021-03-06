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
//                       avtDataBinningFunctionInfo.h                        //
// ************************************************************************* //

#ifndef AVT_DATA_BINNING_FUNCTION_INFO_H
#define AVT_DATA_BINNING_FUNCTION_INFO_H

#include <dbin_exports.h>

#include <vector>
#include <string>


class     avtBinningScheme;


// ****************************************************************************
//  Class: avtDataBinningFunctionInfo
//
//  Purpose:
//      This contains the information about the domain, the codomain, and the
//      binning scheme.  It is the information needed to set up a mapping.
//
//  Note:       The codomain is a mathematical term that can be loosely 
//              interpreted as the range.  The distinction is a little subtle.
//              The "range" of a function is the values that function can 
//              possible create.  The "codomain" is the set of numbers that
//              the function maps onto.  For example, the function "absval"
//              has a range of 0->infinity, but a codomain of the real numbers.
//
//  Programmer: Hank Childs
//  Creation:   February 12, 2006
//
//  Modifications:
//
//    Hank Childs, Sat Aug 21 14:05:14 PDT 2010
//    Renamed from DDF to DataBinning.
//
//    Hank Childs, Mon Aug  1 06:48:26 PDT 2011
//    Add support for spatial coordinates.
//
// ****************************************************************************

class AVTDBIN_API avtDataBinningFunctionInfo
{
  public:
    typedef enum
    {
          VARIABLE, X, Y, Z
    } BinBasedOn;

                         avtDataBinningFunctionInfo(avtBinningScheme *,
                                            const std::vector<std::string> &, 
                                            const std::vector<unsigned char> &, 
                                            const std::string &);
    virtual               ~avtDataBinningFunctionInfo();
  
    int                    GetDomainNumberOfTuples(void) const
                                { return (int)tupleNames.size(); };
    const std::string     &GetDomainTupleName(int) const;
    BinBasedOn             GetBinBasedOnType(int) const;
    const std::string     &GetCodomainName(void) const
                                { return codomainVariable; };
    avtBinningScheme      *GetBinningScheme(void)
                                { return binningScheme; };

  private:
    avtBinningScheme           *binningScheme;
    std::vector<std::string>    tupleNames;
    std::vector<BinBasedOn>     binBasedOn;
    std::string                 codomainVariable;
};


#endif


