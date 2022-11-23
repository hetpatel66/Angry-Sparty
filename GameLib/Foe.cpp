/**
 * @file Foe.cpp
 * @author Michael Tan, Darshil Patel
 */

#include "pch.h"
#include <string>
#include "Foe.h"
#include <b2_fixture.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>

using namespace std;

/// Foe filename
const wstring FoeImageName1 = L"images/foeM.png"; // put the file name of the Foe (.png)

/**
 * Constructor
 * @param game The game this item is a member of
 */
Foe::Foe(Game *game) : Item(game, FoeImageName1)
{
}

/**
 * Destructor
 */
Foe::~Foe()
{

}

/**
 * Draw the foes for the game
 * @param graphics The device context to draw on
 */
void Foe::Draw(const std::shared_ptr<wxGraphicsContext> graphics) {

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
    if(Velocity()){
        if((endHeight) < mDown){
            GetWorld()->DestroyBody(body);
            Kill();
            GetGame()->AddScore(mScore);
        }
    }
}

/**
 * Load the attributes for a foe node.
 * @param node The Xml node we are loading the item from
 */
void Foe::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);
    mImage = node->GetAttribute(L"image", L"").ToStdWstring();

    mImage.ToStdString();

    mImage = "images/" + mImage;

    mPicture = make_shared<wxBitmap>(
            mImage, wxBITMAP_TYPE_ANY);
}

/**
 * Install physics system within foe
 * @param physics smart pointer to the physics variable used in the function.
 */
void Foe::InstallPhysics(std::shared_ptr<Physics> physics)
{

    b2World* world = physics->GetWorld();

    b2PolygonShape poly;


    const int NumVertices = 8;
    float diag_octa = 0.707107 * mRadius;
    float straight_octa = mRadius;
    const b2Vec2 vertices[8] = {
            {straight_octa, 0},
            {diag_octa,	diag_octa},
            {0,	straight_octa},
            {-diag_octa,	diag_octa},
            {-straight_octa,	0},
            {-diag_octa,	-diag_octa},
            {0,	-straight_octa},
            {diag_octa,-diag_octa},
    };
    poly.Set(vertices, NumVertices);
    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_dynamicBody;
    bodyDefinition.position = b2Vec2(mX, mY);
    bodyDefinition.angle = mAngle * Consts::DtoR;
    mBody = world->CreateBody(&bodyDefinition);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = (float)1.0f;
    fixtureDef.friction = (float)0.5f;
    fixtureDef.restitution = (float)0.5f;

    mBody->CreateFixture(&fixtureDef);

}
