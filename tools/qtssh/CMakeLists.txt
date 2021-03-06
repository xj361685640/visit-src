#*****************************************************************************
#
# Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
# Produced at the Lawrence Livermore National Laboratory
# LLNL-CODE-442911
# All rights reserved.
#
# This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
# full copyright notice is contained in the file COPYRIGHT located at the root
# of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
#
# Redistribution  and  use  in  source  and  binary  forms,  with  or  without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of  source code must  retain the above  copyright notice,
#    this list of conditions and the disclaimer below.
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
#    documentation and/or other materials provided with the distribution.
#  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
#    be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
# ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
# LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
# DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
# SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
# CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
# LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
# OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.
#
# Modifications:
#   Kathleen Bonnell, Wed May 5 12:07:54 PST 2010
#   Disable optimization.
# 
#   Kathleen Bonnell, Wed Jan 05 10:25:13 PST 2010
#   Add FOLDER property.
#
#   Brad Whitlock, Mon May 21 14:27:34 PST 2012
#   Turn qtssh back into a console application.
#
#   Brad Whitlock, Tue Jun 12 16:14:32 PST 2012
#   Redo qtssh using new sources and refactored viewer windows.
#
#   Eric Brugger, Wed Apr 17 12:02:02 PDT 2013
#   Create a linux version of qtssh.
#
#   Brad Whitlock, Fri Jun  7 22:03:52 PDT 2013
#   Static build fixes.
#
#   Kevin Griffin, Tue Jan 17 10:29:26 PST 2017
#   Upgraded source code to version 0.67
#
#****************************************************************************/

# All of the platform independent plink sources.
set(PLINK_CORE_SOURCES
    be_all_s.c
    callback.c
    cmdline.c
    conf.c
    cproxy.c
    ldisc.c
    logging.c
    misc.c
    noterm.c
    pgssapi.c
    pinger.c
    portfwd.c
    proxy.c
    raw.c
    rlogin.c
    settings.c
    ssh.c
    sshaes.c
    ssharcf.c
    sshblowf.c
    sshbn.c
    sshcrc.c
    sshcrcda.c
    sshdes.c
    sshdh.c
    sshdss.c
    sshgssc.c
    sshmd5.c
    sshpubk.c
    sshrand.c
    sshrsa.c
    sshsh256.c
    sshsh512.c
    sshsha.c
    sshshare.c
    sshzlib.c
    telnet.c
    timing.c
    tree234.c
    version.c
    wildcard.c
    x11fwd.c
)

# All of the windows specific plink sources.
set(PLINK_WINDOWS_SOURCES
    errsock.c
    windows/plink.rc
    windows/putty.ico
    windows/wincapi.c
    windows/wincons.c
    windows/windefs.c
    windows/wingss.c
    windows/winhandl.c
    windows/winhsock.c
    windows/winmisc.c
    windows/winnet.c
    windows/winnoise.c
    windows/winnojmp.c
    windows/winnpc.c
    windows/winnps.c
    windows/winpgntc.c
    windows/winproxy.c
    windows/winsecur.c
    windows/winser.c
    windows/winshare.c
    windows/winstore.c
    windows/wintime.c
    windows/winx11.c
)

# All of the unix specific plink sources.
set(PLINK_UNIX_SOURCES
    time.c
    unix/ux_x11.c
    unix/uxagentc.c
    unix/uxcons.c
    unix/uxgss.c
    unix/uxmisc.c
    unix/uxnet.c
    unix/uxnoise.c
    unix/uxpeer.c
    unix/uxproxy.c
    unix/uxsel.c
    unix/uxser.c
    unix/uxshare.c
    unix/uxsignal.c
    unix/uxstore.c
)

if(WIN32)
    set(PLINK_SOURCES ${PLINK_CORE_SOURCES} ${PLINK_WINDOWS_SOURCES})
else()
    set(PLINK_SOURCES ${PLINK_CORE_SOURCES} ${PLINK_UNIX_SOURCES})
endif()

set(QTSSH_SOURCES
    qtssh.cpp
    ${VISIT_SOURCE_DIR}/viewer/main/ui/VisItChangeUsernameWindow.C
    ${VISIT_SOURCE_DIR}/viewer/main/ui/VisItPasswordWindow.C
)

if(WIN32)
    list(APPEND QTSSH_SOURCES qtsshmain.c)
else()
    list(APPEND QTSSH_SOURCES uxqtsshmain.c)
endif()

# The subset of the sources that have Q_OBJECT in their header.
set(QTSSH_MOC_SOURCES
    ${VISIT_SOURCE_DIR}/viewer/main/ui/VisItChangeUsernameWindow.h
    ${VISIT_SOURCE_DIR}/viewer/main/ui/VisItPasswordWindow.h
)
qt_wrap_cpp(qtssh QTSSH_SOURCES ${QTSSH_MOC_SOURCES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VISIT_BINARY_DIR}/include
    ${VISIT_SOURCE_DIR}/viewer/main/ui
    ${VISIT_COMMON_INCLUDES}
)

if(WIN32)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/windows)
else()
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/charset
        ${CMAKE_CURRENT_SOURCE_DIR}/unix
    )
endif()

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) 

if(WIN32)
    add_definitions(-DSECURITY_WIN32)
endif()

set(RELEVANT_QT_LIBS 
    ${QT_QTGUI_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

if(VISIT_STATIC)
    MAC_NIB_INSTALL(qtssh)
    set(RELEVANT_QT_LIBS
        ${RELEVANT_QT_LIBS}
        ${QT_QTCORE_LIB_DEPENDENCIES}
        ${QT_QTGUI_LIB_DEPENDENCIES}
    )
endif()

add_executable(qtssh ${QTSSH_SOURCES} ${PLINK_SOURCES})
target_link_libraries(qtssh ${RELEVANT_QT_LIBS})
if(NOT WIN32)
  target_link_libraries(qtssh dl)
endif()

VISIT_INSTALL_TARGETS(qtssh)
VISIT_TOOLS_ADD_FOLDER(qtssh)


