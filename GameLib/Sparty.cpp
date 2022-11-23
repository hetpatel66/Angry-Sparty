/**
 * @file Sparty.cpp
 * @author Michael Tan
 */

#include "pch.h"
#include "Sparty.h"
#include "AngrySparty.h"
#include "Item.h"
#include "Game.h"
#include <b2_fixture.h>
#include <b2_circle_shape.h>

using namespace std;

/// Sparty filename
const wstring SpartyImageName = L"images/gruff-sparty.png"; // put the file name of the sparty (.png)

/// The image to use for this sparty
const std::wstring HelmetSpartyImage = L"helmet-sparty.png";

/// The radius in meters
const double HelmetSpartyRadius = 0.25;

/// The velocity factor for Helmet Sparty
const float HelmetSpartyVelocityFactor = 20.0;

/// The image to use for this sparty
const std::wstring GruffSpartyImage = L"gruff-sparty.png";

/// The radius in meters
const double GruffSpartyRadius = 0.25;

/// The velocity factor for Gruff Sparty
const float GruffSpartyVelocityFactor = 12.0;

/**
 * Constructor
 * @param game The game
 */
Sparty::Sparty(Game *game) : Item(game, SpartyImageName)
{

}

/**
 * Draw the game
 * @param graphics The device context to draw on
 */
void Sparty::Draw(const std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    auto wid = mRadius * Consts::MtoCM * 2;
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;


    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxBitmap> bitmap = mPicture;

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
                         -wid/2,
                         -wid/2,
                         wid, wid);

    graphics->PopState();
    double endHeight = GetBody()->GetPosition().y;
    if (mState == State::Dynamic) {
        if((endHeight) < 0.75){
            if (Velocity()) {
                GetWorld()->DestroyBody(body);
                Kill();
            }
        }
    }

}



void Sparty::Load(b2Vec2 slingshot){
    mState = State::Loading;
    mX = slingshot.x;
    mY = slingshot.y;
}


/**
 * Load the attributes for a sparty node.
 * @param node The Xml node we are loading the sparty from
 */
void Sparty::XmlLoad(wxXmlNode *node)
{
    mX = GetGame()->GetSpartyX();
    mY = GetGame()->GetSpartyY();
    auto type = node->GetName();
    mType = type;
    if (type == L"gruff-sparty") {
        mPicture = make_shared<wxBitmap>(
                L"images/gruff-sparty.png", wxBITMAP_TYPE_ANY);
    }
    if (type == L"helmet-sparty") {
        mPicture = make_shared<wxBitmap>(
                L"images/helmet-sparty.png", wxBITMAP_TYPE_ANY);
    }
}


/**  Test an x,y click location to see if it clicked
* on some item in the game.
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
*/
bool Sparty::HitTest(double x, double y)
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
 * Install physics system within sparty
 * @param physics smart pointer to the physics variable used in the function.
 */
void Sparty::InstallPhysics(std::shared_ptr<Physics> physics)
{
    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_staticBody;

    mSpartyCount = SpartyCount();
    if (SpartyCount() == 1){
        bodyDefinition.position = b2Vec2(mX, mY);
    } else {
        mX = GetGame()->GetSpartyX() + GetGame()->GetSpartySpacing() * (SpartyCount() - 1);
//        GetGame()->GetSpartySpacing()
        bodyDefinition.position = b2Vec2(mX, mY);
    }

    //bodyDefinition.position = b2Vec2(mX, mY);
    bodyDefinition.angle = mAngle * Consts::DtoR;
    mBody = physics->CreateBody(&bodyDefinition);

    // Create the shape
    b2CircleShape circle;

    circle.m_radius = (float)mRadius;

    mBody->CreateFixture(&circle, 0.0f);

}

/**
 * Release sparty from slingshot
 * @param location The location to set
 */

bool Sparty::Release(b2Vec2 location){

    mRelease = location;
    mIfRelease = true;
    return true;
    b2Vec2 mLoadPoint = b2Vec2(-4, 1.16f);
    b2Vec2 toAngry = location - mLoadPoint;
    if (0.1 > toAngry.Length()) {
       auto toAngry = b2Vec2(0.0f, 0.0f);;
    }
}

b2Vec2 Sparty::SlingshotLoad(){
    return mRelease;
};

void Sparty::DynamicMovement2() {
    auto body = GetBody();
    // Get the position and angle before
    // we destroy the body.
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    // Destroy the body in the physics system
    GetWorld()->DestroyBody(body);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_staticBody;
    bodyDefinition.position = b2Vec2(mX, mY);
    bodyDefinition.angle = mAngle * Consts::DtoR;
    mBody = GetWorld()->CreateBody(&bodyDefinition);

    // Create the shape
    b2CircleShape circle;

    circle.m_radius = (float)mRadius;

    mBody->CreateFixture(&circle, 0.0f);



}

/**
 * Control movement of the Sparty
 * @param direction direction sparty is launched
 */
void Sparty::DynamicMovement(b2Vec2 direction)
{
    auto body = GetBody();
    // Get the position and angle before
    // we destroy the body.
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    // Destroy the body in the physics system
    GetWorld()->DestroyBody(body);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = position;
    bodyDefinition.angle = angle;
    bodyDefinition.type = b2_dynamicBody;
    bodyDefinition.angularDamping = 0.9;
    bodyDefinition.linearDamping = 0.1;
    body = GetWorld()->CreateBody(&bodyDefinition);

    // Create the shape
    b2CircleShape circle;
    circle.m_radius = (float)mRadius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = (float)5;
    fixtureDef.friction = 1;
    fixtureDef.restitution = 0.3;

    body->CreateFixture(&fixtureDef);

    if (mType == L"gruff-sparty") {
        velocityFactor = GruffSpartyVelocityFactor;
    }
    if (mType == L"helmet-sparty") {
        velocityFactor = HelmetSpartyVelocityFactor;
    }
    direction *= velocityFactor;
    body->SetLinearVelocity(direction);

    mStateDynamic = true;
    mState = State::Dynamic;

}

