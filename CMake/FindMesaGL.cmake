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
#
#****************************************************************************/

#
# if VISIT_MESAGL_DIR is set, then it was determined that system GL lib
# is insufficient for running VisIt (VTK 8), and Mesa-17x was compiled,
# as was LLVM.
#
# This Find module simply determines the correct soname's for mesa's GL and 
# LLVM and copies them to the build-dir/lib/mesagl.
#
# This new lib path will be used to set LD_LIBRARY_PATH at run-time for gui
# and viewer (running with window).
#

if (VISIT_MESAGL_DIR)

  find_library(MESAGL_LIBRARY GL  PATH ${VISIT_MESAGL_DIR}/lib NO_DEFAULT_PATH)
  if (MESAGL_LIBRARY)
      execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory
                      ${VISIT_BINARY_DIR}/lib/mesagl
                      RESULT_VARIABLE GEN_MESAGL_DIR)

      if(NOT "${GEN_MESAGL_DIR}" STREQUAL "0")
          message(WARNING "Failed to create lib/mesagl/")
      endif()

      get_filename_component(MESAGL_LIB ${MESAGL_LIBRARY} NAME)
      execute_process(COMMAND objdump -p ${MESAGL_LIBRARY}
                      COMMAND grep SONAME
                      RESULT_VARIABLE MESAGL_SONAME_RESULT
                      OUTPUT_VARIABLE MESAGL_SONAME
                      ERROR_VARIABLE MESAGL_SONAME_ERROR)
      if(MESAGL_SONAME)
          string(REPLACE "SONAME" "" MESAGL_SONAME ${MESAGL_SONAME})
          string(STRIP ${MESAGL_SONAME} MESAGL_SONAME)
          set(MESAGL_LIBRARY ${VISIT_MESAGL_DIR}/lib/${MESAGL_SONAME})
      endif()

      execute_process(COMMAND ${CMAKE_COMMAND} -E copy 
                              ${MESAGL_LIBRARY}
                              ${VISIT_BINARY_DIR}/lib/mesagl/)

      set(OPENGL_gl_LIBRARY ${MESAGL_LIBRARY})
      set(OPENGL_LIBRARIES ${MESAGL_LIBRARY})

      # need install commands as well, but I think they should go in
      # lib/CMakeLists.txt
  else()
      message(FATAL_ERROR "VISIT_MESAGL_DIR provided, but it doesn't contain GL library")
  endif()

  find_library(MESAGLU_LIBRARY GLU  PATH ${VISIT_MESAGL_DIR}/lib NO_DEFAULT_PATH)
  if (MESAGLU_LIBRARY)
      get_filename_component(MESAGLU_LIB ${MESAGLU_LIBRARY} NAME)
      execute_process(COMMAND objdump -p ${MESAGLU_LIBRARY}
                      COMMAND grep SONAME
                      RESULT_VARIABLE MESAGLU_SONAME_RESULT
                      OUTPUT_VARIABLE MESAGLU_SONAME
                      ERROR_VARIABLE MESAGLU_SONAME_ERROR)
      if(MESAGLU_SONAME)
          string(REPLACE "SONAME" "" MESAGLU_SONAME ${MESAGLU_SONAME})
          string(STRIP ${MESAGLU_SONAME} MESAGLU_SONAME)
          set(MESAGLU_LIBRARY ${VISIT_MESAGL_DIR}/lib/${MESAGLU_SONAME})
      endif()

      execute_process(COMMAND ${CMAKE_COMMAND} -E copy 
                              ${MESAGLU_LIBRARY}
                              ${VISIT_BINARY_DIR}/lib/mesagl/)

      set(OPENGL_glu_LIBRARY ${MESAGLU_LIBRARY})
      # need install commands as well, but I think they should go in
      # lib/CMakeLists.txt
  endif()

  if (VISIT_LLVM_DIR)
    find_library(MESAGL_LLVM_LIBRARY LLVM  PATH ${VISIT_LLVM_DIR}/lib NO_DEFAULT_PATH)
    if (MESAGL_LLVM_LIBRARY)
        get_filename_component(MESAGL_LLVM_LIB ${MESAGL_LLVM_LIBRARY} NAME)

        execute_process(COMMAND objdump -p ${MESAGL_LLVM_LIBRARY}
                        COMMAND grep SONAME
                        RESULT_VARIABLE MESAGL_LLVM_SONAME_RESULT
                        OUTPUT_VARIABLE MESAGL_LLVM_SONAME
                        ERROR_VARIABLE MESAGL_LLVM_SONAME_ERROR)

        if(MESAGL_LLVM_SONAME)
            string(REPLACE "SONAME" "" MESAGL_LLVM_SONAME ${MESAGL_LLVM_SONAME})
            string(STRIP ${MESAGL_LLVM_SONAME} MESAGL_LLVM_SONAME)
            set(MESAGL_LLVM_LIBRARY ${VISIT_LLVM_DIR}/lib/${MESAGL_LLVM_SONAME})
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} -E copy 
                              ${MESAGL_LLVM_LIBRARY}
                              ${VISIT_BINARY_DIR}/lib/mesagl/)

    list(APPEND OPENGL_gl_LIBRARY ${MESAGL_LLVM_LIBRARY})
    list(APPEND OPENGL_LIBRARIES ${MESAGL_LLVM_LIBRARY})
    endif() 
  endif(VISIT_LLVM_DIR) 
endif(VISIT_MESAGL_DIR)
