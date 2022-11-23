/**
 * @file GameTest.cpp
 * @author Darshil Patel
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <SlingShot.h>
#include <wx/filename.h>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

class GameTest : public::testing::Test
{
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir()+L"/game";
        if (!wxFileName::DirExists(path)) {
            wxFileName::Mkdir(path);
        }
        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString& filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }


};

TEST(GameTest, Construct){
    Game game;
}

TEST(GameTest, HitTest){
    Game game2;
    ASSERT_EQ(game2.HitTest(100, 200), nullptr) <<
                                                   L"Testing empty game";

}
