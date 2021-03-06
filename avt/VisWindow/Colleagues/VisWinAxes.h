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
//                                VisWinAxes.h                               //
// ************************************************************************* //

#ifndef VIS_WIN_AXES_H
#define VIS_WIN_AXES_H
#include <viswindow_exports.h>


#include <VisWinColleague.h>


class vtkAxesActor2D;

class VisWindowColleagueProxy;

// ****************************************************************************
//  Class: VisWinAxes
//
//  Purpose:
//      This is a concrete colleague for the mediator VisWindow.  It puts
//      updating axes around 2D plots.
//
//  Programmer: Hank Childs
//  Creation:   June 9, 2000
//
//  Modifications:
//
//    Hank Childs, Fri Jul  7 10:43:43 PDT 2000
//    Added HasPlots, NoPlots, Add/RemoveAxesTo/FromWindow.
//
//    Hank Childs, Wed Jul 12 09:12:02 PDT 2000
//    Added data members and methods to adjust the precision and put the
//    numbers in scientific notation.
//
//    Kathleen Bonnell, Mon Jun 18 14:56:09 PDT 2001
//    Added methods for user-control of axes appearance.
//
//    Kathleen Bonnell, Fri Jul  6 14:09:00 PDT 2001
//    Added SetXGridVisibility, SetYGridVisibility.
//
//    Kathleen Bonnell, Wed May  8 14:06:50 PDT 2002
//    Added members xTitle and yTitle, methods StartCurveMode, StopCurveMode.
//
//    Eric Brugger, Wed Nov  6 07:58:25 PST 2002
//    Added SetTitleVisibility, SetAutoSetTicks, SetMajorTickMinimum,
//    SetMajorTickMaximum, SetMajorTickSpacing, SetMinorTickSpacing and
//    SetFontScaleFactor.
//
//    Eric Brugger, Fri Jan 24 09:03:00 PST 2003
//    Replaced SetFontScaleFactor with SetXLabelFontHeight,
//    SetYLabelFontHeight, SetXTitleFontHeight and SetYTitleFontHeight.
//
//    Eric Brugger, Fri Feb 28 11:32:39 PST 2003
//    Modified AdjustValues so that the arguments aren't passed by reference
//    because they are no longer modified.
//
//    Eric Brugger, Wed Jun 25 14:09:15 PDT 2003
//    I added SetLineWidth.
//
//    Kathleen Bonnell, Tue Dec 16 11:34:33 PST 2003
//    Added SetLabelScaling, autolabelscalng, userPowX, userPowY.
//
//    Brad Whitlock, Thu Jul 28 08:52:38 PDT 2005
//    Added the ability to specify the axis titles and units.
//
//    Kathleen Bonnell, Thu Mar 29 10:30:41 PDT 2007
//    Added AdjustLabelFormatForLogScale.
//
//    Kathleen Bonnell, Wed May  9 10:54:12 PDT 2007
//    Added bool args to AdjustLabelFormatForLogScale.
//
//    Kathleen Biagas, Wed Jan  8 14:16:04 PST 2014
//    Utilize new vtkAxisActor2D.
//
// ****************************************************************************

class VISWINDOW_API VisWinAxes : public VisWinColleague
{
  public:
                              VisWinAxes(VisWindowColleagueProxy &);
    virtual                  ~VisWinAxes();

    virtual void              SetForegroundColor(double, double, double);
    virtual void              UpdateView(void);
    virtual void              SetViewport(double, double, double, double);
    virtual void              UpdatePlotList(std::vector<avtActor_p> &);

    virtual void              Start2DMode(void);
    virtual void              Stop2DMode(void);

    virtual void              HasPlots(void);
    virtual void              NoPlots(void);

    virtual void              StartCurveMode(void);
    virtual void              StopCurveMode(void);

    void                      SetXTickVisibility(int, int);
    void                      SetYTickVisibility(int, int);
    void                      SetLabelsVisibility(int, int);
    void                      SetTitleVisibility(int, int);
    void                      SetVisibility(int);
    void                      SetTickLocation(int);
    void                      SetXGridVisibility(int);
    void                      SetYGridVisibility(int);
    void                      SetAutoSetTicks(int);
    void                      SetMajorTickMinimum(double, double);
    void                      SetMajorTickMaximum(double, double);
    void                      SetMajorTickSpacing(double, double);
    void                      SetMinorTickSpacing(double, double);
    void                      SetXLabelFontHeight(double);
    void                      SetYLabelFontHeight(double);
    void                      SetXTitleFontHeight(double);
    void                      SetYTitleFontHeight(double);
    void                      SetLineWidth(int);
    void                      SetLabelScaling(bool, int, int);

    void                      SetXTitle(const std::string &, bool);
    void                      SetXUnits(const std::string &, bool);
    void                      SetYTitle(const std::string &, bool);
    void                      SetYUnits(const std::string &, bool);

    void                      SetTitleTextAttributes(
                                  const VisWinTextAttributes &xAxis,
                                  const VisWinTextAttributes &yAxis);
    void                      SetLabelTextAttributes(
                                  const VisWinTextAttributes &xAxis,
                                  const VisWinTextAttributes &yAxis);
  protected:
    vtkAxesActor2D   *axes;

    int                       lastXPow, lastYPow;
    int                       lastXAxisDigits, lastYAxisDigits;
    bool                      addedAxes;
    char                      xTitle[256];
    char                      yTitle[256];
    int                       powX;
    int                       powY;
    char                      unitsX[256];
    char                      unitsY[256];
    bool                      autolabelScaling;
    int                       userPowX;
    int                       userPowY;
    bool                      userXTitle;
    bool                      userXUnits;
    bool                      userYTitle;
    bool                      userYUnits;
    VisWinTextAttributes      titleTextAttributes[2];
    VisWinTextAttributes      labelTextAttributes[2];

    void                      AdjustValues(double, double, double, double);
    void                      AdjustRange(double, double, double, double);
    void                      GetRange(double &, double &, double &, double &);
    void                      AddAxesToWindow(void);
    void                      RemoveAxesFromWindow(void);
    bool                      ShouldAddAxes(void);
    void                      SetTitle(void);

    void AdjustLabelFormatForLogScale(double, double, double, double, bool[2]);
    void UpdateTitleTextAttributes(double fr, double fg, double fb);
    void UpdateLabelTextAttributes(double fr, double fg, double fb);
};


#endif


