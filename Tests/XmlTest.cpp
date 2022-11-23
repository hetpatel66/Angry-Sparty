/**
 * @file XmlTest.cpp
 * @author michael_tan
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

class XmlTest : public ::testing::Test {
protected:
    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
     *  Test an game with items
     */
    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;


        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<background width=\"14\\.22.*\" height=\"8\" image=\"background1.png\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<slingshot x=\"-5\\.5.*\" y=\"0\\.25.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<block x=\"0\" y=\"0\\.125.*\" width=\"14\\.22.*\" height=\"0\\.23.*\" repeat-x=\"35\" type=\"static\" image=\"sand.png\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<foe x=\"3\\.09669.*\" y=\"1\\.8305.*\" angle=\"22\\.8317.*\" radius=\"0\\.3.*\" down=\"1\" image=\"foeO.png\"")));

    }

};

TEST_F(XmlTest, Construct){
    Game game;
}

TEST_F(XmlTest, Load) {
    Game gameTest;
    auto fileTest =  L"../resources/levels/levelTest.xml";

    TestAllTypes(fileTest);

    Game gameTest1;
    auto fileTest1 =  L"../resources/levels/level0.xml";

    gameTest1.Load(0);
    ASSERT_TRUE(gameTest1.GetOuterCount() == 2);
    ASSERT_TRUE(gameTest1.GetItemsCount() == 8);
    ASSERT_TRUE(gameTest1.GetAngryCount() == 2);

    Game gameTest2;
    auto fileTest2 =  L"../resources/levels/level1.xml";

    gameTest2.Load(1);
    ASSERT_TRUE(gameTest2.GetOuterCount() == 2);
    ASSERT_TRUE(gameTest2.GetItemsCount() == 19);
    ASSERT_TRUE(gameTest2.GetAngryCount() == 3);


    Game gameTest3;
    auto fileTest3 =  L"../resources/levels/level2.xml";

    gameTest3.Load(2);
    ASSERT_TRUE(gameTest3.GetOuterCount() == 2);
    ASSERT_TRUE(gameTest3.GetItemsCount() == 24);
    ASSERT_TRUE(gameTest3.GetAngryCount() == 6);

}

