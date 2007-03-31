#ifndef PICKATTRIBUTES_H
#define PICKATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>
class PickVarInfo;
#include <iostream.h>

// ****************************************************************************
// Class: PickAttributes
//
// Purpose:
//    This class contains attributes used for pick.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Sep 17 17:25:36 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API PickAttributes : public AttributeSubject
{
public:
    enum PickType
    {
        Zone,
        Node
    };

    PickAttributes();
    PickAttributes(const PickAttributes &obj);
    virtual ~PickAttributes();

    virtual void operator = (const PickAttributes &obj);
    virtual bool operator == (const PickAttributes &obj) const;
    virtual bool operator != (const PickAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectPickLetter();
    void SelectDatabaseName();
    void SelectActiveVariable();
    void SelectPickPoint();
    void SelectCellPoint();
    void SelectIncidentElements();
    void SelectVariables();
    void SelectVarInfo();
    void SelectNodeCoords();
    void SelectRayPoint1();
    void SelectRayPoint2();
    void SelectMeshInfo();
    void SelectRealIncidentElements();

    // Property setting methods
    void SetClearWindow(bool clearWindow_);
    void SetFulfilled(bool fulfilled_);
    void SetPickLetter(const std::string &pickLetter_);
    void SetElementNumber(int elementNumber_);
    void SetTimeStep(int timeStep_);
    void SetDomain(int domain_);
    void SetDimension(int dimension_);
    void SetDatabaseName(const std::string &databaseName_);
    void SetActiveVariable(const std::string &activeVariable_);
    void SetPickPoint(const float *pickPoint_);
    void SetCellPoint(const float *cellPoint_);
    void SetIncidentElements(const intVector &incidentElements_);
    void SetVariables(const stringVector &variables_);
    void SetVarInfo(const AttributeGroupVector &varInfo_);
    void SetUseNodeCoords(bool useNodeCoords_);
    void SetLogicalCoords(bool logicalCoords_);
    void SetNodeCoords(const stringVector &nodeCoords_);
    void SetRayPoint1(const float *rayPoint1_);
    void SetRayPoint2(const float *rayPoint2_);
    void SetNeedTransformMessage(bool needTransformMessage_);
    void SetPickType(PickType pickType_);
    void SetMeshInfo(const std::string &meshInfo_);
    void SetRealElementNumber(int realElementNumber_);
    void SetRealIncidentElements(const intVector &realIncidentElements_);

    // Property getting methods
    bool               GetClearWindow() const;
    bool               GetFulfilled() const;
    const std::string  &GetPickLetter() const;
          std::string  &GetPickLetter();
    int                GetElementNumber() const;
    int                GetTimeStep() const;
    int                GetDomain() const;
    int                GetDimension() const;
    const std::string  &GetDatabaseName() const;
          std::string  &GetDatabaseName();
    const std::string  &GetActiveVariable() const;
          std::string  &GetActiveVariable();
    const float        *GetPickPoint() const;
          float        *GetPickPoint();
    const float        *GetCellPoint() const;
          float        *GetCellPoint();
    const intVector    &GetIncidentElements() const;
          intVector    &GetIncidentElements();
    const stringVector &GetVariables() const;
          stringVector &GetVariables();
    const AttributeGroupVector &GetVarInfo() const;
          AttributeGroupVector &GetVarInfo();
    bool               GetUseNodeCoords() const;
    bool               GetLogicalCoords() const;
    const stringVector &GetNodeCoords() const;
          stringVector &GetNodeCoords();
    const float        *GetRayPoint1() const;
          float        *GetRayPoint1();
    const float        *GetRayPoint2() const;
          float        *GetRayPoint2();
    bool               GetNeedTransformMessage() const;
    PickType           GetPickType() const;
    const std::string  &GetMeshInfo() const;
          std::string  &GetMeshInfo();
    int                GetRealElementNumber() const;
    const intVector    &GetRealIncidentElements() const;
          intVector    &GetRealIncidentElements();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Attributegroup convenience methods
    void AddPickVarInfo(const PickVarInfo &);
    void ClearPickVarInfos();
    void RemovePickVarInfo(int i);
    int  GetNumPickVarInfos() const;
    PickVarInfo &GetPickVarInfo(int i);
    const PickVarInfo &GetPickVarInfo(int i) const;

    PickVarInfo &operator [] (int i);
    const PickVarInfo &operator [] (int i) const;

    // Enum conversion functions
    static std::string PickType_ToString(PickType);
    static bool PickType_FromString(const std::string &, PickType &);
protected:
    static std::string PickType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    void PrintSelf(ostream &os);
    void CreateOutputString(std::string &os, bool withLetter = true);
    void PrepareForNewPick();
protected:
    AttributeGroup *CreateSubAttributeGroup(int index);
private:
    bool                 clearWindow;
    bool                 fulfilled;
    std::string          pickLetter;
    int                  elementNumber;
    int                  timeStep;
    int                  domain;
    int                  dimension;
    std::string          databaseName;
    std::string          activeVariable;
    float                pickPoint[3];
    float                cellPoint[3];
    intVector            incidentElements;
    stringVector         variables;
    AttributeGroupVector varInfo;
    bool                 useNodeCoords;
    bool                 logicalCoords;
    stringVector         nodeCoords;
    float                rayPoint1[3];
    float                rayPoint2[3];
    bool                 needTransformMessage;
    int                  pickType;
    std::string          meshInfo;
    int                  realElementNumber;
    intVector            realIncidentElements;
};

#endif
