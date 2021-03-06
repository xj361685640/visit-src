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

// ************************************************************************* //
//                               avtOpacityMap.C                             //
// ************************************************************************* //

#include <avtOpacityMap.h>

// For NULL
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <DebugStream.h>
#include <ImproperUseException.h>


// ****************************************************************************
//  Method: avtOpacityMap constructor
//
//  Arguments:
//      te      The desired number of table entries.
//
//  Programmer: Hank Childs
//  Creation:   November 29, 2000
//
//  Modifications:
//
//    Hank Childs, Sat Feb  3 12:00:51 PST 2001
//    Modified to make map table-based.
//
//    Hank Childs, Wed Jan  4 11:26:15 PST 2006
//    Call memset to make sure that all entries of RGBA struct are initialized.
//    This cannot be done without a memset because of padding issues.  We
//    want to make sure the inaccessible byte is initialized to avoid purify
//    warnings.
//
// ****************************************************************************

avtOpacityMap::avtOpacityMap(int te)
{
    tableEntries = te;
    table = new RGBA[tableEntries];
  
    transferFn1D = new _RGBA[tableEntries]();
    // RGBA contains a padded byte after the B and before the A.  Use a memset
    // to make sure this inaccessible byte is initialized.  This will allow
    // us to avoid purify issues.
    memset(table, 0, sizeof(RGBA)*tableEntries);
/*
    for (int i = 0 ; i < tableEntries ; i++)
    {
        table[i].R = 0;
        table[i].G = 0;
        table[i].B = 0;
        table[i].A = 0.;
    }
*/
    min = 0.;
    max = 1.;
    minVisibleScalarIndex = maxVisibleScalarIndex = 0;
    minVisibleScalar = maxVisibleScalar = 0.;
    SetIntermediateVars();
}

avtOpacityMap::avtOpacityMap(const avtOpacityMap &obj)
{
    tableEntries = obj.tableEntries;
    table = new RGBA[tableEntries];
    memcpy(table, obj.table, tableEntries * sizeof(RGBA));
    transferFn1D = new _RGBA[tableEntries];
    memcpy(transferFn1D, obj.transferFn1D, tableEntries * sizeof(_RGBA));
    min = obj.min;
    max = obj.max;
    range = obj.range;
    inverseRange = obj.range;
    multiplier = obj.multiplier;
    minVisibleScalarIndex = obj.minVisibleScalarIndex;
    maxVisibleScalarIndex = obj.maxVisibleScalarIndex;
    minVisibleScalar = obj.minVisibleScalar;
    maxVisibleScalar = obj.maxVisibleScalar;
}

void avtOpacityMap::operator = (const avtOpacityMap &obj)
{
    tableEntries = obj.tableEntries;
    table = new RGBA[tableEntries];
    memcpy(table, obj.table, tableEntries * sizeof(RGBA));
    transferFn1D = new _RGBA[tableEntries];
    memcpy(transferFn1D, obj.transferFn1D, tableEntries * sizeof(_RGBA));
    min = obj.min;
    max = obj.max;
    range = obj.range;
    inverseRange = obj.range;
    multiplier = obj.multiplier;
    minVisibleScalarIndex = obj.minVisibleScalarIndex;
    maxVisibleScalarIndex = obj.maxVisibleScalarIndex;
    minVisibleScalar = obj.minVisibleScalar;
    maxVisibleScalar = obj.maxVisibleScalar;
}

// ****************************************************************************
//  Method: avtOpacityMap destructor
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
// ****************************************************************************

avtOpacityMap::~avtOpacityMap()
{
    if (table != NULL)
    {
        delete [] table;
    }

    if (transferFn1D != NULL){
        delete []transferFn1D;
        transferFn1D = NULL;
    }
}


// ****************************************************************************
//  Method: avtOpacityMap::SetMin
//
//  Purpose:
//      Sets the minimum for the opacity map.  Used for quantizing.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
// ****************************************************************************

void
avtOpacityMap::SetMin(double m)
{
    min = m;
    SetIntermediateVars();
}


// ****************************************************************************
//  Method: avtOpacityMap::SetMax
//
//  Purpose:
//      Sets the maximum for the opacity map.  Used for quantizing.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
// ****************************************************************************

void
avtOpacityMap::SetMax(double m)
{
    max = m;
    SetIntermediateVars();
}


// ****************************************************************************
//  Method: avtOpacityMap::SetIntermediateVars
//
//  Purpose:
//      Sets up some variables used when quantizing a value.  This is strictly
//      to prevent unnecessary calculation.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
//  Modifications:
//
//    Hank Childs, Mon Feb 12 17:25:14 PST 2001
//    Multiplier was being set incorrectly.
//
// ****************************************************************************

void
avtOpacityMap::SetIntermediateVars(void)
{
    if (min != max)
    {
        range        = max - min;
    }
    else
    {
        range        = 1.;
    }
    inverseRange = 1./range;
    multiplier   = inverseRange*(tableEntries-1);
}


// ****************************************************************************
//  Method: avtOpacityMap::SetTable
//
//  Purpose:
//      Allows the table to be set from some outside array.
//
//  Arguments:
//      arr     The new table.
//      te      The number of entries in arr.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
//  Modifications:
//
//    Hank Childs, Mon Feb 19 09:01:31 PST 2001
//    Made opacity a float instead of an unsigned char.
//
//    Hank Childs, Tue Dec 21 16:39:22 PST 2004
//    Add support for attenuation.
//
//    Brad Whitlock, Thu Feb 16 10:42:43 PST 2017
//    fix alpha calculation. Set transferFn1D too.
//
// ****************************************************************************

void
avtOpacityMap::SetTable(unsigned char *arr, int te, double attenuation)
{
    if (attenuation < 0. || attenuation > 1.)
    {
        debug1 << "Bad attenuation value " << attenuation << std::endl;
        EXCEPTION0(ImproperUseException);
    }

    if (table != NULL)
        delete [] table;
    if (transferFn1D != NULL)
        delete [] transferFn1D;

    tableEntries = te;
    table = new RGBA[tableEntries];
    transferFn1D = new _RGBA[tableEntries];
    for (int i = 0 ; i < tableEntries ; i++)
    {
        table[i].R = arr[i*4];
        table[i].G = arr[i*4+1];
        table[i].B = arr[i*4+2];
        double alpha = (static_cast<double>(arr[i*4+3]) / 255.) * attenuation;
        table[i].A = static_cast<unsigned char>(static_cast<int>(alpha * 255.));

        transferFn1D[i].R = static_cast<float>(arr[i*4]) / 255.f;
        transferFn1D[i].G = static_cast<float>(arr[i*4+1]) / 255.f;
        transferFn1D[i].B = static_cast<float>(arr[i*4+2]) / 255.f;
        transferFn1D[i].A = alpha;
    }

    //
    // We need to set the intermediate vars again since the table size has
    // potentially changed.
    //
    SetIntermediateVars();
}


// ****************************************************************************
//  Method: avtOpacityMap::SetTable
//
//  Purpose:
//      Allows the table to be set from some outside array in the predefined
//      RGBA format. Matches the SLIVR renderer.
//
//  Arguments:
//      arr             The new table in RGBA format.
//      te              The number of entries in arr.
//      attenuation     The attenuation parameter specified
//      over            Reducing based on the number of slices
//
//  Programmer: Pascal Grosset
//  Creation:   December 11, 2012
//
// ****************************************************************************
void
avtOpacityMap::SetTable(unsigned char *arr, int te, double attenuation, float over)
{
    if (attenuation < -1. || attenuation > 1.)
    {
        debug1 << "Bad attenuation value " << attenuation << std::endl;
        EXCEPTION0(ImproperUseException);
    }

    if (table != NULL)
    {
        delete [] table;
    }

    tableEntries = te;
    table = new RGBA[tableEntries];
    for (int i = 0 ; i < tableEntries ; i++)
    {
        double bp = tan(1.570796327 * (0.5 - attenuation*0.49999));
        double alpha = pow((float) arr[i*4+3] / 255.f, (float)bp);
        alpha = 1.0 - pow((1.0 - alpha), 1.0/over);

        table[i].R = arr[i*4];
        table[i].G = arr[i*4+1];
        table[i].B = arr[i*4+2];
        table[i].A = alpha;
    }

    //
    // We need to set the intermediate vars again since the table size has
    // potentially changed.
    //
    SetIntermediateVars();
}


// ****************************************************************************
//  Method: avtOpacityMap::SetTableFloat
//
//  Purpose:
//      Allows the table to be set from some outside array in the predefined
//      RGBA format. Matches the SLIVR renderer.
//
//  Arguments:
//      arr             The new table in RGBA format.
//      te              The number of entries in arr.
//      attenuation     The attenuation parameter specified
//      over            Reducing based on the number of slices
//
//  Programmer: Pascal Grosset
//  Creation:   June 6, 2013
//
// ****************************************************************************
void
avtOpacityMap::SetTableFloat(unsigned char *arr, int te, double attenuation, float over)
{
    if (attenuation < -1. || attenuation > 1.)
    {
        debug1 << "Bad attenuation value " << attenuation << std::endl;
        EXCEPTION0(ImproperUseException);
    }

    if (transferFn1D != NULL)
    {
        delete [] transferFn1D;
    }

    tableEntries = te;
    transferFn1D = new _RGBA[tableEntries]();
    minVisibleScalarIndex =  maxVisibleScalarIndex = -1;
    for (int i = 0 ; i < tableEntries ; i++)
    {
        double bp = tan(1.570796327 * (0.5 - attenuation*0.49999));
        double alpha = pow((float) arr[i*4+3] / 255.f, (float)bp);
        alpha = 1.0 - pow((1.0 - alpha), 1.0/over);

        transferFn1D[i].R = (float)arr[i*4+0]/255.*alpha;
        transferFn1D[i].G = (float)arr[i*4+1]/255.*alpha;
        transferFn1D[i].B = (float)arr[i*4+2]/255.*alpha;
        transferFn1D[i].A = alpha;
        if (alpha != 0 && minVisibleScalarIndex == -1){
            minVisibleScalarIndex = i;
            //debug5 << "starting alpha = 0 at i= " << i << std::endl;
        }

        //debug5 << i << " : " << transferFn1D[i].R << ", " << transferFn1D[i].G << ", " << transferFn1D[i].B <<  ", " << transferFn1D[i].A << std::endl;
    }
    for (int i=tableEntries-1; i>=0; i--)
    {
        if (transferFn1D[i].A != 0 && maxVisibleScalarIndex == -1){
            maxVisibleScalarIndex = i;
            //debug5 << "ending alpha = 0 at i= " << i << std::endl;
        }
    }


    //debug5 << "minVisibleScalarIndex: " << minVisibleScalarIndex << "   maxVisibleScalarIndex: " << maxVisibleScalarIndex << std::endl;

    //
    // We need to set the intermediate vars again since the table size has
    // potentially changed.
    //
    SetIntermediateVars();
}
// ****************************************************************************
//  Method: avtOpacityMap::GetMinVisibleScalar
//
//  Purpose:
//      Get the minimum scalar value that is visible
//
//  Programmer: Pascal Grosset
//  Creation:   July 14, 2016
//
// ****************************************************************************
double avtOpacityMap::GetMinVisibleScalar()
{
    return minVisibleScalar;
}


// ****************************************************************************
//  Method: avtOpacityMap::GetMaxVisibleScalar
//
//  Purpose:
//      Get the maximum scalar value that is visible
//
//  Programmer: Pascal Grosset
//  Creation:   July 14, 2016
//
// ****************************************************************************
double avtOpacityMap::GetMaxVisibleScalar()
{
    return maxVisibleScalar;
}


// ****************************************************************************
//  Method: avtOpacityMap::computeVisibleRange
//
//  Purpose:
//      Compute the scalar range that will be visible
//
//  Programmer: Pascal Grosset
//  Creation:   July 14, 2016
//
// ****************************************************************************
void avtOpacityMap::computeVisibleRange()
{
    double scalarRange = max - min;
    if (minVisibleScalarIndex == 0)
        minVisibleScalar =  min;
    else
        minVisibleScalar = ( ((float)minVisibleScalarIndex/(tableEntries-1)) * scalarRange) + min;
    


    if (maxVisibleScalarIndex == tableEntries-1)
        maxVisibleScalar =  max;
    else
        maxVisibleScalar = ( ((float)maxVisibleScalarIndex/(tableEntries-1)) * scalarRange) + min;


     debug5 << "max: " << max << "  min: " << min << "  scalarRange: " << scalarRange << "  minVisibleScalarIndex: " << minVisibleScalarIndex <<
             "  maxVisibleScalarIndex: " << maxVisibleScalarIndex << "   tableEntries: " << tableEntries << 
             "  maxVisibleScalar: " << maxVisibleScalar << "   minVisibleScalar: " << minVisibleScalar << std::endl;
}

// ****************************************************************************
//  Method: avtOpacityMap::SetTable
//
//  Purpose:
//      Allows the table to be set from some outside array in the predefined
//      RGBA format.
//
//  Arguments:
//      arr     The new table in RGBA format.
//      te      The number of entries in arr.
//
//  Programmer: Hank Childs
//  Creation:   February 19, 2001
//
//  Modifications:
//
//    Hank Childs, Tue Dec 21 16:39:22 PST 2004
//    Add support for attenuation.
//
// ****************************************************************************

void
avtOpacityMap::SetTable(RGBA *arr, int te, double attenuation)
{
    if (attenuation < 0. || attenuation > 1.)
    {
        debug1 << "Bad attenuation value " << attenuation << std::endl;
        EXCEPTION0(ImproperUseException);
    }

    if (table != NULL)
    {
        delete [] table;
    }

    tableEntries = te;
    table = new RGBA[tableEntries];
    for (int i = 0 ; i < tableEntries ; i++)
    {
        table[i].R = arr[i].R;
        table[i].G = arr[i].G;
        table[i].B = arr[i].B;
        table[i].A = arr[i].A * attenuation;
        if (table[i].A < 0. || table[i].A > 1.)
        {
            debug1 << "Bad value " << table[i].A << std::endl;
            EXCEPTION0(ImproperUseException);
        }
    }

    //
    // We need to set the intermediate vars again since the table size has
    // potentially changed.
    //
    SetIntermediateVars();
}





// ****************************************************************************
//  Method: avtOpacityMap::GetOpacity
//
//  Purpose:
//      Gets the opacity for a specific value.  This method should not be used
//      when performing a lot of mappings and is only provided for
//      completeness.  When lots of mappings are done, the GetTable method
//      should be used in conjunction with Quantize.
//
//  Arguments:
//      v       The value.
//
//  Returns:    The <R,G,B,A> corresponding to v.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
// ****************************************************************************

const RGBA &
avtOpacityMap::GetOpacity(double v)
{
    return table[Quantize(v)];
}


// ****************************************************************************
//  Method: avtOpacityMap::AddRange
//
//  Purpose:
//      Adds a range to the table.
//
//  Arguments:
//      lo     The low part of the range.
//      hi     The high part of the range.
//      rgba   The opacity and color the range should have.
//
//  Programmer: Hank Childs
//  Creation:   February 3, 2001
//
// ****************************************************************************

void
avtOpacityMap::AddRange(double lo, double hi, RGBA &rgba)
{
    int low  = Quantize(lo);
    int high = Quantize(hi);
    for (int i = low ; i <= high ; i++)
    {
        table[i].R = rgba.R;
        table[i].G = rgba.G;
        table[i].B = rgba.G;
        table[i].A = rgba.A;
    }
}


ostream &
operator << (ostream &os, const avtOpacityMap &obj)
{
    os << "tableEntries = " << obj.tableEntries << endl;
    os << "table = {";
    for(int i = 0; i < obj.tableEntries; ++i)
    {
        os << "[" << i << "] = {"
           << static_cast<int>(obj.table[i].R) << ", "
           << static_cast<int>(obj.table[i].G) << ", "
           << static_cast<int>(obj.table[i].B) << ", "
           << static_cast<int>(obj.table[i].A) << "}" 
           << endl;
    }
    os << "}";
    os << "transferFn1D = {";
    for(int i = 0; i < obj.tableEntries; ++i)
    {
        os << "[" << i << "] = {"
           << obj.transferFn1D[i].R << ", "
           << obj.transferFn1D[i].G << ", "
           << obj.transferFn1D[i].B << ", "
           << obj.transferFn1D[i].A << "}"
           << endl;
    }
    os << "}";
    os << "min =" << obj.min << endl;
    os << "max =" << obj.max << endl;
    os << "range =" << obj.range << endl;
    os << "inverseRange =" << obj.inverseRange << endl;
    os << "multiplier = " << obj.multiplier << endl;

    return os;
}
