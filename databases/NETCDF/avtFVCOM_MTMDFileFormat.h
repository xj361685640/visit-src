/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
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
//                            avtFVCOMFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_FVCOM_MTMD_FILE_FORMAT_H
#define AVT_FVCOM_MTMD_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>
#include <avtMTMDFileFormatInterface.h>

#include <vector>

class NETCDFFileObject;
class avtFVCOMReader;
    
// ****************************************************************************
//  Class: avtFVCOM_MTMDFileFormat
//
//  Purpose:
//      Reads in FVCOM Master file as a plugin to VisIt.
//
//  Programmer: dstuebe -- generated by xml2avt
//  Creation:   Wed Aug 16 16:40:22 PST 2006
//
// ****************************************************************************

class avtFVCOM_MTMDFileFormat : public avtMTMDFileFormat
{
  public:
   static bool        Identify(NETCDFFileObject *);   

   static avtFileFormatInterface *CreateInterface(NETCDFFileObject *f,
                         const char *const *list, int nList, int nBlock);

                       avtFVCOM_MTMDFileFormat(const char *, NETCDFFileObject *);
                       avtFVCOM_MTMDFileFormat(const char *);
    virtual           ~avtFVCOM_MTMDFileFormat();

    virtual void       Init(void);

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    
    virtual void        GetCycles(std::vector<int> &);
    virtual void        GetTimes(std::vector<double> &);

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "FVCOM"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

    virtual void          *GetAuxiliaryData(const char *var, int timestate,
                                            int domain,
                                            const char *type, void *args,
                                            DestructorFunction &);

   protected:
    // DATA MEMBERS
   NETCDFFileObject      *fileObject;

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

    bool  init;
    bool IsGeoRef;
    
    //    int status;

    size_t ndoms;
    size_t nfnames;
    size_t ntime;
    size_t ntwo;
    
    std::vector<avtFVCOMReader *> domainFiles;

    private:
   
    const char *keysuffix;
};


#endif
