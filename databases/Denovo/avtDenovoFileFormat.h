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
//                            avtDenovoFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_Denovo_FILE_FORMAT_H
#define AVT_Denovo_FILE_FORMAT_H

#include <hdf5.h>
#include <avtSTMDFileFormat.h>
#include <InvalidFilesException.h>

#include <vector>

class avtMaterial;

// ****************************************************************************
//  Class: avtDenovoFileFormat
//
//  Purpose:
//      Reads in Denovo files as a plugin to VisIt.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Fri Oct 6 11:06:44 PDT 2017
//
// ****************************************************************************

class avtDenovoFileFormat : public avtSTMDFileFormat
{
  public:
                       avtDenovoFileFormat(const char *);
    virtual           ~avtDenovoFileFormat() {}

    virtual void      *GetAuxiliaryData(const char *var,
                                        int domain,
                                        const char *type,
                                        void *args, 
                                        DestructorFunction &df);
    

    //
    // If you know the cycle number, overload this function.
    // Otherwise, VisIt will make up a reasonable one for you.
    //
    // virtual int         GetCycle(void);
    //

    virtual const char    *GetType(void)   { return "Denovo"; }
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

  protected:
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);
    void LoadFile();
    avtMaterial *GetMaterial(const std::string &var, int domain);

    bool fileLoaded;
    hid_t fileId;

    //Meta data.
    struct varInfo
    {
        varInfo() {}
        varInfo(hid_t fileId, const std::string &nm, const std::string &fileName) : name(nm)
        {
            if ((varId = H5Dopen(fileId, name.c_str(), H5P_DEFAULT)) < 0)
                EXCEPTION1(InvalidFilesException, fileName);
            if ((spaceId = H5Dget_space(varId)) < 0)
                EXCEPTION1(InvalidFilesException, fileName);
            
            dims.resize(H5Sget_simple_extent_ndims(spaceId));
            H5Sget_simple_extent_dims(spaceId, &dims[0], NULL);
            cout<<nm<<": dims= "<<dims.size()<<endl;
            /*
            if (dims.size() > 1)
                cout<<"CONSTRUCTION: "<<nm<<": "<<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<" "<<dims[3]<<endl;
            */

            size_t pos = name.rfind("/");
            if (pos == std::string::npos)
                EXCEPTION1(InvalidFilesException, fileName);
        
            std::string vName = name.substr(pos+1);
            if (dims.size() < 4)
            {
                varNames.push_back(vName);
                cout<<"     SIMPLE "<<endl;
            }
            else
            {
                char tmp[64];
                for (int i = 0; i < dims[0]; i++)
                {
                    sprintf(tmp, "%s_%d", vName.c_str(), i);
                    varNames.push_back(tmp);
                }
            }
        }
        
        std::string name;
        std::vector<std::string> varNames;
        hid_t varId, spaceId;
        std::vector<hsize_t> dims;
    };
    std::vector<varInfo> coordMetaData;
    std::vector<varInfo> varMetaData;

    struct mixTableEntry
    {
        int row, col;
        double val;
    };
    std::vector<mixTableEntry> mixTable;
    std::vector<std::string> materialNames, materialColors;
};


#endif
