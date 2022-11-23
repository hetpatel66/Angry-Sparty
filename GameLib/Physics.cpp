/**
 * @file Physics.cpp
 * @author Michael Tan
 */

#include "pch.h"
#include "Physics.h"
#include <b2_body.h>
#include <b2_polygon_shape.h>

/**
 * Constructor
 * @param size The size of the level in meters
 */
Physics::Physics(const b2Vec2& size) : mWorld(b2Vec2(0.0f, Gravity))
{
    // Create a ground body at 0,0 to use as a reference
    b2BodyDef bodyDefinition;
    bodyDefinition.position.Set(0, 0.1);
    bodyDefinition.type = b2_staticBody;
    mGround = mWorld.CreateBody(&bodyDefinition);

    // Bottom
    b2PolygonShape box;
    box.SetAsBox(size.x*2, 0.1);
    mGround->CreateFixture(&box, 0.0f);

    // Right side
    box.SetAsBox(0.1, size.y, b2Vec2(size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);

    // Left side
    box.SetAsBox(0.1, size.y, b2Vec2(-size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);
}

/**
 * Create a body for the physics class
 * @param p_def used to create a body in mWorld
 * @return pointer to b2Body object
 */
b2Body* Physics::CreateBody(b2BodyDef* p_def)
{
    auto temp = mWorld.CreateBody(p_def);
    return temp;
}