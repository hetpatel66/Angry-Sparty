/**
 * @file ItemTest.cpp
 * @author Anand Pinnamaneni
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

/// Base filename for the slingshot image
const std::wstring WoodSlingshotBaseName = L"images/slingshot.png";

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, WoodSlingshotBaseName) {}
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    virtual void AcceptVisitor(ItemVisitor* visitor) override { }
    virtual bool HitTest(double x, double y) override;
};

bool ItemMock::HitTest(double x, double y)
{
    return false;
}

// Test getters and setters, ripped from aquarium
TEST(ItemTest, GettersSetters) {
    Game game;
    ItemMock item(&game);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(11.8, 12.4);
    ASSERT_NEAR(11.8, item.GetX(), 0.0001);
    ASSERT_NEAR(12.4, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-42, -17);
    ASSERT_NEAR(-42, item.GetX(), 0.0001);
    ASSERT_NEAR(-17, item.GetY(), 0.0001);
}