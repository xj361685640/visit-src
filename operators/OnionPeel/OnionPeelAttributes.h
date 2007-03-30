#ifndef ONIONPEELATTRIBUTES_H
#define ONIONPEELATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: OnionPeelAttributes
//
// Purpose:
//    Attributes for the onion peel operator
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue May 20 14:50:18 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class OnionPeelAttributes : public AttributeSubject
{
public:
    enum NodeFace
    {
        Node,
        Face
    };

    OnionPeelAttributes();
    OnionPeelAttributes(const OnionPeelAttributes &obj);
    virtual ~OnionPeelAttributes();

    virtual void operator = (const OnionPeelAttributes &obj);
    virtual bool operator == (const OnionPeelAttributes &obj) const;
    virtual bool operator != (const OnionPeelAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectCategoryName();
    void SelectSubsetName();
    void SelectIndex();

    // Property setting methods
    void SetAdjacencyType(NodeFace adjacencyType_);
    void SetCategoryName(const std::string &categoryName_);
    void SetSubsetName(const std::string &subsetName_);
    void SetIndex(const intVector &index_);
    void SetLogical(bool logical_);
    void SetRequestedLayer(int requestedLayer_);

    // Property getting methods
    NodeFace          GetAdjacencyType() const;
    const std::string &GetCategoryName() const;
          std::string &GetCategoryName();
    const std::string &GetSubsetName() const;
          std::string &GetSubsetName();
    const intVector   &GetIndex() const;
          intVector   &GetIndex();
    bool              GetLogical() const;
    int               GetRequestedLayer() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string NodeFace_ToString(NodeFace);
    static bool NodeFace_FromString(const std::string &, NodeFace &);
protected:
    static std::string NodeFace_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    int         adjacencyType;
    std::string categoryName;
    std::string subsetName;
    intVector   index;
    bool        logical;
    int         requestedLayer;
};

#endif
