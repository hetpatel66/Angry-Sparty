/**
 * @file Background.cpp
 * @author Het Patel
 */

#include "pch.h"
#include "Background.h"
#include <string>
#include "Consts.h"

using namespace std;

/// Background filename
const std::wstring backgroundName = L"images/background1.png";

/**
 * Constructor for Background class
 * @param game
 */
Background::Background(Game* game) : Item(game, backgroundName)
{
}

/**
 * Draws background
 * @param graphics
 */
void Background::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = mWidth * Consts::MtoCM;
    auto hit = mHeight * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = mPicture;

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
                         -wid/2,
                         -hit,
                         wid, hit);
    graphics->PopState();

}

/**
 * Load the attributes for an block.
 * @param node The Xml node we are loading the item from
 */
void Background::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
    mImage = node->GetAttribute(L"image", L"").ToStdWstring();

    mImage.ToStdString();

    mImage = "images/" + mImage;

    mPicture = make_shared<wxBitmap>(
            mImage, wxBITMAP_TYPE_ANY);
}

/**  Test an x,y click location to see if it clicked
* on the game's background.
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
* (should return false)
*/
bool Background::HitTest(double x, double y) {
    return false;
}