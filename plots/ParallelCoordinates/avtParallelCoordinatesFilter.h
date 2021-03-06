/*****************************************************************************
*
* Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
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
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                         avtParallelCoordinatesFilter.h                    //
// ************************************************************************* //

#ifndef AVT_PARALLEL_COORDINATES_FILTER_H
#define AVT_PARALLEL_COORDINATES_FILTER_H

#include <avtSIMODataTreeIterator.h>
#include <avtHistogramSpecification.h>

#include <ParallelCoordinatesAttributes.h>

#include <vector>
#include <string>

#define PCP_CTX_BRIGHTNESS_LEVELS         100
#define PCP_MAX_TIMESTEPS                 12

class vtkDataSet;
class vtkPolyData;
class vtkCellArray;
class vtkPoints;


// ****************************************************************************
//  Class: avtParallelCoordinatesFilter
//
//  Purpose: A filter that outputs plot data for the ParallelCoordinates plot.
//
//  Programmer: Jeremy Meredith
//  Creation:   January 31, 2008
//
//  Note: Much of the initial version of this plot was distilled from an
//        earlier version of Mark Blair's ParallelAxis plot.
//
//  Modifications:
//    Jeremy Meredith, Mon Feb  4 15:46:42 EST 2008
//    Cleaned up some unused things and other refactoring.
//
//    Jeremy Meredith, Thu Feb  7 17:39:52 EST 2008
//    Handle array variables as sole input variable, which makes the
//    ordered axis array names in the attributes be empty.
//    Also handle X positions defined by binning in array vars.
//
//    Hank Childs, Mon Feb 23 18:01:41 PST 2009
//    Added methods for creating named selections.
//
//    Jeremy Meredith, Wed Feb 25 13:37:08 EST 2009
//    Use new histogram structure for context and (optionally) focus.
//    Add some multiple-timestep support.
//
//    Hank Childs, Mon Apr  6 13:07:18 PDT 2009
//    Added method for registering named selections.
//
//    Jeremy Meredith, Mon Apr 27 10:44:49 EDT 2009
//    Added ability to draw focus as color-graduated bins, merging
//    context- and focus-as-histogram-drawing routines.
//
//    Hank Childs, Thu Aug 26 13:47:30 PDT 2010
//    Change extents names.
//
//    Eric Brugger, Tue Aug 19 11:03:10 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtParallelCoordinatesFilter : public avtSIMODataTreeIterator
{
public:
                                avtParallelCoordinatesFilter(
                                    ParallelCoordinatesAttributes &atts);
    virtual                    ~avtParallelCoordinatesFilter();

    void                        ShouldCreateLabels(bool b) { return; }
    virtual const char         *GetType(void)
                                    { return "avtParallelCoordinatesFilter"; };
    virtual const char         *GetDescription(void)
                                    { return "Parallel coordinates plot"; };
    virtual void                ReleaseData(void);
    virtual avtNamedSelection  *CreateNamedSelection(avtContract_p, const std::string &);
    virtual void                RegisterNamedSelection(const std::string &s) 
                                              { namedSelections.push_back(s);};

protected:
    virtual avtContract_p       ModifyContract(avtContract_p);
    virtual avtDataTree_p       ExecuteDataTree(avtDataRepresentation *);

    virtual void                UpdateDataObjectInfo(void);
    virtual void                PreExecute(void);
    virtual void                PostExecute(void);

    void                        CreateLabels(void);

private:
    void                        ComputeActualDataExtentsOverAllDomains();

    void                        InitializeDataTupleInput();
    void                        CountDataTupleFocus(int ts,
                                                    const floatVector &tuple);
    void                        CountDataTupleContext(int ts,
                                                     const floatVector &tuple);

    void                        InitializeContextHistograms();
    void                        InitializeFocusHistograms();
    void                        CleanUpAllHistograms();

    void                        DrawHistogram(int ts, bool focus);
    void                        DrawContext(int ts);
    void                        DrawFocusHistograms(int ts);
    void                        PrepareForArrayVariable();
    std::string                 ConvertExtentsToCondition();
    std::string                 ConvertNamedSelectionToCondition();

    ParallelCoordinatesAttributes parCoordsAtts;
    
    bool                        isArrayVar;
    bool                        sendNullOutput;

    stringVector                focusLabels[PCP_MAX_TIMESTEPS];
    stringVector                contextLabels[PCP_MAX_TIMESTEPS];

    int                         axisCount;

    doubleVector                axisMinima;
    doubleVector                axisMaxima;
    doubleVector                axisXPositions;
    
    stringVector                namedSelections;

    boolVector                  applySubranges;
    bool                        extentsApplied;

    bool                        gotHistogramsFromDB;
    std::vector<avtHistogramSpecification*> histograms;
    std::vector<avtHistogramSpecification*> histogramsForSelectedRegion;

    // Data and methods to support old full-data-point focus rendering
    vtkPolyData                *dataCurvePolyData;
    vtkPoints                  *dataCurvePoints;
    vtkCellArray               *dataCurveLines;
    vtkCellArray               *dataCurveVerts;
    int outputCurveCount;
    void DrawFocusPolyLines();
    void InitializeFocusPolyData();
    void AppendDataTupleFocus(const floatVector&);

    virtual avtNamedSelection  *CreateNamedSelectionThroughTraversal(avtContract_p, const std::string &);
    virtual avtNamedSelection  *CreateDBAcceleratedNamedSelection(avtContract_p, const std::string &);
};



#endif
