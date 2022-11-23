/**
 * @file GameView.cpp
 * @author Elio Moussa, Darshil Patel
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "Consts.h"
#include "Level.h"
#include "SlingShot.h"
#include "Poly.h"

using namespace std;
/// Frame duration in seconds
const double FrameDuration = 1.0/60.0;


/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */

void GameView::Initialize(wxFrame* parent)
{
    // initalize the game
    LevelLoad(1);
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);


    mTimer.SetOwner(this);
    mTimer.Start(int(FrameDuration*1000));
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);


    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel0, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddSlingShot, this, IDM_ADDSLINGSHOT);

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);

    mStopWatch.Start();

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
//    // Update until the game time matches
//    // the current time.
    auto newTime = mStopWatch.Time() * 0.001;
    while(mTime < newTime)
    {
        mTime += FrameDuration;
        mGame.Update(FrameDuration);
    }


    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();

    auto graphics =
            std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());

}

/**
 * Menu handler for Add Slingshot
 */
void GameView::OnAddSlingShot(wxCommandEvent&)
{
    auto item = make_shared<SlingShot>(&mGame);
    mGame.Add(item);
    Refresh();
}


/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event);
}

/**
* Handle the left mouse button down event
* @param event Mouse event
*/
void GameView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event Mouse event
*/
void GameView::OnMouseMove(wxMouseEvent &event)
{
    mGame.OnMouseMove(event);
}

/**
 * Load the level into game
 * @param level Level that gets loaded
 */
void GameView::LevelLoad(int level)
{
    mGame.Load(level);
    Refresh();
}

/**
 * Event handler for selecting 'Level 0'
 * from the menu
 */
void GameView::OnLevel0(wxCommandEvent&)
{
    LevelLoad(0);
    Refresh();
}

/**
 * Event handler for selecting 'Level 1'
 * from the menu
 */
void GameView::OnLevel1(wxCommandEvent&)
{
    LevelLoad(1);
    Refresh();
}

/**
 * Event handler for selecting 'Level 2'
 * from the menu
 */
void GameView::OnLevel2(wxCommandEvent&)
{
    LevelLoad(2);
    Refresh();
}

/**
 * Event handler for selecting 'Level 3'
 * from the menu
 */
void GameView::OnLevel3(wxCommandEvent&)
{
    LevelLoad(3);
    Refresh();
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Handle a keypress event
 * @param event Keypress event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    mGame.OnKeyDown(event);
}

/**
 * Handle a key up event
 * @param event Key release event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    mGame.OnKeyUp(event);
}



