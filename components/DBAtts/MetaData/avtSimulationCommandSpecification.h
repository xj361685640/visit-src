#ifndef AVTSIMULATIONCOMMANDSPECIFICATION_H
#define AVTSIMULATIONCOMMANDSPECIFICATION_H
#include <dbatts_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: avtSimulationCommandSpecification
//
// Purpose:
//    Contains the specification for one command
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Fri Mar 18 16:21:33 PST 2005
//
// Modifications:
//   
// ****************************************************************************

class DBATTS_API avtSimulationCommandSpecification : public AttributeSubject
{
public:
    enum CommandArgumentType
    {
        CmdArgNone,
        CmdArgInt,
        CmdArgFloat,
        CmdArgString
    };

    avtSimulationCommandSpecification();
    avtSimulationCommandSpecification(const avtSimulationCommandSpecification &obj);
    virtual ~avtSimulationCommandSpecification();

    virtual avtSimulationCommandSpecification& operator = (const avtSimulationCommandSpecification &obj);
    virtual bool operator == (const avtSimulationCommandSpecification &obj) const;
    virtual bool operator != (const avtSimulationCommandSpecification &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectName();

    // Property setting methods
    void SetName(const std::string &name_);
    void SetArgumentType(CommandArgumentType argumentType_);

    // Property getting methods
    const std::string &GetName() const;
          std::string &GetName();
    CommandArgumentType GetArgumentType() const;

    // Enum conversion functions
    static std::string CommandArgumentType_ToString(CommandArgumentType);
    static bool CommandArgumentType_FromString(const std::string &, CommandArgumentType &);
protected:
    static std::string CommandArgumentType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    std::string name;
    int         argumentType;
};

#endif
