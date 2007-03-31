package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: SurfCompPrepAttributes
//
// Purpose:
//    Attributes for the SurfCompPrep operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Tue Jul 1 11:03:05 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

public class SurfCompPrepAttributes extends AttributeSubject implements Plugin
{
    // Constants
    public final static int COORDINATESYSTEM_CARTESIAN = 0;
    public final static int COORDINATESYSTEM_CYLINDRICAL = 1;
    public final static int COORDINATESYSTEM_SPHERICAL = 2;

    public final static int SURFACETYPE_CLOSEST = 0;
    public final static int SURFACETYPE_FARTHEST = 1;
    public final static int SURFACETYPE_AVERAGE = 2;


    public SurfCompPrepAttributes()
    {
        super(20);

        surfaceType = SURFACETYPE_AVERAGE;
        coordSystem = COORDINATESYSTEM_CARTESIAN;
        thetaStart = 0;
        thetaStop = 360;
        thetaSteps = 90;
        phiStart = 0;
        phiStop = 180;
        phiSteps = 45;
        startRadius = 0;
        endRadius = 1;
        radiusSteps = 100;
        xStart = 0;
        xStop = 1;
        xSteps = 100;
        yStart = 0;
        yStop = 1;
        ySteps = 100;
        zStart = 0;
        zStop = 1;
        zSteps = 100;
    }

    public SurfCompPrepAttributes(SurfCompPrepAttributes obj)
    {
        super(20);

        surfaceType = obj.surfaceType;
        coordSystem = obj.coordSystem;
        thetaStart = obj.thetaStart;
        thetaStop = obj.thetaStop;
        thetaSteps = obj.thetaSteps;
        phiStart = obj.phiStart;
        phiStop = obj.phiStop;
        phiSteps = obj.phiSteps;
        startRadius = obj.startRadius;
        endRadius = obj.endRadius;
        radiusSteps = obj.radiusSteps;
        xStart = obj.xStart;
        xStop = obj.xStop;
        xSteps = obj.xSteps;
        yStart = obj.yStart;
        yStop = obj.yStop;
        ySteps = obj.ySteps;
        zStart = obj.zStart;
        zStop = obj.zStop;
        zSteps = obj.zSteps;

        SelectAll();
    }

    public boolean equals(SurfCompPrepAttributes obj)
    {
        // Create the return value
        return ((surfaceType == obj.surfaceType) &&
                (coordSystem == obj.coordSystem) &&
                (thetaStart == obj.thetaStart) &&
                (thetaStop == obj.thetaStop) &&
                (thetaSteps == obj.thetaSteps) &&
                (phiStart == obj.phiStart) &&
                (phiStop == obj.phiStop) &&
                (phiSteps == obj.phiSteps) &&
                (startRadius == obj.startRadius) &&
                (endRadius == obj.endRadius) &&
                (radiusSteps == obj.radiusSteps) &&
                (xStart == obj.xStart) &&
                (xStop == obj.xStop) &&
                (xSteps == obj.xSteps) &&
                (yStart == obj.yStart) &&
                (yStop == obj.yStop) &&
                (ySteps == obj.ySteps) &&
                (zStart == obj.zStart) &&
                (zStop == obj.zStop) &&
                (zSteps == obj.zSteps));
    }

    public String GetName() { return "SurfCompPrep"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetSurfaceType(int surfaceType_)
    {
        surfaceType = surfaceType_;
        Select(0);
    }

    public void SetCoordSystem(int coordSystem_)
    {
        coordSystem = coordSystem_;
        Select(1);
    }

    public void SetThetaStart(double thetaStart_)
    {
        thetaStart = thetaStart_;
        Select(2);
    }

    public void SetThetaStop(double thetaStop_)
    {
        thetaStop = thetaStop_;
        Select(3);
    }

    public void SetThetaSteps(int thetaSteps_)
    {
        thetaSteps = thetaSteps_;
        Select(4);
    }

    public void SetPhiStart(double phiStart_)
    {
        phiStart = phiStart_;
        Select(5);
    }

    public void SetPhiStop(double phiStop_)
    {
        phiStop = phiStop_;
        Select(6);
    }

    public void SetPhiSteps(int phiSteps_)
    {
        phiSteps = phiSteps_;
        Select(7);
    }

    public void SetStartRadius(double startRadius_)
    {
        startRadius = startRadius_;
        Select(8);
    }

    public void SetEndRadius(double endRadius_)
    {
        endRadius = endRadius_;
        Select(9);
    }

    public void SetRadiusSteps(int radiusSteps_)
    {
        radiusSteps = radiusSteps_;
        Select(10);
    }

    public void SetXStart(double xStart_)
    {
        xStart = xStart_;
        Select(11);
    }

    public void SetXStop(double xStop_)
    {
        xStop = xStop_;
        Select(12);
    }

    public void SetXSteps(int xSteps_)
    {
        xSteps = xSteps_;
        Select(13);
    }

    public void SetYStart(double yStart_)
    {
        yStart = yStart_;
        Select(14);
    }

    public void SetYStop(double yStop_)
    {
        yStop = yStop_;
        Select(15);
    }

    public void SetYSteps(int ySteps_)
    {
        ySteps = ySteps_;
        Select(16);
    }

    public void SetZStart(double zStart_)
    {
        zStart = zStart_;
        Select(17);
    }

    public void SetZStop(double zStop_)
    {
        zStop = zStop_;
        Select(18);
    }

    public void SetZSteps(int zSteps_)
    {
        zSteps = zSteps_;
        Select(19);
    }

    // Property getting methods
    public int    GetSurfaceType() { return surfaceType; }
    public int    GetCoordSystem() { return coordSystem; }
    public double GetThetaStart() { return thetaStart; }
    public double GetThetaStop() { return thetaStop; }
    public int    GetThetaSteps() { return thetaSteps; }
    public double GetPhiStart() { return phiStart; }
    public double GetPhiStop() { return phiStop; }
    public int    GetPhiSteps() { return phiSteps; }
    public double GetStartRadius() { return startRadius; }
    public double GetEndRadius() { return endRadius; }
    public int    GetRadiusSteps() { return radiusSteps; }
    public double GetXStart() { return xStart; }
    public double GetXStop() { return xStop; }
    public int    GetXSteps() { return xSteps; }
    public double GetYStart() { return yStart; }
    public double GetYStop() { return yStop; }
    public int    GetYSteps() { return ySteps; }
    public double GetZStart() { return zStart; }
    public double GetZStop() { return zStop; }
    public int    GetZSteps() { return zSteps; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(surfaceType);
        if(WriteSelect(1, buf))
            buf.WriteInt(coordSystem);
        if(WriteSelect(2, buf))
            buf.WriteDouble(thetaStart);
        if(WriteSelect(3, buf))
            buf.WriteDouble(thetaStop);
        if(WriteSelect(4, buf))
            buf.WriteInt(thetaSteps);
        if(WriteSelect(5, buf))
            buf.WriteDouble(phiStart);
        if(WriteSelect(6, buf))
            buf.WriteDouble(phiStop);
        if(WriteSelect(7, buf))
            buf.WriteInt(phiSteps);
        if(WriteSelect(8, buf))
            buf.WriteDouble(startRadius);
        if(WriteSelect(9, buf))
            buf.WriteDouble(endRadius);
        if(WriteSelect(10, buf))
            buf.WriteInt(radiusSteps);
        if(WriteSelect(11, buf))
            buf.WriteDouble(xStart);
        if(WriteSelect(12, buf))
            buf.WriteDouble(xStop);
        if(WriteSelect(13, buf))
            buf.WriteInt(xSteps);
        if(WriteSelect(14, buf))
            buf.WriteDouble(yStart);
        if(WriteSelect(15, buf))
            buf.WriteDouble(yStop);
        if(WriteSelect(16, buf))
            buf.WriteInt(ySteps);
        if(WriteSelect(17, buf))
            buf.WriteDouble(zStart);
        if(WriteSelect(18, buf))
            buf.WriteDouble(zStop);
        if(WriteSelect(19, buf))
            buf.WriteInt(zSteps);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetSurfaceType(buf.ReadInt());
                break;
            case 1:
                SetCoordSystem(buf.ReadInt());
                break;
            case 2:
                SetThetaStart(buf.ReadDouble());
                break;
            case 3:
                SetThetaStop(buf.ReadDouble());
                break;
            case 4:
                SetThetaSteps(buf.ReadInt());
                break;
            case 5:
                SetPhiStart(buf.ReadDouble());
                break;
            case 6:
                SetPhiStop(buf.ReadDouble());
                break;
            case 7:
                SetPhiSteps(buf.ReadInt());
                break;
            case 8:
                SetStartRadius(buf.ReadDouble());
                break;
            case 9:
                SetEndRadius(buf.ReadDouble());
                break;
            case 10:
                SetRadiusSteps(buf.ReadInt());
                break;
            case 11:
                SetXStart(buf.ReadDouble());
                break;
            case 12:
                SetXStop(buf.ReadDouble());
                break;
            case 13:
                SetXSteps(buf.ReadInt());
                break;
            case 14:
                SetYStart(buf.ReadDouble());
                break;
            case 15:
                SetYStop(buf.ReadDouble());
                break;
            case 16:
                SetYSteps(buf.ReadInt());
                break;
            case 17:
                SetZStart(buf.ReadDouble());
                break;
            case 18:
                SetZStop(buf.ReadDouble());
                break;
            case 19:
                SetZSteps(buf.ReadInt());
                break;
            }
        }
    }


    // Attributes
    private int    surfaceType;
    private int    coordSystem;
    private double thetaStart;
    private double thetaStop;
    private int    thetaSteps;
    private double phiStart;
    private double phiStop;
    private int    phiSteps;
    private double startRadius;
    private double endRadius;
    private int    radiusSteps;
    private double xStart;
    private double xStop;
    private int    xSteps;
    private double yStart;
    private double yStop;
    private int    ySteps;
    private double zStart;
    private double zStop;
    private int    zSteps;
}

