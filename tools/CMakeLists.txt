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
#   Kathleen Bonnell, Wed Jun 2 15:11:22 PST 2010
#   Disable MakeMili on windows.
#
#   Kathleen Bonnell, Fri Jun  4 14:46:56 PDT 2010
#   Change ${MILI_FOUND} to MILI_FOUND.
#
#   Kathleen Bonnell, Wed Jan 05 10:25:13 PST 2010
#   Add FOLDER property.
#
#   Cyrus Harrison, Fri Apr 29 15:33:38 PDT 2011
#   Added mrgtree2dot utility.
#
#   Brad Whitlock, Thu Oct 20 12:38:14 PDT 2011
#   Do not build writer when we're doing a static build.
#
#   Brad Whitlock, Wed May 23 17:10:05 PDT 2012
#   Add usedataserver example program.
#
#   Eric Brugger, Wed Dec  5 13:17:20 PST 2012
#   Add xmf_writer.
#
#   Eric Brugger, Wed Apr 17 12:00:47 PDT 2013
#   Also build qtssh on unix.
#
#   Eric Brugger, Wed Dec 17 12:37:22 PST 2014
#   Add avtexamples.
#
#   Kathleen Biagas, Dec 22, 2014
#   Add ability to turn off building of avt examples.
#
#   Eric Brugger, Thu Oct  1 08:34:37 PDT 2015
#   Add add_visit_searchpath.
#
#****************************************************************************/

MACRO(VISIT_TOOLS_ADD_FOLDER type)
    IF(${ARGC} GREATER 1)
        SET_TARGET_PROPERTIES(${ARGN} PROPERTIES FOLDER tools/${type})
    ELSE(${ARGC} GREATER 1)
        SET_TARGET_PROPERTIES(${type} PROPERTIES FOLDER tools/${type})
    ENDIF(${ARGC} GREATER 1)
ENDMACRO(VISIT_TOOLS_ADD_FOLDER)

IF(VISIT_BUILD_DIAGNOSTICS)
    ADD_SUBDIRECTORY(diagnostics)
ENDIF()

IF(VISIT_DBIO_ONLY OR VISIT_ENGINE_ONLY OR VISIT_SERVER_COMPONENTS_ONLY)
    ADD_SUBDIRECTORY(convert)
ELSE(VISIT_DBIO_ONLY OR VISIT_ENGINE_ONLY OR VISIT_SERVER_COMPONENTS_ONLY)
    # We always want these to be built
    IF(SILO_FOUND AND NOT WIN32)
        ADD_SUBDIRECTORY(add_visit_searchpath)
    ENDIF(SILO_FOUND AND NOT WIN32)
    ADD_SUBDIRECTORY(annotations)
    IF(VISIT_BUILD_AVTEXAMPLES AND NOT VISIT_STATIC)
        ADD_SUBDIRECTORY(avtexamples)
    ENDIF(VISIT_BUILD_AVTEXAMPLES AND NOT VISIT_STATIC)
    ADD_SUBDIRECTORY(convert)
    ADD_SUBDIRECTORY(embedviewer)
    ADD_SUBDIRECTORY(imagetools)
    IF(MILI_FOUND AND NOT WIN32)
        ADD_SUBDIRECTORY(makemili)
    ENDIF(MILI_FOUND AND NOT WIN32)
    IF(NOT WIN32)
        ADD_SUBDIRECTORY(mcurvit)
        ADD_SUBDIRECTORY(clipeditor)
    ENDIF(NOT WIN32)
    ADD_SUBDIRECTORY(mpeg2encode)
    IF(SILO_FOUND)
        ADD_SUBDIRECTORY(mrgtree2dot)
    ENDIF(SILO_FOUND)
    ADD_SUBDIRECTORY(protocol)
    IF(WIN32 OR UNIX)
        ADD_SUBDIRECTORY(qtssh)
    ENDIF(WIN32 OR UNIX)
    IF(VISIT_PYTHON_SCRIPTING AND NOT VISIT_STATIC)
        ADD_SUBDIRECTORY(dataserver)
        ADD_SUBDIRECTORY(writer)
    ENDIF(VISIT_PYTHON_SCRIPTING AND NOT VISIT_STATIC)
    IF(HDF5_FOUND AND NOT WIN32)
        ADD_SUBDIRECTORY(xdmf_writer)
    ENDIF(HDF5_FOUND AND NOT WIN32)
    ADD_SUBDIRECTORY(xml)
    ADD_SUBDIRECTORY(xmledit)

    ADD_SUBDIRECTORY(DataManualExamples)
ENDIF(VISIT_DBIO_ONLY OR VISIT_ENGINE_ONLY OR VISIT_SERVER_COMPONENTS_ONLY)


# Maybe create a separate build system for all of these...
# ADD_SUBDIRECTORY(DataManualExamples)

# These do not need to be built:
# antialiased_shadows
# avt_do_add
# clidriver
# doxygenate
# escan
# surfcomp
# vtk_debug_parser

