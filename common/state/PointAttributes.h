#ifndef POINTATTRIBUTES_H
#define POINTATTRIBUTES_H
#include <state_exports.h>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: PointAttributes
//
// Purpose:
//    Attributes for a point
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Mon Jun 9 09:54:24 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API PointAttributes : public AttributeSubject
{
public:
    PointAttributes();
    PointAttributes(const PointAttributes &obj);
    virtual ~PointAttributes();

    virtual void operator = (const PointAttributes &obj);
    virtual bool operator == (const PointAttributes &obj);
    virtual bool operator != (const PointAttributes &obj);

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectPoint();

    // Property setting methods
    void SetPoint(const double *point_);

    // Property getting methods
    const double *GetPoint() const;
          double *GetPoint();

    // Persistence methods
    virtual void CreateNode(DataNode *node);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, AttributeGroup *rhs);

private:
    double point[3];
};

#endif
