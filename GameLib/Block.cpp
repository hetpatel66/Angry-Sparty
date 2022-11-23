/**
 * @file Block.cpp
 * @author Het Patel
 */

#include "pch.h"
#include <string>
#include "Block.h"
#include "Consts.h"
#include "ItemBlock.h"
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

using namespace std;

/// Block filename
const std::wstring sampleBlock = L"images/debrisGlass_1.png";

/**
 * Constructor
 * @param game The game this item is a member of
 */
Block::Block(Game *game) : ItemBlock(game, sampleBlock)
{

}

/**
 * Draw the blocks for the game
 * @param graphics The device context to draw on
 */
void Block::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(position.x * Consts::MtoCM,
                        position.y * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mSize.x/2 * Consts::MtoCM;

    // And the top
    double y = mSize.y/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mSize.x / mRepeatX * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = mPicture;

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix=0; ix<mRepeatX;  ix++)
    {
        graphics->DrawBitmap(*bitmap,
                             x,
                             0,
                             xw, mSize.y * Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}

/**
 * Load the attributes for an block.
 * @param node The Xml node we are loading the item from
 */
void Block::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);

    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
    mSize.x = mWidth;
    mSize.y = mHeight;
    node->GetAttribute(L"repeat-x", L"1").ToDouble(&mRepeatX);
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"friction", L"0.5").ToDouble(&mFriction);
    node->GetAttribute(L"restitution", L"0.5").ToDouble(&mRestitution);
    node->GetAttribute(L"density", L"1.0").ToDouble(&mDensity);
    mType = node->GetAttribute(L"type", L"").ToStdWstring();
    mImage = node->GetAttribute(L"image", L"").ToStdWstring();

    mImage.ToStdString();

    mImage = "images/" + mImage;

    mPicture = make_shared<wxBitmap>(
            mImage, wxBITMAP_TYPE_ANY);

    if (mType == L"static"){
        mStatic = TRUE;
    }
}

/**  Test an x,y click location to see if it clicked
* on some block in the game.
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
*/
bool Block::HitTest(double x, double y)
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
 * Install physics system within block
 * @param physics smart pointer to the physics variable used in the function.
 */
void Block::InstallPhysics(std::shared_ptr<Physics> physics)
{

    b2World* world = physics->GetWorld();

    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mSize.x/2, mSize.y/2);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = b2Vec2(mX, mY);
    bodyDefinition.angle = mAngle * Consts::DtoR;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    mBody = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        mBody->CreateFixture(&box, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        mBody->CreateFixture(&fixtureDef);
    }
}