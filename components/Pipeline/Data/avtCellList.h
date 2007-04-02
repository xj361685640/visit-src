// ************************************************************************* //
//                                avtCellList.h                              //
// ************************************************************************* //

#ifndef AVT_CELL_LIST_H
#define AVT_CELL_LIST_H

#include <pipeline_exports.h>

#include <avtCellTypes.h>

class     avtHexahedronExtractor;
class     avtImagePartition;
class     avtPointExtractor;
class     avtPyramidExtractor;
class     avtTetrahedronExtractor;
class     avtWedgeExtractor;
class     avtVolume;


typedef struct
{
    int   minx;
    int   maxx;
    int   miny;
    int   maxy;
    int   size;
    char *cell;
} avtSerializedCell;



// ****************************************************************************
//  Class: avtCellList
//
//  Purpose:
//      Stores cells so that sample points don't always have to be immediately
//      extracted from them.  This is really only used when operating in
//      parallel.
//
//  Programmer: Hank Childs
//  Creation:   January 27, 2001
//
//  Modifications:
//
//    Hank Childs, Wed Nov 14 15:14:50 PST 2001
//    Add support for multiple variables.
//
//    Hank Childs, Tue Jan  1 13:15:09 PST 2002
//    Add estimates of number of samples per scanline to help the image
//    partition to create non-uniform partitions with approximately equal
//    sized partitions with respect to number of samples.
//
//    Hank Childs, Tue Jan 24 16:50:30 PST 2006
//    Add support for points.
//
//    Hank Childs, Fri Jan 27 14:50:38 PST 2006
//    Added method "Restrict".
//
// ****************************************************************************

class PIPELINE_API avtCellList
{
  public:
                             avtCellList(int);
    virtual                 ~avtCellList();

    void                     Store(const avtHexahedron &, int, int, int, int);
    void                     Store(const avtPoint &, int, int, int, int);
    void                     Store(const avtPyramid &, int, int, int, int);
    void                     Store(const avtTetrahedron &, int, int, int, int);
    void                     Store(const avtWedge &, int, int, int, int);

    void                     ExtractCells(const char * const *, const int *,
                                          int, avtVolume *);
    char                    *ConstructMessages(avtImagePartition *, char **,
                                               int *);
    void                     EstimateNumberOfSamplesPerScanline(int *);
    int                      GetNumberOfCells(void) const { return celllistI; };

    void                     Restrict(int, int, int, int);

  protected:
    avtSerializedCell      **celllist;
    int                      celllistI;
    int                      celllistN;
    int                      nVars;

    bool                     useRestriction;
    int                      minWidth, maxWidth;
    int                      minHeight, maxHeight;

    char                    *Serialize(const float (*)[3], 
                                       const float (*)[AVT_VARIABLE_LIMIT],int);
    char                    *SerializePoint(const float *, const float *);
    void                     Store(char *, int, int, int, int, int);
    void                     Unserialize(float (*)[3],
                                         float (*)[AVT_VARIABLE_LIMIT], int, 
                                         const char *&);
    void                     UnserializePoint(float *, float *, const char *&);
};


#endif


