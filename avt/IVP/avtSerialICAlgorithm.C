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
//                              avtSerialICAlgorithm.C                       //
// ************************************************************************* //

#include "avtSerialICAlgorithm.h"
#include <TimingsManager.h>
#include <avtParallel.h>
#include <DebugStream.h>
#include <VisItStreamUtil.h>


// ****************************************************************************
//  Method: avtSerialICAlgorithm::avtSerialICAlgorithm
//
//  Purpose:
//      avtSerialICAlgorithm constructor.
//
//  Programmer: Dave Pugmire
//  Creation:   January 27, 2009
//
//  Modifications:
//
// ****************************************************************************

avtSerialICAlgorithm::avtSerialICAlgorithm( avtPICSFilter *picsFilter )
    : avtICAlgorithm(picsFilter)
{
}

// ****************************************************************************
//  Method: avtSerialICAlgorithm::~avtSerialICAlgorithm
//
//  Purpose:
//      avtSerialICAlgorithm destructor.
//
//  Programmer: Dave Pugmire
//  Creation:   January 27, 2009
//
// ****************************************************************************

avtSerialICAlgorithm::~avtSerialICAlgorithm()
{
}

// ****************************************************************************
//  Method: avtSerialICAlgorithm::Initialize
//
//  Purpose:
//      Initialization.
//
//  Programmer: Dave Pugmire
//  Creation:   January 27, 2009
//
//  Modifications:
//
//   Dave Pugmire, Mon Mar 23 18:33:10 EDT 2009
//   Make changes for point decomposed domain databases.
//
//   Hank Childs, Fri Apr  3 16:26:24 PDT 2009
//   Change parallelization strategy, since it was loading up on the last
//   processor and we want it to be more spread out.
//
//   Hank Childs, Sun Jun  6 12:21:30 CDT 2010
//   Change name of method called to AddIntegralCurves.
//
// ****************************************************************************

void
avtSerialICAlgorithm::Initialize(std::vector<avtIntegralCurve *> &seedPts)
{
    avtICAlgorithm::Initialize(seedPts);

    AddIntegralCurves(seedPts);
}

// ****************************************************************************
//  Method: avtSerialICAlgorithm::Initialize
//
//  Purpose:
//      Do a restore initialization, don't add ICs that are not in current
//  time slice.
//
//  Programmer: David Camp
//  Creation:   March 5, 2012
//
//  Modifications:
//
// ****************************************************************************

void
avtSerialICAlgorithm::RestoreInitialize(std::vector<avtIntegralCurve *> &ics, int curTimeSlice)
{
    for (size_t i = 0; i < ics.size(); i++)
    {
        avtIntegralCurve *s = ics[i];

        if (!s->blockList.empty() &&
            s->blockList.front().timeStep == curTimeSlice)
        {
            s->status.ClearAtTemporalBoundary();
            SetDomain(s);
            activeICs.push_back(s);
        }
        else
        {
            terminatedICs.push_back(s);
        }
    }
}

// ****************************************************************************
//  Method: avtSerialICAlgorithm::AddIntegralCurves
//
//  Purpose:
//      Add integral curves
//
//  Programmer: Dave Pugmire
//  Creation:   December 3, 2009
//
//  Modifications:
//
//   Hank Childs, Thu Jun  3 10:22:16 PDT 2010
//   Use new name "GetCurrentLocation".
//
// ****************************************************************************

void
avtSerialICAlgorithm::AddIntegralCurves(std::vector<avtIntegralCurve *> &ics)
{
    int nSeeds = ics.size();
    int i0 = 0, i1 = nSeeds;

 #ifdef PARALLEL
    if( allSeedsSentToAllProcs )
    {
        int rank = PAR_Rank();
        int nProcs = PAR_Size();

        int nSeedsPerProc = (nSeeds / nProcs);
        int oneExtraUntil = (nSeeds % nProcs);
    
        if (rank < oneExtraUntil)
        {
            i0 = (rank)*(nSeedsPerProc+1);
            i1 = (rank+1)*(nSeedsPerProc+1);
        }
        else
        {
            i0 = (rank)*(nSeedsPerProc) + oneExtraUntil;
            i1 = (rank+1)*(nSeedsPerProc) + oneExtraUntil;
        }

        // When integrating in both directions make sure the forward
        // and backwards seed are on the same rank. If the number of
        // seeds for this rank is odd then adjust the seed count.
        if (picsFilter->GetIntegrationDirection() ==
            PICS_INTEGRATE_BOTH_DIRECTIONS &&
            (i1-i0) % 2)
        {
          // Odd rank so give up a seed to make the seed count even.
          if( rank % 2 == 1 )
            i0 += 1;
          
          // Even rank so add a seed to make the seed count even.
          else if( rank % 2 == 0 )
            i1 += 1;
        }
    
        // Delete the seeds not needed.
        for (int i = 0; i < i0; i++)
            delete ics[i];
        for (int i = i1; i < nSeeds; i++)
            delete ics[i];
    }
#endif
    
    for (int i = i0; i < i1; i++)
    {
        inactiveICs.push_back(ics[i]);
        
#ifdef USE_IC_STATE_TRACKING
        ics[i]->InitTrk();
#endif
    }

    if (DebugStream::Level1()) 
    {
      if( i0 < i1 )
      {
        debug1 << "Proc " << PAR_Rank() << " has " << (i1-i0) << " seeds: "
               << i0 << " to " << (i1-1) << " of " << nSeeds << " total seeds"
               << std::endl;
      }
      else
      {
        debug1 << "Proc " << PAR_Rank() << " has no seeds " << std::endl;
      }
    }
}

// ****************************************************************************
// Method:  avtSerialICAlgorithm::ActivateICs()
//
// Purpose:
//   Move ICs from inactive to active list, as possible.
//
// Programmer:  Dave Pugmire
// Creation:    May 30, 2012
//
// ****************************************************************************

void
avtSerialICAlgorithm::ActivateICs()
{
    std::list<avtIntegralCurve *>::iterator it = inactiveICs.begin();

    while (it != inactiveICs.end())
    {
        if (!(*it)->status.EncounteredTemporalBoundary())
        {
            activeICs.push_back(*it);
            it = inactiveICs.erase(it);
        }
        else
            it++;
    }
    
    SortIntegralCurves(activeICs);
}

// ****************************************************************************
//  Method: avtSerialICAlgorithm::RunAlgorithm
//
//  Purpose:
//      Execute the serial integral curve algorithm.
//
//  Programmer: Dave Pugmire
//  Creation:   January 27, 2009
//
//  Modifications:
//
//   Dave Pugmire, Mon Mar 23 18:33:10 EDT 2009
//   Make changes for point decomposed domain databases.
//
//   Hank Childs, Sat Apr 11 23:18:32 CDT 2009
//   Make an explicit call to GetDomain before calling AdvectParticle.
//   If we don't make this call, AdvectParticle will call GetDomain for 
//   us.  But by calling it explicitly, it goes through the avtICAlgorithm
//   bookkeeping logic, meaning that I/O will correctly be counted as I/O,
//   instead of being rolled in with integration time.
//
//   Dave Pugmire, Thu Sep 24 13:52:59 EDT 2009
//   Change Execute to RunAlgorithm.
//
//   Dave Pugmire, Thu Dec  3 13:28:08 EST 2009
//   Move some initialization into RunAlgorithm.
//
//   Hank Childs, Sat Nov 27 16:52:12 PST 2010
//   Add progress reporting.
//
//   David Camp, Mon Aug 15 09:36:04 PDT 2011
//   Pathline could have domains set to -1, which would cause them to be put
//   in the oob list and continuously process (hung process).
//
// ****************************************************************************

void
avtSerialICAlgorithm::RunAlgorithm()
{
    while (1)
    {
        ActivateICs();
        if (activeICs.empty())
            break;
        
        while (!activeICs.empty())
        {
            avtIntegralCurve *ic = activeICs.front();
            activeICs.pop_front();
            GetDomain(ic);
            do
            {
                AdvectParticle(ic);
            }
            while (ic->status.Integrateable() &&
                   !ic->blockList.empty() &&
                   DomainLoaded(ic->blockList.front()));
            
            // If the user termination criteria was reached so terminate the IC.
            if( ic->status.TerminationMet() )
                terminatedICs.push_back(ic);
            else if (ic->status.EncounteredSpatialBoundary())
                inactiveICs.push_back(ic);
            // Some other termination criteria was reached so terminate the IC.
            else
                terminatedICs.push_back(ic);

        }
    }
}
