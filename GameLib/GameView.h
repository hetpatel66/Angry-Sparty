/**
 * @file GameView.h
 * @author Elio Moussa, Darshil Patel
 *
 * Class that implements the child window our program draws in.
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 *
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"
#include "Level.h"

/**
 * Provide the visuals for the Game.
 */
class GameView : public wxWindow{
private:
    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    double mTime = 0;
    /// Timer
    wxTimer mTimer;
    /// An object that describes our game
    Game  mGame;
    /// Level
    Level mLevel;

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
public:
    void Initialize(wxFrame* parent);
    void LevelLoad(int level);
    void OnLevel0(wxCommandEvent&);
    void OnLevel1(wxCommandEvent&);
    void OnLevel2(wxCommandEvent&);
    void OnLevel3(wxCommandEvent&);
    void OnAddSlingShot(wxCommandEvent&);
    /// Stop GameView Timer
    void Stop() {mTimer.Stop();}
};

#endif //PROJECT1_GAMEVIEW_H
