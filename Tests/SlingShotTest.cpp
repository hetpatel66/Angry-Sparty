/**
 * @file SlingShotTest.cpp
 * @author Darshil Patel
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <SlingShot.h>

TEST(Slingshot, HitTest)
{
    // Create a game to test
    Game game;
    SlingShot slingshot(&game);

    slingshot.SetLocation(100, 200);

    // Left of the slingshot
    ASSERT_FALSE(slingshot.HitTest(10, 200));

    // Right of the slingshot
    ASSERT_FALSE(slingshot.HitTest(200, 200));

    // Above the slingshot
    ASSERT_FALSE(slingshot.HitTest(100, 0));

    // Below the slingshot
    ASSERT_FALSE(slingshot.HitTest(0, 0));
}