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

#ifndef SURFCOMPPREPATTRIBUTES_H
#define SURFCOMPPREPATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: SurfCompPrepAttributes
//
// Purpose:
//    Attributes for the SurfCompPrep operator.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class SurfCompPrepAttributes : public AttributeSubject
{
public:
    enum CoordinateSystem
    {
        Cartesian,
        Cylindrical,
        Spherical
    };
    enum SurfaceType
    {
        Closest,
        Farthest,
        Average
    };

    // These constructors are for objects of this class
    SurfCompPrepAttributes();
    SurfCompPrepAttributes(const SurfCompPrepAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    SurfCompPrepAttributes(private_tmfs_t tmfs);
    SurfCompPrepAttributes(const SurfCompPrepAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~SurfCompPrepAttributes();

    virtual SurfCompPrepAttributes& operator = (const SurfCompPrepAttributes &obj);
    virtual bool operator == (const SurfCompPrepAttributes &obj) const;
    virtual bool operator != (const SurfCompPrepAttributes &obj) const;
private:
    void Init();
    void Copy(const SurfCompPrepAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();

    // Property setting methods
    void SetSurfaceType(SurfaceType surfaceType_);
    void SetCoordSystem(CoordinateSystem coordSystem_);
    void SetThetaStart(double thetaStart_);
    void SetThetaStop(double thetaStop_);
    void SetThetaSteps(int thetaSteps_);
    void SetPhiStart(double phiStart_);
    void SetPhiStop(double phiStop_);
    void SetPhiSteps(int phiSteps_);
    void SetStartRadius(double startRadius_);
    void SetEndRadius(double endRadius_);
    void SetRadiusSteps(int radiusSteps_);
    void SetXStart(double xStart_);
    void SetXStop(double xStop_);
    void SetXSteps(int xSteps_);
    void SetYStart(double yStart_);
    void SetYStop(double yStop_);
    void SetYSteps(int ySteps_);
    void SetZStart(double zStart_);
    void SetZStop(double zStop_);
    void SetZSteps(int zSteps_);

    // Property getting methods
    SurfaceType GetSurfaceType() const;
    CoordinateSystem GetCoordSystem() const;
    double GetThetaStart() const;
    double GetThetaStop() const;
    int    GetThetaSteps() const;
    double GetPhiStart() const;
    double GetPhiStop() const;
    int    GetPhiSteps() const;
    double GetStartRadius() const;
    double GetEndRadius() const;
    int    GetRadiusSteps() const;
    double GetXStart() const;
    double GetXStop() const;
    int    GetXSteps() const;
    double GetYStart() const;
    double GetYStop() const;
    int    GetYSteps() const;
    double GetZStart() const;
    double GetZStop() const;
    int    GetZSteps() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string CoordinateSystem_ToString(CoordinateSystem);
    static bool CoordinateSystem_FromString(const std::string &, CoordinateSystem &);
protected:
    static std::string CoordinateSystem_ToString(int);
public:
    static std::string SurfaceType_ToString(SurfaceType);
    static bool SurfaceType_FromString(const std::string &, SurfaceType &);
protected:
    static std::string SurfaceType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_surfaceType = 0,
        ID_coordSystem,
        ID_thetaStart,
        ID_thetaStop,
        ID_thetaSteps,
        ID_phiStart,
        ID_phiStop,
        ID_phiSteps,
        ID_startRadius,
        ID_endRadius,
        ID_radiusSteps,
        ID_xStart,
        ID_xStop,
        ID_xSteps,
        ID_yStart,
        ID_yStop,
        ID_ySteps,
        ID_zStart,
        ID_zStop,
        ID_zSteps,
        ID__LAST
    };

private:
    int    surfaceType;
    int    coordSystem;
    double thetaStart;
    double thetaStop;
    int    thetaSteps;
    double phiStart;
    double phiStop;
    int    phiSteps;
    double startRadius;
    double endRadius;
    int    radiusSteps;
    double xStart;
    double xStop;
    int    xSteps;
    double yStart;
    double yStop;
    int    ySteps;
    double zStart;
    double zStop;
    int    zSteps;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define SURFCOMPPREPATTRIBUTES_TMFS "iiddiddiddiddiddiddi"

#endif
