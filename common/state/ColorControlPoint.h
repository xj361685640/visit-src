#ifndef COLORCONTROLPOINT_H
#define COLORCONTROLPOINT_H
#include <state_exports.h>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: ColorControlPoint
//
// Purpose:
//    This class contains an RGBA color with a position value.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue May 20 13:39:44 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API ColorControlPoint : public AttributeSubject
{
public:
    ColorControlPoint();
    ColorControlPoint(const ColorControlPoint &obj);
    virtual ~ColorControlPoint();

    virtual void operator = (const ColorControlPoint &obj);
    virtual bool operator == (const ColorControlPoint &obj) const;
    virtual bool operator != (const ColorControlPoint &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectColors();

    // Property setting methods
    void SetColors(const unsigned char *colors_);
    void SetPosition(float position_);

    // Property getting methods
    const unsigned char *GetColors() const;
          unsigned char *GetColors();
    float               GetPosition() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    ColorControlPoint(float pos, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
private:
    unsigned char colors[4];
    float         position;
};

#endif
