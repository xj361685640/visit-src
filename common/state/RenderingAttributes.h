#ifndef RENDERINGATTRIBUTES_H
#define RENDERINGATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>
#include <ColorAttribute.h>
#include <float.h>

// ****************************************************************************
// Class: RenderingAttributes
//
// Purpose:
//    This class contains special rendering attributes like antialiasing and stero settings.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed May 12 07:29:22 PDT 2004
//
// Modifications:
//   
// ****************************************************************************

class STATE_API RenderingAttributes : public AttributeSubject
{
public:
    enum GeometryRepresentation
    {
        Surfaces,
        Wireframe,
        Points
    };
    enum StereoTypes
    {
        RedBlue,
        Interlaced,
        CrystalEyes
    };
    enum TriStateMode
    {
        Never,
        Always,
        Auto
    };
    static const int DEFAULT_SCALABLE_AUTO_THRESHOLD;
    static const int DEFAULT_SCALABLE_ACTIVATION_MODE;

    RenderingAttributes();
    RenderingAttributes(const RenderingAttributes &obj);
    virtual ~RenderingAttributes();

    virtual void operator = (const RenderingAttributes &obj);
    virtual bool operator == (const RenderingAttributes &obj) const;
    virtual bool operator != (const RenderingAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectSpecularColor();

    // Property setting methods
    void SetAntialiasing(bool antialiasing_);
    void SetGeometryRepresentation(GeometryRepresentation geometryRepresentation_);
    void SetDisplayListMode(TriStateMode displayListMode_);
    void SetStereoRendering(bool stereoRendering_);
    void SetStereoType(StereoTypes stereoType_);
    void SetNotifyForEachRender(bool notifyForEachRender_);
    void SetScalableActivationMode(TriStateMode scalableActivationMode_);
    void SetScalableAutoThreshold(int scalableAutoThreshold_);
    void SetSpecularFlag(bool specularFlag_);
    void SetSpecularCoeff(float specularCoeff_);
    void SetSpecularPower(float specularPower_);
    void SetSpecularColor(const ColorAttribute &specularColor_);

    // Property getting methods
    bool                 GetAntialiasing() const;
    GeometryRepresentation GetGeometryRepresentation() const;
    TriStateMode         GetDisplayListMode() const;
    bool                 GetStereoRendering() const;
    StereoTypes          GetStereoType() const;
    bool                 GetNotifyForEachRender() const;
    TriStateMode         GetScalableActivationMode() const;
    int                  GetScalableAutoThreshold() const;
    bool                 GetSpecularFlag() const;
    float                GetSpecularCoeff() const;
    float                GetSpecularPower() const;
    const ColorAttribute &GetSpecularColor() const;
          ColorAttribute &GetSpecularColor();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string GeometryRepresentation_ToString(GeometryRepresentation);
    static bool GeometryRepresentation_FromString(const std::string &, GeometryRepresentation &);
protected:
    static std::string GeometryRepresentation_ToString(int);
public:
    static std::string StereoTypes_ToString(StereoTypes);
    static bool StereoTypes_FromString(const std::string &, StereoTypes &);
protected:
    static std::string StereoTypes_ToString(int);
public:
    static std::string TriStateMode_ToString(TriStateMode);
    static bool TriStateMode_FromString(const std::string &, TriStateMode &);
protected:
    static std::string TriStateMode_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    static int GetEffectiveScalableThreshold(TriStateMode mode, int autoThreshold);
private:
    bool           antialiasing;
    int            geometryRepresentation;
    int            displayListMode;
    bool           stereoRendering;
    int            stereoType;
    bool           notifyForEachRender;
    int            scalableActivationMode;
    int            scalableAutoThreshold;
    bool           specularFlag;
    float          specularCoeff;
    float          specularPower;
    ColorAttribute specularColor;
};

#endif
