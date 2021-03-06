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
//                           avtMoleculePlot.h                               //
// ************************************************************************* //

#ifndef AVT_MOLECULE_PLOT_H
#define AVT_MOLECULE_PLOT_H

#include <avtPlot.h>
#include <MoleculeAttributes.h>
#include <avtLevelsLegend.h>

class avtVariableLegend;
class avtLevelsLegend;
class avtLookupTable;
class avtMoleculeFilter;
class avtMoleculeMapper;
class avtExtractMolInfoFilter;

// ****************************************************************************
//  Method: avtMoleculePlot
//
//  Purpose:
//      A concrete type of avtPlot for molecules.
//
//  Programmer: Jeremy Meredith
//  Creation:   Februray 14, 2006
//
//  Modifications:
//    Jeremy Meredith, Tue Aug 29 13:19:09 EDT 2006
//    Changed to point data plot.
//
// ****************************************************************************

class
avtMoleculePlot : public avtPointDataPlot
{
  public:
    avtMoleculePlot();
    virtual        ~avtMoleculePlot();

    static avtPlot *Create();

    virtual const char *GetName(void) { return "MoleculePlot"; };

    virtual void    SetAtts(const AttributeGroup*);
    virtual void    GetDataExtents(std::vector<double> &);
    virtual void    ReleaseData(void);
    virtual bool    SetColorTable(const char *ctName);

    void            SetLegend(bool);
    void            SetLegendRange(void);

    avtContract_p EnhanceSpecification(avtContract_p);
  protected:
    MoleculeAttributes       atts;

    avtMoleculeMapper       *mapper;

    avtMoleculeFilter       *moleculeFilter;
    avtExtractMolInfoFilter *extractMolInfoFilter;

    avtLevelsLegend         *levelsLegend;
    avtLegend_p              levelsLegendRefPtr;

    avtVariableLegend       *variableLegend;
    avtLegend_p              variableLegendRefPtr;

    avtLookupTable          *levelsLUT;
    avtLookupTable          *variableLUT;

    LevelColorMap            elementColorMap;
    LevelColorMap            residueColorMap;
    LevelColorMap            blankColorMap;

    virtual avtMapperBase   *GetMapper(void);
    virtual avtDataObject_p  ApplyOperators(avtDataObject_p);
    virtual avtDataObject_p  ApplyRenderingTransformation(avtDataObject_p);
    virtual void             CustomizeBehavior(void);
    virtual void             CustomizeMapper(avtDataObjectInformation &);
    virtual avtLegend_p      GetLegend(void);
    void                     CreateLegendColorMaps();
};


#endif


