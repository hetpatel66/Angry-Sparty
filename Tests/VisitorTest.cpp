/**
 * @file VisitorTest.cpp
 * @author Darshil Patel
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>

#include <ItemVisitor.h>
const std::wstring Level0 = L"../resources/levels/level0.xml";
const std::wstring Level1 = L"../resources/levels/level1.xml";
const std::wstring Level2= L"../resources/levels/level2.xml";
const std::wstring Level3 = L"../resources/levels/level3.xml";
const std::vector<std::wstring> LevelGame = {Level0,Level1,Level2,Level3};

class Visitor : public ItemVisitor {
public:
    int mBackground = 0;
    int mBlock = 0;
    int mSlingShot = 0;
    int mGoalPost = 0;
    int mFoe = 0;
    int mSparty = 0;
    virtual void VisitBackGround(Background* background){mBackground++;}
    virtual void VisitBlock(Block* block){mBlock++;}
    virtual void VisitSlingShot(SlingShot* slingshot){mSlingShot++;}
    virtual void VisitGoalPosts(GoalPosts* goalposts){mGoalPost++;}
    virtual void VisitFoe(Foe* foe){mFoe++;}
    virtual void VisitSparty(Sparty* sparty){mSparty++;}


};

TEST(VisitorTest, test){
    Game game;
    Visitor visitor;
    auto item = &visitor;
    game.AcceptVisitor(item);
    ASSERT_EQ(item->mBackground,0);
    ASSERT_EQ(item->mBlock,0);
    ASSERT_EQ(item->mSlingShot,0);
    ASSERT_EQ(item->mGoalPost,0);
    ASSERT_EQ(item->mFoe,0);
    ASSERT_EQ(item->mSparty,0);

}

TEST(VisitorTest, LevelZero){
    Game game;
    game.Load(0);
    Visitor visitor;
    auto item = &visitor;
    game.AcceptVisitor(item);
    ASSERT_EQ(item->mBackground,0);
    ASSERT_EQ(item->mBlock,0);
    ASSERT_EQ(item->mSlingShot,1);
    ASSERT_EQ(item->mGoalPost,0);
    ASSERT_EQ(item->mFoe,2);
    ASSERT_EQ(item->mSparty,2);
}

TEST(VisitorTest, LevelOne){
    Game game;
    game.Load(1);
    Visitor visitor;
    auto item = &visitor;
    game.AcceptVisitor(item);
    ASSERT_EQ(item->mBackground,0);
    ASSERT_EQ(item->mBlock,0);
    ASSERT_EQ(item->mSlingShot,1);
    ASSERT_EQ(item->mGoalPost,0);
    ASSERT_EQ(item->mFoe,2);
    ASSERT_EQ(item->mSparty,3);
}

TEST(VisitorTest, LevelTwo){
    Game game;
    game.Load(2);
    Visitor visitor;
    auto item = &visitor;
    game.AcceptVisitor(item);
    ASSERT_EQ(item->mBackground,0);
    ASSERT_EQ(item->mBlock,0);
    ASSERT_EQ(item->mSlingShot,0);
    ASSERT_EQ(item->mGoalPost,1);
    ASSERT_EQ(item->mFoe,4);
    ASSERT_EQ(item->mSparty,6);
}

