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

#include <ViewerHostProfileSelector.h>

// ****************************************************************************
//  Constructor:  ViewerHostProfileSelector::ViewerHostProfileSelector
//
//  Programmer:  Kathleen Bonnell
//  Creation:    February 5, 2003 
//
//  Modifications:
//
// ****************************************************************************

ViewerHostProfileSelector::ViewerHostProfileSelector()
{
}

// ****************************************************************************
//  Destructor:  ViewerHostProfileSelector::~ViewerHostProfileSelector
//
//  Programmer:  Kathleen Bonnell 
//  Creation:    February 5, 2003 
//
//  Modifications:
//
// ****************************************************************************

ViewerHostProfileSelector::~ViewerHostProfileSelector()
{
}

// ****************************************************************************
//  Method:  ViewerHostProfileSelector::ClearCache
//
//  Purpose:
//    Erases previous settings for re-launching engines.
//    This will typically be called if the previous launch failed
//    or if the user closed the engine manually.
//
//  Arguments:
//    hostName   the host name of the remote engine
//
//  Programmer:  Jeremy Meredith
//  Creation:    August 14, 2002
//
// ****************************************************************************

void
ViewerHostProfileSelector::ClearCache(const std::string &hostName)
{
    cachedProfile.erase(hostName);
}


// ****************************************************************************
//  Method:  ViewerHostProfileSelector::AddRestartArgsToCachedProfile
//
//  Purpose:
//    Modify a cached profile to include the given arguments.
//
//  Arguments:
//    hostName   the host name of the remote engine
//    args       the arguments to save
//
//  Programmer:  Jeremy Meredith
//  Creation:    April  2, 2004
//
//  Modifications:
//    Jeremy Meredith, Thu Feb 18 15:25:27 EST 2010
//    Split HostProfile int MachineProfile and LaunchProfile.
//
//    Jeremy Meredith, Tue Jul 13 16:16:45 EDT 2010
//    Sometimes we just cache a dummy machine profile.  In these cases, we
//    still need to be able to save off command line args.  (These coincide
//    when someone adds -np 4 to the command line, for instance.)  So we
//    create an empty launch profile to use for this case.
//
// ****************************************************************************
void
ViewerHostProfileSelector::AddRestartArgsToCachedProfile(
                                          const std::string &hostName,
                                          const std::vector<std::string> &args)
{
    if (cachedProfile.count(hostName))
    {
        // If we don't have any launch profiles, add one!
        if (cachedProfile[hostName].GetNumLaunchProfiles() == 0)
        {
            cachedProfile[hostName].AddLaunchProfiles(LaunchProfile());
            cachedProfile[hostName].SetActiveProfile(0);
        }

        // This had better be true now......
        if (cachedProfile[hostName].GetActiveLaunchProfile())
        {
            std::vector<std::string> &a =
             cachedProfile[hostName].GetActiveLaunchProfile()->GetArguments();
            a.insert(a.end(), args.begin(), args.end());
        }
    }
}
