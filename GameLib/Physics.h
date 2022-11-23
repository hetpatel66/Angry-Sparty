/**
 * @file Physics.h
 * @author Michael Tan
 */

#ifndef PROJECT1_PHYSICS_H
#define PROJECT1_PHYSICS_H

#include <b2_world.h>
#include <b2_body.h>

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/**
 * Implements the in-game physics.
 */
class Physics {
private:
    /// The box2d world
    b2World mWorld;
    /// A ground reference object
    b2Body* mGround;

public:
    Physics(const b2Vec2& size);
    Physics();

    /**
     * Create a Box2D Body object
     * @return pointer to b2Body object
     */
    b2Body* CreateBody(b2BodyDef* p_def);

    /**
     * Get the Box2D World object
     * @return b2World object
     */
    b2World *GetWorld() {return &mWorld;}

    /**
     * Get the Box2D Ground object
     * @return b2Body object
     */
    b2Body *GetGround() {return mGround;}
};

#endif //PROJECT1_PHYSICS_H
