package llnl.visit;


// ****************************************************************************
// Class: SaveWindowAttributes
//
// Purpose:
//    This class contains the attributes used for saving windows.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Tue Oct 21 09:01:14 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

public class SaveWindowAttributes extends AttributeSubject
{
    // Constants
    public final static int FILEFORMAT_BMP = 0;
    public final static int FILEFORMAT_CURVE = 1;
    public final static int FILEFORMAT_JPEG = 2;
    public final static int FILEFORMAT_OBJ = 3;
    public final static int FILEFORMAT_PNG = 4;
    public final static int FILEFORMAT_POSTSCRIPT = 5;
    public final static int FILEFORMAT_PPM = 6;
    public final static int FILEFORMAT_RGB = 7;
    public final static int FILEFORMAT_STL = 8;
    public final static int FILEFORMAT_TIFF = 9;
    public final static int FILEFORMAT_ULTRA = 10;
    public final static int FILEFORMAT_VTK = 11;


    public SaveWindowAttributes()
    {
        super(14);

        hostName = new String("localhost");
        fileName = new String("visit");
        family = true;
        format = FILEFORMAT_TIFF;
        maintainAspect = true;
        width = 1024;
        height = 1024;
        screenCapture = true;
        saveTiled = false;
        quality = 80;
        progressive = false;
        binary = false;
        lastRealFilename = new String("(null)");
        stereo = false;
    }

    public SaveWindowAttributes(SaveWindowAttributes obj)
    {
        super(14);

        hostName = new String(obj.hostName);
        fileName = new String(obj.fileName);
        family = obj.family;
        format = obj.format;
        maintainAspect = obj.maintainAspect;
        width = obj.width;
        height = obj.height;
        screenCapture = obj.screenCapture;
        saveTiled = obj.saveTiled;
        quality = obj.quality;
        progressive = obj.progressive;
        binary = obj.binary;
        lastRealFilename = new String(obj.lastRealFilename);
        stereo = obj.stereo;

        SelectAll();
    }

    public boolean equals(SaveWindowAttributes obj)
    {
        // Create the return value
        return ((hostName == obj.hostName) &&
                (fileName == obj.fileName) &&
                (family == obj.family) &&
                (format == obj.format) &&
                (maintainAspect == obj.maintainAspect) &&
                (width == obj.width) &&
                (height == obj.height) &&
                (screenCapture == obj.screenCapture) &&
                (saveTiled == obj.saveTiled) &&
                (quality == obj.quality) &&
                (progressive == obj.progressive) &&
                (binary == obj.binary) &&
                (lastRealFilename == obj.lastRealFilename) &&
                (stereo == obj.stereo));
    }

    // Property setting methods
    public void SetHostName(String hostName_)
    {
        hostName = hostName_;
        Select(0);
    }

    public void SetFileName(String fileName_)
    {
        fileName = fileName_;
        Select(1);
    }

    public void SetFamily(boolean family_)
    {
        family = family_;
        Select(2);
    }

    public void SetFormat(int format_)
    {
        format = format_;
        Select(3);
    }

    public void SetMaintainAspect(boolean maintainAspect_)
    {
        maintainAspect = maintainAspect_;
        Select(4);
    }

    public void SetWidth(int width_)
    {
        width = width_;
        Select(5);
    }

    public void SetHeight(int height_)
    {
        height = height_;
        Select(6);
    }

    public void SetScreenCapture(boolean screenCapture_)
    {
        screenCapture = screenCapture_;
        Select(7);
    }

    public void SetSaveTiled(boolean saveTiled_)
    {
        saveTiled = saveTiled_;
        Select(8);
    }

    public void SetQuality(int quality_)
    {
        quality = quality_;
        Select(9);
    }

    public void SetProgressive(boolean progressive_)
    {
        progressive = progressive_;
        Select(10);
    }

    public void SetBinary(boolean binary_)
    {
        binary = binary_;
        Select(11);
    }

    public void SetLastRealFilename(String lastRealFilename_)
    {
        lastRealFilename = lastRealFilename_;
        Select(12);
    }

    public void SetStereo(boolean stereo_)
    {
        stereo = stereo_;
        Select(13);
    }

    // Property getting methods
    public String  GetHostName() { return hostName; }
    public String  GetFileName() { return fileName; }
    public boolean GetFamily() { return family; }
    public int     GetFormat() { return format; }
    public boolean GetMaintainAspect() { return maintainAspect; }
    public int     GetWidth() { return width; }
    public int     GetHeight() { return height; }
    public boolean GetScreenCapture() { return screenCapture; }
    public boolean GetSaveTiled() { return saveTiled; }
    public int     GetQuality() { return quality; }
    public boolean GetProgressive() { return progressive; }
    public boolean GetBinary() { return binary; }
    public String  GetLastRealFilename() { return lastRealFilename; }
    public boolean GetStereo() { return stereo; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteString(hostName);
        if(WriteSelect(1, buf))
            buf.WriteString(fileName);
        if(WriteSelect(2, buf))
            buf.WriteBool(family);
        if(WriteSelect(3, buf))
            buf.WriteInt(format);
        if(WriteSelect(4, buf))
            buf.WriteBool(maintainAspect);
        if(WriteSelect(5, buf))
            buf.WriteInt(width);
        if(WriteSelect(6, buf))
            buf.WriteInt(height);
        if(WriteSelect(7, buf))
            buf.WriteBool(screenCapture);
        if(WriteSelect(8, buf))
            buf.WriteBool(saveTiled);
        if(WriteSelect(9, buf))
            buf.WriteInt(quality);
        if(WriteSelect(10, buf))
            buf.WriteBool(progressive);
        if(WriteSelect(11, buf))
            buf.WriteBool(binary);
        if(WriteSelect(12, buf))
            buf.WriteString(lastRealFilename);
        if(WriteSelect(13, buf))
            buf.WriteBool(stereo);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetHostName(buf.ReadString());
                break;
            case 1:
                SetFileName(buf.ReadString());
                break;
            case 2:
                SetFamily(buf.ReadBool());
                break;
            case 3:
                SetFormat(buf.ReadInt());
                break;
            case 4:
                SetMaintainAspect(buf.ReadBool());
                break;
            case 5:
                SetWidth(buf.ReadInt());
                break;
            case 6:
                SetHeight(buf.ReadInt());
                break;
            case 7:
                SetScreenCapture(buf.ReadBool());
                break;
            case 8:
                SetSaveTiled(buf.ReadBool());
                break;
            case 9:
                SetQuality(buf.ReadInt());
                break;
            case 10:
                SetProgressive(buf.ReadBool());
                break;
            case 11:
                SetBinary(buf.ReadBool());
                break;
            case 12:
                SetLastRealFilename(buf.ReadString());
                break;
            case 13:
                SetStereo(buf.ReadBool());
                break;
            }
        }
    }


    // Attributes
    private String  hostName;
    private String  fileName;
    private boolean family;
    private int     format;
    private boolean maintainAspect;
    private int     width;
    private int     height;
    private boolean screenCapture;
    private boolean saveTiled;
    private int     quality;
    private boolean progressive;
    private boolean binary;
    private String  lastRealFilename;
    private boolean stereo;
}

