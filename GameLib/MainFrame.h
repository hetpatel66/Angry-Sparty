/**
 * @file MainFrame.h
 * @author Darshil Patel
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// GameView object
    GameView *mGameView;
public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent &event);
};

#endif //PROJECT1_MAINFRAME_H
