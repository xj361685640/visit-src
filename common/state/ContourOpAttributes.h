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

#ifndef CONTOUROPATTRIBUTES_H
#define CONTOUROPATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: ContourOpAttributes
//
// Purpose:
//    This class contains the operator attributes for the contour operator.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class STATE_API ContourOpAttributes : public AttributeSubject
{
public:
    enum ContourMethod
    {
        Level,
        Value,
        Percent
    };
    enum ContourScaling
    {
        Linear,
        Log
    };

    // These constructors are for objects of this class
    ContourOpAttributes();
    ContourOpAttributes(const ContourOpAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    ContourOpAttributes(private_tmfs_t tmfs);
    ContourOpAttributes(const ContourOpAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~ContourOpAttributes();

    virtual ContourOpAttributes& operator = (const ContourOpAttributes &obj);
    virtual bool operator == (const ContourOpAttributes &obj) const;
    virtual bool operator != (const ContourOpAttributes &obj) const;
private:
    void Init();
    void Copy(const ContourOpAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectContourValue();
    void SelectContourPercent();
    void SelectVariable();

    // Property setting methods
    void SetContourNLevels(int contourNLevels_);
    void SetContourValue(const doubleVector &contourValue_);
    void SetContourPercent(const doubleVector &contourPercent_);
    void SetContourMethod(ContourMethod contourMethod_);
    void SetMinFlag(bool minFlag_);
    void SetMaxFlag(bool maxFlag_);
    void SetMin(double min_);
    void SetMax(double max_);
    void SetScaling(ContourScaling scaling_);
    void SetVariable(const std::string &variable_);

    // Property getting methods
    int                GetContourNLevels() const;
    const doubleVector &GetContourValue() const;
          doubleVector &GetContourValue();
    const doubleVector &GetContourPercent() const;
          doubleVector &GetContourPercent();
    ContourMethod      GetContourMethod() const;
    bool               GetMinFlag() const;
    bool               GetMaxFlag() const;
    double             GetMin() const;
    double             GetMax() const;
    ContourScaling     GetScaling() const;
    const std::string  &GetVariable() const;
          std::string  &GetVariable();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string ContourMethod_ToString(ContourMethod);
    static bool ContourMethod_FromString(const std::string &, ContourMethod &);
protected:
    static std::string ContourMethod_ToString(int);
public:
    static std::string ContourScaling_ToString(ContourScaling);
    static bool ContourScaling_FromString(const std::string &, ContourScaling &);
protected:
    static std::string ContourScaling_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_contourNLevels = 0,
        ID_contourValue,
        ID_contourPercent,
        ID_contourMethod,
        ID_minFlag,
        ID_maxFlag,
        ID_min,
        ID_max,
        ID_scaling,
        ID_variable,
        ID__LAST
    };

private:
    int          contourNLevels;
    doubleVector contourValue;
    doubleVector contourPercent;
    int          contourMethod;
    bool         minFlag;
    bool         maxFlag;
    double       min;
    double       max;
    int          scaling;
    std::string  variable;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define CONTOUROPATTRIBUTES_TMFS "id*d*ibbddis"

#endif
