/**
 * @file SlingShot.cpp
 * @author Anand Pinnamaneni
 */

#include "pch.h"
#include "SlingShot.h"
#include "Image.h"
#include "Consts.h"
#include "Item.h"
#include "Sparty.h"
#include <cmath>

using namespace std;

/// Base filename for the slingshot image
const std::wstring WoodSlingshotBaseName = L"images/slingshot.png";

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

/// Back band attachment point
const b2Vec2 WoodSlingshotBandAttachBack = b2Vec2(-0.15f, 1.12f);

/// Front band attachment point
const b2Vec2 WoodSlingshotBandAttachFront = b2Vec2(0.15f, 1.2f);

/// Maximum amount the slingshot can be pulled in meters
const double WoodSlingshotMaximumPull = 1;

/// Pull angles from -pi to this value are allowed
const double SlingshotMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double SlingshotMinimumPositivePullAngle = 2.42;

/// Width of the slingshot band in centimeters
const int SlingshotBandWidth = 15;

/// The slingshot band colour
const wxColour SlingshotBandColor = wxColour(55, 18, 1);

/**
 * Constructor
 * @param game
 */
SlingShot::SlingShot(Game* game) : Item(game, WoodSlingshotBaseName)
{
}


/**
 * Draw the SlingShot for the game
 * @param graphics The device context to draw on
 */
void SlingShot::Draw(const std::shared_ptr<wxGraphicsContext> graphics) {
    graphics->PushState();

    graphics->Translate(GetX() * Consts::MtoCM,
                        GetY() * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -WoodSlingshotSize.x / 2 * Consts::MtoCM;

    // And the top
    double y = WoodSlingshotSize.y * Consts::MtoCM;

    mPicture = make_shared<wxBitmap>(
            WoodSlingshotBaseName, wxBITMAP_TYPE_ANY);

    std::shared_ptr<wxBitmap> bitmap = mPicture;

    graphics->Translate(0, y);
    graphics->Scale(1, -1);

    double xw = WoodSlingshotSize.x / 1 * Consts::MtoCM;

    for (int ix = 0; ix < 1; ix++) {
        graphics->DrawBitmap(*bitmap,
                             x,
                             0,
                             xw, WoodSlingshotSize.y * Consts::MtoCM);

        x += xw;
    }
    graphics->PopState();

    graphics->PushState();
    b2Vec2 pos(GetX(), GetY());
    auto frontAttach = WoodSlingshotBandAttachFront + pos;
    auto backAttach = WoodSlingshotBandAttachBack + pos;
    frontAttach *= Consts::MtoCM;
    backAttach *= Consts::MtoCM;
    graphics->SetPen(wxPen(SlingshotBandColor, SlingshotBandWidth));
    mSparty = GetGame()->Playing();

    if (mSparty != nullptr && mSparty->GetState() == false) {
        auto temp = mSparty;
        mSparty->Load(b2Vec2(0.0f + mX, 1.16f + mY));
//        mSparty->DynamicMovement2();
        auto temp_2 = temp->GetBody();
        auto temp_3 = temp_2->GetPosition();
        graphics->StrokeLine(backAttach.x, backAttach.y, temp_3.x * Consts::MtoCM, temp_3.y* Consts::MtoCM);
        graphics->StrokeLine(temp_3.x* Consts::MtoCM, temp_3.y* Consts::MtoCM, frontAttach.x, frontAttach.y);
    } else {
        graphics->StrokeLine(backAttach.x, backAttach.y,frontAttach.x,frontAttach.y);
    }
    graphics->PopState();

}

/**  Test an x,y location to see
 * if it registered slingshot pull
 * @param x X location
 * @param y Y location
 * @return bool which determines if we did or didn't click.
 */
bool SlingShot::HitTest(double x, double y)
{
    return false;
}

/**
 * Load the attributes for an block.
 * @param node The Xml node we are loading the item from
 */
void SlingShot::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 * Used to launch the sparty
 */
void SlingShot::Launch() {
    mSparty = GetGame()->Playing();
    mSparty->Load(b2Vec2(mX, mY));
    if (mSparty->GetIfReleased() == true) {
        auto location = mSparty->SlingshotLoad();
        if (mSparty != nullptr) {
            b2Vec2 toAngry = location - mLoadPoint;
            if (0.1 > toAngry.Length()) {
                toAngry = b2Vec2(0.0f + mX, 1.16f + mY);
            }
            double theta = atan2(location.y - mLoadPoint.y, location.x - mLoadPoint.x);
            if (theta < SlingshotMaximumNegativePullAngle) {
                theta = SlingshotMaximumNegativePullAngle;
            }
            if (theta > SlingshotMinimumPositivePullAngle) {
                theta = SlingshotMinimumPositivePullAngle;
            }
            if (toAngry.Length() >= WoodSlingshotMaximumPull) {
                toAngry.x = toAngry.x / toAngry.Length();
                toAngry.y = toAngry.y / toAngry.Length();
            }
            mSparty->DynamicMovement(-toAngry);
        }
        GetGame()->Launched();
    }
}