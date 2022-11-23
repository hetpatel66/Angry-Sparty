/**
 * @file Item.cpp
 * @author Het Patel, Darshil Patel, Michael Tan
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

#include <b2_fixture.h>

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Constructor
 * @param game The game this item is a member of
 * @param filename The filename that corresponds to the item
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game)
{

}

/**
 * Constructor
 */
Item::Item()
{
}

/**
 * Draw an item for game
 * @param graphics The device context to draw on
 */
void Item::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap.IsNull()) {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }

    double mWidth = mItemImage->GetWidth();
    double mHeight = mItemImage->GetHeight();
    graphics->DrawBitmap(mItemBitmap,
            int(GetX() - mWidth / 2),
            int(GetY() - mHeight / 2),mWidth,mHeight);
}

/**
 * Compute the distance from this item to another item
 * @param item Item we are computing the distance to
 * @return Distance in pixels
 */
double Item::DistanceTo(const std::shared_ptr<Item>& item) const
{
    auto dx = item->GetX() - GetX();
    auto dy = item->GetY() - GetY();
    return sqrt(dx * dx + dy * dy);
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 * Create a fixture and assign a given shape to it.
 * A fixture connects a shape to a body.
 * @param shape Shape to assign.
 * @param density Density to assign.
 * @return the created b2Fixture object
 */
b2Fixture* Item::CreateFixture(b2Shape* shape, float density)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    return mBody->CreateFixture(&fixtureDef);
}

/**
 * Set the transform for the item.
 * @param location Item location in meters
 * @param angle Angle in radians
 */
void Item::SetTransform(const b2Vec2& location, double angle)
{
    mBody->SetTransform(location, (float)angle);
}

/**
 * Get the phy
 * @return
 */
b2World* Item::GetWorld()
{
    return mGame->WorldGet();
}

/**
 * Install physics system within item
 * @param physics smart pointer to the physics variable used in the function.
 */
void Item::InstallPhysics(std::shared_ptr<Physics> physics)
{
}

/**  Test an x,y click location to see if it clicked
* on some item in the game.
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
*/
bool Item::HitTest(double x, double y)
{
    auto fixture = GetBody()->GetFixtureList();
    for( ; fixture != nullptr; fixture = fixture->GetNext())
    {
        if(fixture->TestPoint(b2Vec2(x, y)))
        {
            return true;
        }
    }
    return false;
}
/**
 * kill the items
 * TA suggested to make this function
 */
void Item::Kill()
{
    mKill = true;
}

/**
 * Boolean to see if its released.
 * @return b2vec2
 */
bool Item::Release(b2Vec2)
{
    return false;
}


/**
 * Velocity
 * TA suggested to make this function
 * @returns bool stating if length is correct
 */
bool Item::Velocity()
{
    auto speed = mBody->GetLinearVelocity();
    auto length = speed.Length();
    if (length < 1){
        return true;
    }
    return false;
}
