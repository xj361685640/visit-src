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
#include <MovieSequenceCompositeTransition.h>

#include <WidgetDataNode.h>
#include <QvisCompositeTransition.h>
#include <DebugStream.h>

// Icons
#include <icons/ms_comp_fadein.xpm>
#include <icons/ms_comp_fadeout.xpm>
#include <icons/ms_comp_lr_slide.xpm>
#include <icons/ms_comp_rl_slide.xpm>
#include <icons/ms_comp_tb_slide.xpm>
#include <icons/ms_comp_bt_slide.xpm>

// ****************************************************************************
// Method: MovieSequenceCompositeTransition::MovieSequenceCompositeTransition
//
// Purpose: 
//   Base class constructor for composite transition sequences.
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 14 10:44:20 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

MovieSequenceCompositeTransition::MovieSequenceCompositeTransition() :
    MovieSequence()
{
}

// ****************************************************************************
// Method: MovieSequenceCompositeTransition::~MovieSequenceCompositeTransition
//
// Purpose: 
//   Destructor.
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 14 10:44:50 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

MovieSequenceCompositeTransition::~MovieSequenceCompositeTransition()
{
}

// ****************************************************************************
// Method: MovieSequenceCompositeTransition::CreateUI
//
// Purpose: 
//   Create the user interface for the sequence.
//
// Returns:    A pointer to the new user interface object.
//
// Note:       
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 14 10:45:01 PDT 2006
//
// Modifications:
//   Brad Whitlock, Tue Apr  8 10:33:54 PDT 2008
//   SequenceMenuName now returns QString.
//
//   Brad Whitlock, Tue Oct  7 11:21:26 PDT 2008
//   Qt 4.
//
// ****************************************************************************

QWidget *
MovieSequenceCompositeTransition::CreateUI()
{
    QvisCompositeTransition *ui = new QvisCompositeTransition(Pixmap(), 0);
    ui->setObjectName(GetName().c_str());
    ui->setTitle(SequenceMenuName());

    return ui;
}

// ****************************************************************************
// Method: MovieSequenceCompositeTransition::ReadUIValues
//
// Purpose: 
//   Gets the values from the data node and updates the user interface.
//
// Arguments:
//   ui   : The user interface.
//   node : The node in which to insert the sequence's data values.
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 14 10:40:58 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
MovieSequenceCompositeTransition::ReadUIValues(QWidget *ui, DataNode *node)
{
    const char *mName = "MovieSequenceCompositeTransition::ReadUIValues: ";

    if(node != 0)
    {
        QvisCompositeTransition *UI = (QvisCompositeTransition *)ui;

        // Read the number of frames.
        DataNode *nFramesNode = node->GetNode("nFrames");
        if(nFramesNode !=0 && nFramesNode->GetNodeType() == INT_NODE)
        {
            UI->setNFrames(nFramesNode->AsInt());
        }
        else
        {
            debug4 << mName << "nFrames not found in node." << endl;
        }

        // Read the reverse flag.
        DataNode *reverseNode = node->GetNode("reverse");
        if(reverseNode !=0 && reverseNode->GetNodeType() == BOOL_NODE)
        {
            UI->setReverse(reverseNode->AsBool());
        }
        else
        {
            debug4 << mName << "reverse not found in node." << endl;
        }
    }
}

// ****************************************************************************
// Method: MovieSequenceCompositeTransition::WriteUIValues
//
// Purpose: 
//   Gets data values from the user interface and inserts them into the
//   data node representation where they can be written to the template
//   specification file.
//
// Arguments:
//   ui   : The user interface.
//   node : The node in which to insert the sequence's data values.
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 14 10:40:58 PDT 2006
//
// Modifications:
//   
// ****************************************************************************

void
MovieSequenceCompositeTransition::WriteUIValues(QWidget *ui, DataNode *node)
{
    if(node != 0)
    {
        QvisCompositeTransition *UI = (QvisCompositeTransition *)ui;
        node->RemoveNode("nFrames");
        node->AddNode(new DataNode("nFrames", UI->getNFrames()));

        node->RemoveNode("reverse");
        node->AddNode(new DataNode("reverse", UI->getReverse()));
    }
}

//
// Pixmap and menu name methods for the derived classes.
//

QPixmap
MovieSequenceCompositeFadeIn::Pixmap()
{
    return QPixmap(ms_comp_fadein_xpm);
}

QString
MovieSequenceCompositeFadeIn::SequenceMenuName() const
{
    return tr("Fade in viewport");
}

////////////////////////////////////////////////////////////////////////////////

QPixmap
MovieSequenceCompositeFadeOut::Pixmap()
{
    return QPixmap(ms_comp_fadeout_xpm);
}

QString
MovieSequenceCompositeFadeOut::SequenceMenuName() const
{
    return tr("Fade out viewport");
}

////////////////////////////////////////////////////////////////////////////////

QPixmap
MovieSequenceCompositeLRSlide::Pixmap()
{
    return QPixmap(ms_comp_lr_slide_xpm);
}

QString
MovieSequenceCompositeLRSlide::SequenceMenuName() const
{
    return tr("Slide in viewport left to right");
}

////////////////////////////////////////////////////////////////////////////////

QPixmap
MovieSequenceCompositeRLSlide::Pixmap()
{
    return QPixmap(ms_comp_rl_slide_xpm);
}

QString
MovieSequenceCompositeRLSlide::SequenceMenuName() const
{
    return tr("Slide in viewport right to left");
}

////////////////////////////////////////////////////////////////////////////////

QPixmap
MovieSequenceCompositeTBSlide::Pixmap()
{
    return QPixmap(ms_comp_tb_slide_xpm);
}

QString
MovieSequenceCompositeTBSlide::SequenceMenuName() const
{
    return tr("Slide in viewport top to bottom");
}

////////////////////////////////////////////////////////////////////////////////

QPixmap
MovieSequenceCompositeBTSlide::Pixmap()
{
    return QPixmap(ms_comp_bt_slide_xpm);
}

QString
MovieSequenceCompositeBTSlide::SequenceMenuName() const
{
    return tr("Slide in viewport bottom to top");
}

