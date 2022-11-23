/**
 * @file ItemBlock.cpp
 * @author Darshil Patel
 */

#include "pch.h"
#include "ItemBlock.h"
#include "Game.h"
#include <b2_fixture.h>
#include <b2_polygon_shape.h>
#include "Consts.h"


using namespace std;

/// Name of image path name
const std::wstring mFolder = L"images/";

/**
 * Destructor
 */
ItemBlock::~ItemBlock()
{
}

/**
 * Constructor
 * @param game The game this item is a member of
 * @param filename The wstring representing the
 * filename of the respective block
 */
ItemBlock::ItemBlock(Game *game, const std::wstring &filename) :Item(game, filename)
{
    mItemBlockImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Draw the game
 * @param graphics The device context to draw on
 */
void ItemBlock::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    /// TA helped me with the draw implementation
    auto body = GetBody();
    auto angle = body->GetAngle();
    auto position = body->GetPosition();

    b2Vec2 max = mVertices[0];
    b2Vec2 min = mVertices[0];
    for (auto i : mVertices){
        max.x = fmax(max.x,i.x);
        max.y = fmax(max.y,i.y);
        min.x = fmin(min.x,i.x);
        min.y = fmin(min.y,i.y);
    }
    auto average = max - min;
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;
    graphics->PushState();
    graphics->Translate(x,y);
    graphics->Rotate(angle);
    std::shared_ptr<wxBitmap> bitmapBlock = mItemBlockBitmap;
    graphics->DrawBitmap(*bitmapBlock,min.x*Consts::MtoCM,min.y*Consts::MtoCM,average.x*Consts::MtoCM,
            average.y*Consts::MtoCM);
    graphics->PopState();
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
void ItemBlock::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    double width;
    double height;
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"width", L"0").ToDouble(&width);
    node->GetAttribute(L"height", L"0").ToDouble(&height);
    mSize = {float(width), float(height)};
    node->GetAttribute(L"friction", L"0.5").ToDouble(&mFriction);
    node->GetAttribute(L"restitution", L"0.5").ToDouble(&mRestitution);
    node->GetAttribute(L"density", L"1.0").ToDouble(&mDensity);

    mStatic = (node->GetAttribute(L"type", L"static") == L"static");

}

void ItemBlock::InstallPhysics(std::shared_ptr<Physics> physics)
{
    mPhysics = physics;
    b2World* world = physics->GetWorld();

    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mSize.x/2, mSize.y/2);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = GetPosition();
    bodyDefinition.angle = mAngle;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        body->CreateFixture(&box, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        body->CreateFixture(&fixtureDef);
    }
}

std::shared_ptr<wxBitmap> ItemBlock::Bitmap()
{
    if (mItemBlockBitmap == nullptr){
        mItemBlockBitmap = std::make_shared<wxBitmap>(*mItemBlockImage);
    }
    return mItemBlockBitmap;
}

bool ItemBlock::HitTest(double x, double y)
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