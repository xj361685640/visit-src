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
// Creation:   Mon Jan 23 16:16:29 PST 2006
//
// Modifications:
//   
// ****************************************************************************

class DBATTS_API avtSimulationCommandSpecification : public AttributeSubject
{
public:
    enum RunMode
    {
        Unknown,
        Running,
        Stopped
    };
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
    void SelectClassName();
    void SelectParent();
    void SelectSignal();
    void SelectText();
    void SelectUiType();
    void SelectValue();

    // Property setting methods
    void SetName(const std::string &name_);
    void SetArgumentType(CommandArgumentType argumentType_);
    void SetClassName(const std::string &className_);
    void SetEnabled(bool enabled_);
    void SetParent(const std::string &parent_);
    void SetIsOn(bool isOn_);
    void SetSignal(const std::string &signal_);
    void SetText(const std::string &text_);
    void SetUiType(const std::string &uiType_);
    void SetValue(const std::string &value_);

    // Property getting methods
    const std::string &GetName() const;
          std::string &GetName();
    CommandArgumentType GetArgumentType() const;
    const std::string &GetClassName() const;
          std::string &GetClassName();
    bool              GetEnabled() const;
    const std::string &GetParent() const;
          std::string &GetParent();
    bool              GetIsOn() const;
    const std::string &GetSignal() const;
          std::string &GetSignal();
    const std::string &GetText() const;
          std::string &GetText();
    const std::string &GetUiType() const;
          std::string &GetUiType();
    const std::string &GetValue() const;
          std::string &GetValue();

    // Enum conversion functions
    static std::string RunMode_ToString(RunMode);
    static bool RunMode_FromString(const std::string &, RunMode &);
protected:
    static std::string RunMode_ToString(int);
public:
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
    std::string className;
    bool        enabled;
    std::string parent;
    bool        isOn;
    std::string signal;
    std::string text;
    std::string uiType;
    std::string value;
};

#endif
