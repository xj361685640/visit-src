/*****************************************************************************
*
* Copyright (c) 2000 - 2013, Lawrence Livermore National Security, LLC
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

#ifndef MODELBASEDCLUSTERINGATTRIBUTES_H
#define MODELBASEDCLUSTERINGATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: ModelBasedClusteringAttributes
//
// Purpose:
//    ModelBasedClustering Attributes
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class ModelBasedClusteringAttributes : public AttributeSubject
{
public:
    enum clusterAlgorithmType
    {
        EM,
        ACEM,
        APECM,
        APECMA,
        K_MEANS
    };

    // These constructors are for objects of this class
    ModelBasedClusteringAttributes();
    ModelBasedClusteringAttributes(const ModelBasedClusteringAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    ModelBasedClusteringAttributes(private_tmfs_t tmfs);
    ModelBasedClusteringAttributes(const ModelBasedClusteringAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~ModelBasedClusteringAttributes();

    virtual ModelBasedClusteringAttributes& operator = (const ModelBasedClusteringAttributes &obj);
    virtual bool operator == (const ModelBasedClusteringAttributes &obj) const;
    virtual bool operator != (const ModelBasedClusteringAttributes &obj) const;
private:
    void Init();
    void Copy(const ModelBasedClusteringAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectVar2();
    void SelectVar3();

    // Property setting methods
    void SetNumClusters(int numClusters_);
    void SetClusterMethod(clusterAlgorithmType clusterMethod_);
    void SetThreshold(double threshold_);
    void SetPercentile(double percentile_);
    void SetVar2(const std::string &var2_);
    void SetVar3(const std::string &var3_);

    // Property getting methods
    int               GetNumClusters() const;
    clusterAlgorithmType GetClusterMethod() const;
    double            GetThreshold() const;
    double            GetPercentile() const;
    const std::string &GetVar2() const;
          std::string &GetVar2();
    const std::string &GetVar3() const;
          std::string &GetVar3();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string clusterAlgorithmType_ToString(clusterAlgorithmType);
    static bool clusterAlgorithmType_FromString(const std::string &, clusterAlgorithmType &);
protected:
    static std::string clusterAlgorithmType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_numClusters = 0,
        ID_clusterMethod,
        ID_threshold,
        ID_percentile,
        ID_var2,
        ID_var3,
        ID__LAST
    };

private:
    int         numClusters;
    int         clusterMethod;
    double      threshold;
    double      percentile;
    std::string var2;
    std::string var3;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define MODELBASEDCLUSTERINGATTRIBUTES_TMFS "iiddss"

#endif
