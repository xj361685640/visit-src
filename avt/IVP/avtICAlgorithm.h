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
//                              avtICAlgorithm.h                             //
// ************************************************************************* //

#ifndef AVT_IC_ALGORITHM_H
#define AVT_IC_ALGORITHM_H

#include <avtPICSFilter.h>
#include "avtIntegralCurve.h"
#include <vector>

// ****************************************************************************
// Class: avtICAlgorithm
//
// Purpose:
//    Abstract base class for integral curve algorithms.
//
// Programmer: Dave Pugmire
// Creation:   Mon Jan 26 13:25:58 EST 2009
//
// Modifications:
//
//    Dave Pugmire, Fri Feb  6 08:43:00 EST 2009
//    Add a SortIntegralCurves that takes a vector.
//
//   Dave Pugmire, Fri Feb  6 14:42:07 EST 2009
//   Add histogram to the statistics.
//
//   Dave Pugmire, Tue Mar 10 12:41:11 EDT 2009
//   Generalized domain to include domain/time.
//   
//   Dave Pugmire, Mon Mar 23 12:48:12 EDT 2009
//   Change how timings are reported/calculated.
//
//   Dave Pugmire, Mon Mar 23 18:33:10 EDT 2009
//   Make changes for point decomposed domain databases.
//
//   Dave Pugmire, Thu Mar 26 12:02:27 EDT 2009
//   Add counters for domain loading
//
//   Dave Pugmire, Tue Aug 18 09:10:49 EDT 2009
//   Add ability to restart integration of integral curves.
//
//   Dave Pugmire, Thu Sep 24 13:52:59 EDT 2009
//   Replace Execute() with RunAlgorithm(). Add a Pre/Post RunAlgorithm.
//
//   Dave Pugmire, Thu Dec  2 11:21:06 EST 2010
//   Add CheckNextTimeStepNeeded.
//
//   Dave Pugmire, Mon Dec 20 15:01:14 EST 2010
//   Added Sleep() method.
//
//   Dave Pugmire, Fri Jan 14 11:06:09 EST 2011
//   Added PostStepCallback() method.
//
//   David Camp, Mon Aug 22 12:59:31 PDT 2011
//   Added SetDomain method, which forwards the call to the PICs filter.
//
//   Dave Pugmire, Mon Dec 15 11:00:23 EST 2014
//   Add a #steps taken counter.
//
// ****************************************************************************

class avtICAlgorithm
{
  public:
    avtICAlgorithm( avtPICSFilter *picsFilter );
    virtual ~avtICAlgorithm();

    //Execution of the algorithm.
    void                      Execute();
    bool                      CheckNextTimeStepNeeded(int curTimeSlice);

    virtual void              Initialize(std::vector<avtIntegralCurve *> &);
    virtual void              RestoreInitialize(std::vector<avtIntegralCurve *> &, int curTimeSlice) {}
    virtual void              ResetIntegralCurvesForContinueExecute();
    virtual void              ActivateICsForNextTimeStep();
    virtual void              PostExecute();
    virtual void              GetTerminatedICs(std::vector<avtIntegralCurve *> &v);
    virtual void              AddIntegralCurves(std::vector<avtIntegralCurve*> &ics) = 0;
    virtual void              DeleteIntegralCurves(std::vector<int> &icIDs);
    virtual bool              PostStepCallback() { return false; }

    virtual void              UpdateICsDomain( int curTimeSlice );

  protected:
    virtual void              RunAlgorithm() = 0;
    virtual void              PreRunAlgorithm() {}
    virtual void              PostRunAlgorithm();
    
    std::string               activeICInfo() const;
    std::string               terminatedICInfo() const;
    std::string               inactiveICInfo() const;

    virtual const char*       AlgoName() const = 0;
    
    //Helper accessor funcstions to the filter.
    avtIVPSolver *            GetSolver() {return picsFilter->solver; }
    virtual bool              ICInBlock(avtIntegralCurve *ic, BlockIDType &dom)
    { return picsFilter->avtPICSFilter::ICInBlock(ic, dom); }
    virtual void              AdvectParticle(avtIntegralCurve *ic);
    vtkDataSet               *GetDomain(avtIntegralCurve *ic);
    vtkDataSet               *GetDomain(const BlockIDType &dom, const avtVector &pt);
    virtual bool              DomainLoaded(BlockIDType &dom) const
    { return picsFilter->avtPICSFilter::BlockLoaded(dom); }
    void                      SetDomain(avtIntegralCurve *ic)
    { return picsFilter->avtPICSFilter::FindCandidateBlocks(ic); }
    
    bool                      OwnDomain(BlockIDType &dom)
    {return picsFilter->avtPICSFilter::OwnDomain(dom); }
    int                       DomainToRank(BlockIDType &dom)
    {return picsFilter->avtPICSFilter::DomainToRank(dom); }
    int                       DomCacheSize() const { return picsFilter->cacheQLen; }

    //Utility functions.
    virtual void              SortIntegralCurves(std::list<avtIntegralCurve *> &);
    virtual void              SortIntegralCurves(std::vector<avtIntegralCurve *> &);
    void                      Sleep(long nanoSec=10) const;

public:
    virtual void              SetAllSeedsSentToAllProcs( bool flag )
    { allSeedsSentToAllProcs = flag; };
    
protected:
    //Statistics and timers.
    class ICStatistics
    {
      public:
        ICStatistics(std::string s="")
        {
            nm = s;
            value = 0.0;
            min=max=mean=sigma=total=0.0;
            histogram.resize(0);
        }
        double min, max, mean, sigma, total;
        std::vector<double> histogram;
        double value;
        std::string nm;

        ostream& operator<<(std::ostream &out) const;
    };

    virtual void              ReportStatistics();
    void                      CompileAlgorithmStatistics();
    virtual void              CompileTimingStatistics();
    virtual void              CompileCounterStatistics();
    virtual void              CalculateExtraTime();    
    virtual void              ComputeStatistic(ICStatistics &stats);
    virtual void              ComputeDomainLoadStatistic();
    virtual void              ReportStatistics(ostream &os);
    virtual void              ReportTimings(ostream &os, bool totals);
    virtual void              ReportCounters(ostream &os, bool totals);

    void                      PrintTiming(ostream &os,
                                          const char *str, 
                                          const ICStatistics &s,
                                          const ICStatistics &t,
                                          bool total);
    void                      PrintCounter(ostream &os,
                                           const char *str,
                                           const ICStatistics &s,
                                           bool total);

    avtPICSFilter             *picsFilter;

    //Timers.
    ICStatistics              TotalTime, IOTime, IntegrateTime, SortTime,
                              ExtraTime;
    //Counters.
    ICStatistics              IntegrateCnt, IntegrateStepCnt, DomLoadCnt, DomPurgeCnt;

    std::list<avtIntegralCurve *> terminatedICs, activeICs, inactiveICs;

    // Flag if all seeds are sent to all process
    bool                      allSeedsSentToAllProcs;
    int                       numDomains, numSeedPoints;  

    //Special counters.
    int                       domainsUsed, totDomainsLoaded, domainLoadedMin, domainLoadedMax;
    int                       globalDomainsUsed, globalTotDomainsLoaded, globalDomainLoadedMin, globalDomainLoadedMax;
    double                    avgDomainLoaded, globalAvgDomainLoaded;
};

#endif
