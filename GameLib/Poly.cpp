/**
 * @file Poly.cpp
 * @author Het Patel
 */

#include "pch.h"
#include "Poly.h"
#include <string>
#include "Consts.h"
#include <b2_polygon_shape.h>
#include <b2_fixture.h>

using namespace std;

/// Block filename
const std::wstring samplePoly = L"images/elementMetal002.png";

/**
 * Constructor
 * @param game The game this item is a member of
 */
Poly::Poly(Game *game) : ItemBlock(game, samplePoly)
{

}

/**
 * Draw the poly for the game
 * @param graphics The device context to draw on
 */
void Poly::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    // Find the minimum and maximum x/y values
    b2Vec2 minimums = mVertices[0];
    b2Vec2 maximums = mVertices[0];
    for(auto v : mVertices)
    {
        minimums.x = fmin(minimums.x, v.x);
        minimums.y = fmin(minimums.y, v.y);
        maximums.x = fmax(maximums.x, v.x);
        maximums.y = fmax(maximums.y, v.y);
    }

    auto size = maximums - minimums;

    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxBitmap> bitmap = mPicture;

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
                         minimums.x * Consts::MtoCM,
                         minimums.y * Consts::MtoCM,
                         size.x * Consts::MtoCM,
                         size.y * Consts::MtoCM);

    graphics->PopState();

}


/**
 * Load the attributes for an poly.
 * @param node The Xml node we are loading the item from
 */
void Poly::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    mImage = node->GetAttribute(L"image", L"").ToStdWstring();
    mImage.ToStdString();
    mImage = "images/" + mImage;
    mPicture = make_shared<wxBitmap>(
            mImage, wxBITMAP_TYPE_ANY);


    auto child = node->GetChildren();
    for (; child; child = child->GetNext()) {
        double x, y;
        child->GetAttribute(L"x", L"0").ToDouble(&x);
        child->GetAttribute(L"y", L"0").ToDouble(&y);

        mVertices.push_back(b2Vec2 (x, y));
    }

}

/**  Test an x,y click location to see if it clicked
* on some poly in the game.
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
*/
bool Poly::HitTest(double x, double y)
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
 * Install physics system within poly
 * @param physics smart pointer to the physics variable used in the function.
 */
void Poly::InstallPhysics(std::shared_ptr<Physics> physics)
{
    b2World* world = physics->GetWorld();
    // Create the poly
    b2PolygonShape poly;
    poly.Set(&mVertices[0], mVertices.size());

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = b2Vec2(mX, mY);
    bodyDefinition.angle = mAngle * Consts::DtoR;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    mBody = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        mBody->CreateFixture(&poly, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &poly;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        mBody->CreateFixture(&fixtureDef);
    }
}