/**
 * @file MainFrame.cpp
 * @author Darshil Patel
 */

#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{

    Create(nullptr, wxID_ANY, L"Angry Sparty",
            wxDefaultPosition,  wxSize( 1000,800 ));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    SetSizer( sizer );
    Layout();

    CreateStatusBar();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto viewMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);


    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(viewMenu, L"&View");
    menuBar->Append(helpMenu, L"&Help");

    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Level 3");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel0, mGameView, IDM_LEVEL0);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel1, mGameView, IDM_LEVEL1);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel2, mGameView, IDM_LEVEL2);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel3, mGameView, IDM_LEVEL3);

    SetMenuBar( menuBar );
    Bind(wxEVT_CLOSE_WINDOW,&MainFrame::OnClose,this);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About the game
 * @param event About event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Angry Sparty",
            L"About Scissor tailed flycatcher",
            wxOK,
            this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}