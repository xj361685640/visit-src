/*****************************************************************************
*
* Copyright (c) 2000 - 2016, Lawrence Livermore National Security, LLC
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
//                         avtOpenFOAMFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_OpenFOAM_FILE_FORMAT_H
#define AVT_OpenFOAM_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#include <utility>
#include <map>
#include <vector>
#include <vectortypes.h>
#include <avtTypes.h>

class DBOptionsAttributes;
class visit_vtkPOpenFOAMReader;
class vtkStdString;
class vtkMultiBlockDataSet;

// ****************************************************************************
//  Class: avtOpenFOAMFileFormat
//
//  Purpose:
//      Reads in OpenFOAM files as a plugin to VisIt.
//
//  Programmer: biagas2 -- generated by xml2avt
//  Creation:   Tue May 21 11:07:32 PDT 2013
//
// ****************************************************************************

class avtOpenFOAMFileFormat : public avtMTMDFileFormat
{
  public:
                           avtOpenFOAMFileFormat(const char *, DBOptionsAttributes *);
    virtual               ~avtOpenFOAMFileFormat() {;};

    virtual void           GetTimes(std::vector<double> &);
    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "OpenFOAM"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);
    // Number of variables dynamic
    virtual bool           HasInvariantMetaData(void) const { return true; }
    // Number of Domains dynamic
    virtual bool           HasInvariantSIL(void) const      { return true; }
    virtual void           ActivateTimestep(int);

  protected:
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
    void                   SelectPatchArray(int, const std::string &);
    avtVarType             OpenFOAMClassNameToVarType(const vtkStdString &cn);
    void                   AddVarToMetaData(avtVarType, avtDatabaseMetaData *, 
                                            std::string, std::string,
                                            avtCentering);
    vtkDataArray          *ReadVar(int, int, const char *);
    vtkDataSet            *GetBlock(vtkMultiBlockDataSet *, bool);
    visit_vtkPOpenFOAMReader    *reader;
    doubleVector           timeSteps;
    bool                   convertCellToPoint;
    bool                   readZones;
    int                    currentTimeStep;
    std::string            currentMesh;
    std::string            currentPatch;
};


#endif
