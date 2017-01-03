/*****************************************************************************
*
* Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC
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

#ifndef MODELFITATTS_H
#define MODELFITATTS_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: ModelFitAtts
//
// Purpose:
//    This file contains attributes for the ModelFit operator.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class ModelFitAtts : public AttributeSubject
{
public:
    enum Spaces
    {
        VARIABLE,
        NORMAL,
        LOG,
        PROBABILITY
    };
    enum Stats
    {
        AVERAGE,
        MIN,
        MAX,
        NONE
    };
    enum Distances
    {
        EUCLIDEAN,
        MANHATTAN,
        MAXIMUM
    };

    // These constructors are for objects of this class
    ModelFitAtts();
    ModelFitAtts(const ModelFitAtts &obj);
protected:
    // These constructors are for objects derived from this class
    ModelFitAtts(private_tmfs_t tmfs);
    ModelFitAtts(const ModelFitAtts &obj, private_tmfs_t tmfs);
public:
    virtual ~ModelFitAtts();

    virtual ModelFitAtts& operator = (const ModelFitAtts &obj);
    virtual bool operator == (const ModelFitAtts &obj) const;
    virtual bool operator != (const ModelFitAtts &obj) const;
private:
    void Init();
    void Copy(const ModelFitAtts &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectVars();
    void SelectNumVars();
    void SelectTuples();
    void SelectStatTuples();
    void SelectNumTups();
    void SelectThold();
    void SelectSelectionType();
    void SelectDistanceType();
    void SelectInputSpace();
    void SelectModelNames();
    void SelectModelNums();

    // Property setting methods
    void SetVars(const stringVector &Vars_);
    void SetNumVars(const intVector &numVars_);
    void SetTuples(const doubleVector &Tuples_);
    void SetStatTuples(const unsignedCharVector &StatTuples_);
    void SetNumTups(const intVector &numTups_);
    void SetThold(const doubleVector &thold_);
    void SetSelectionType(const intVector &selectionType_);
    void SetDistanceType(const intVector &distanceType_);
    void SetInputSpace(const intVector &inputSpace_);
    void SetModelNames(const stringVector &modelNames_);
    void SetModelNums(const intVector &modelNums_);

    // Property getting methods
    const stringVector       &GetVars() const;
          stringVector       &GetVars();
    const intVector          &GetNumVars() const;
          intVector          &GetNumVars();
    const doubleVector       &GetTuples() const;
          doubleVector       &GetTuples();
    const unsignedCharVector &GetStatTuples() const;
          unsignedCharVector &GetStatTuples();
    const intVector          &GetNumTups() const;
          intVector          &GetNumTups();
    const doubleVector       &GetThold() const;
          doubleVector       &GetThold();
    const intVector          &GetSelectionType() const;
          intVector          &GetSelectionType();
    const intVector          &GetDistanceType() const;
          intVector          &GetDistanceType();
    const intVector          &GetInputSpace() const;
          intVector          &GetInputSpace();
    const stringVector       &GetModelNames() const;
          stringVector       &GetModelNames();
    const intVector          &GetModelNums() const;
          intVector          &GetModelNums();

    // Enum conversion functions
    static std::string Spaces_ToString(Spaces);
    static bool Spaces_FromString(const std::string &, Spaces &);
protected:
    static std::string Spaces_ToString(int);
public:
    static std::string Stats_ToString(Stats);
    static bool Stats_FromString(const std::string &, Stats &);
protected:
    static std::string Stats_ToString(int);
public:
    static std::string Distances_ToString(Distances);
    static bool Distances_FromString(const std::string &, Distances &);
protected:
    static std::string Distances_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_Vars = 0,
        ID_numVars,
        ID_Tuples,
        ID_StatTuples,
        ID_numTups,
        ID_thold,
        ID_selectionType,
        ID_distanceType,
        ID_inputSpace,
        ID_modelNames,
        ID_modelNums,
        ID__LAST
    };

private:
    stringVector       Vars;
    intVector          numVars;
    doubleVector       Tuples;
    unsignedCharVector StatTuples;
    intVector          numTups;
    doubleVector       thold;
    intVector          selectionType;
    intVector          distanceType;
    intVector          inputSpace;
    stringVector       modelNames;
    intVector          modelNums;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define MODELFITATTS_TMFS "s*i*d*u*i*d*i*i*i*s*i*"

#endif
