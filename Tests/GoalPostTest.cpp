/**
 * @file GoalPostTest.cpp
 * @author Darshil Patel
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <GoalPosts.h>

TEST(Goalpost, HitTest)
{
    // Create a game to test
    Game game;
    GoalPosts goalpost(&game);

    goalpost.SetLocation(100, 200);

    // Center of the goalpost should be a true
//    ASSERT_TRUE(goalpost.HitTest(100, 200));

    // Left of the goalpost
    ASSERT_FALSE(goalpost.HitTest(10, 200));

    // Right of the goalpost
    ASSERT_FALSE(goalpost.HitTest(200, 200));

    // Above the goalpost
    ASSERT_FALSE(goalpost.HitTest(100, 0));

    // Below the goalpost
    ASSERT_FALSE(goalpost.HitTest(0, 0));
}