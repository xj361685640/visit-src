package llnl.visit.plots;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;
import llnl.visit.ColorAttribute;

// ****************************************************************************
// Class: VectorAttributes
//
// Purpose:
//    Attributes for the vector plot
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Thu Aug 15 14:55:18 PST 2002
//
// Modifications:
//   
// ****************************************************************************

public class VectorAttributes extends AttributeSubject implements Plugin
{
    public VectorAttributes()
    {
        super(12);

        useStride = false;
        stride = 1;
        nVectors = 400;
        lineStyle = 0;
        lineWidth = 0;
        scale = 0.25;
        headSize = 0.25;
        headOn = true;
        colorByMag = true;
        useLegend = true;
        vectorColor = new ColorAttribute(0, 0, 0);
        colorTableName = new String("Default");
    }

    public VectorAttributes(VectorAttributes obj)
    {
        super(12);

        useStride = obj.useStride;
        stride = obj.stride;
        nVectors = obj.nVectors;
        lineStyle = obj.lineStyle;
        lineWidth = obj.lineWidth;
        scale = obj.scale;
        headSize = obj.headSize;
        headOn = obj.headOn;
        colorByMag = obj.colorByMag;
        useLegend = obj.useLegend;
        vectorColor = new ColorAttribute(obj.vectorColor);
        colorTableName = new String(obj.colorTableName);

        SelectAll();
    }

    public boolean equals(VectorAttributes obj)
    {
        // Create the return value
        return ((useStride == obj.useStride) &&
                (stride == obj.stride) &&
                (nVectors == obj.nVectors) &&
                (lineStyle == obj.lineStyle) &&
                (lineWidth == obj.lineWidth) &&
                (scale == obj.scale) &&
                (headSize == obj.headSize) &&
                (headOn == obj.headOn) &&
                (colorByMag == obj.colorByMag) &&
                (useLegend == obj.useLegend) &&
                (vectorColor == obj.vectorColor) &&
                (colorTableName == obj.colorTableName));
    }

    public String GetName() { return "Vector"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetUseStride(boolean useStride_)
    {
        useStride = useStride_;
        Select(0);
    }

    public void SetStride(int stride_)
    {
        stride = stride_;
        Select(1);
    }

    public void SetNVectors(int nVectors_)
    {
        nVectors = nVectors_;
        Select(2);
    }

    public void SetLineStyle(int lineStyle_)
    {
        lineStyle = lineStyle_;
        Select(3);
    }

    public void SetLineWidth(int lineWidth_)
    {
        lineWidth = lineWidth_;
        Select(4);
    }

    public void SetScale(double scale_)
    {
        scale = scale_;
        Select(5);
    }

    public void SetHeadSize(double headSize_)
    {
        headSize = headSize_;
        Select(6);
    }

    public void SetHeadOn(boolean headOn_)
    {
        headOn = headOn_;
        Select(7);
    }

    public void SetColorByMag(boolean colorByMag_)
    {
        colorByMag = colorByMag_;
        Select(8);
    }

    public void SetUseLegend(boolean useLegend_)
    {
        useLegend = useLegend_;
        Select(9);
    }

    public void SetVectorColor(ColorAttribute vectorColor_)
    {
        vectorColor = vectorColor_;
        Select(10);
    }

    public void SetColorTableName(String colorTableName_)
    {
        colorTableName = colorTableName_;
        Select(11);
    }

    // Property getting methods
    public boolean        GetUseStride() { return useStride; }
    public int            GetStride() { return stride; }
    public int            GetNVectors() { return nVectors; }
    public int            GetLineStyle() { return lineStyle; }
    public int            GetLineWidth() { return lineWidth; }
    public double         GetScale() { return scale; }
    public double         GetHeadSize() { return headSize; }
    public boolean        GetHeadOn() { return headOn; }
    public boolean        GetColorByMag() { return colorByMag; }
    public boolean        GetUseLegend() { return useLegend; }
    public ColorAttribute GetVectorColor() { return vectorColor; }
    public String         GetColorTableName() { return colorTableName; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(useStride);
        if(WriteSelect(1, buf))
            buf.WriteInt(stride);
        if(WriteSelect(2, buf))
            buf.WriteInt(nVectors);
        if(WriteSelect(3, buf))
            buf.WriteInt(lineStyle);
        if(WriteSelect(4, buf))
            buf.WriteInt(lineWidth);
        if(WriteSelect(5, buf))
            buf.WriteDouble(scale);
        if(WriteSelect(6, buf))
            buf.WriteDouble(headSize);
        if(WriteSelect(7, buf))
            buf.WriteBool(headOn);
        if(WriteSelect(8, buf))
            buf.WriteBool(colorByMag);
        if(WriteSelect(9, buf))
            buf.WriteBool(useLegend);
        if(WriteSelect(10, buf))
            vectorColor.Write(buf);
        if(WriteSelect(11, buf))
            buf.WriteString(colorTableName);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetUseStride(buf.ReadBool());
                break;
            case 1:
                SetStride(buf.ReadInt());
                break;
            case 2:
                SetNVectors(buf.ReadInt());
                break;
            case 3:
                SetLineStyle(buf.ReadInt());
                break;
            case 4:
                SetLineWidth(buf.ReadInt());
                break;
            case 5:
                SetScale(buf.ReadDouble());
                break;
            case 6:
                SetHeadSize(buf.ReadDouble());
                break;
            case 7:
                SetHeadOn(buf.ReadBool());
                break;
            case 8:
                SetColorByMag(buf.ReadBool());
                break;
            case 9:
                SetUseLegend(buf.ReadBool());
                break;
            case 10:
                vectorColor.Read(buf);
                Select(10);
                break;
            case 11:
                SetColorTableName(buf.ReadString());
                break;
            }
        }
    }


    // Attributes
    private boolean        useStride;
    private int            stride;
    private int            nVectors;
    private int            lineStyle;
    private int            lineWidth;
    private double         scale;
    private double         headSize;
    private boolean        headOn;
    private boolean        colorByMag;
    private boolean        useLegend;
    private ColorAttribute vectorColor;
    private String         colorTableName;
}

