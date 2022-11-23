/**
 * @file Game.cpp
 * @author Michael Tan, Darshil Patel
 */

#include "pch.h"

#include <b2_mouse_joint.h>
#include <algorithm>

#include "Game.h"
#include "Item.h"
#include "Background.h"
#include "SlingShot.h"
#include "GoalPosts.h"
#include "Poly.h"
#include "ScoreBoard.h"
#include "Block.h"
#include "Foe.h"
#include "Consts.h"
#include "Level.h"
#include "DebugDraw.h"
#include "Sparty.h"
#include "Physics.h"
#include "ItemCounter.h"

using namespace std;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;
/// Number of position update iterations per step
const int PositionIterations = 2;
/// Duration of the Level message
const double Duration = 1.0;

/**
 * Game Constructor
 */
Game::Game()
{

}

/**
 * Handle drawing the game on the screen including all subsystems.
 * @param graphics Graphics context to draw on
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxBrush background(*wxBLACK);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, width, height);
    graphics->PushState();

    // Get the playing area size in centimeters
    b2Vec2 playingAreaSize = mSize; // Get the height and width from every level
    playingAreaSize *= Consts::MtoCM;

    //
    // Automatic Scaling
    // We use CM display units instead of meters
    // because a 1-meter wide line is very wide
    //
    auto scaleX = double(height)/double(playingAreaSize.y);
    auto scaleY = double(width)/double(playingAreaSize.x);
    mScale = scaleX<scaleY ? scaleX : scaleY;
    graphics->Scale(mScale, -mScale);

    // Determine the virtual size in cm
    auto virtualWidth = (double) width/mScale;
    auto virtualHeight = (double) height/mScale;

    // And the offset to the middle of the screen
    mXOffset = virtualWidth/2.0;
    mYOffset = -(virtualHeight-playingAreaSize.y)/2.0-playingAreaSize.y;

    graphics->Translate(mXOffset, mYOffset);

      //
      // From here we are dealing with centimeter pixels
      // and Y up being increase values
      //
    // Draw a box to show the entire playing area
    graphics->SetPen(*wxWHITE_PEN);
    graphics->SetBrush(*wxTRANSPARENT_BRUSH);
    graphics->DrawRectangle(-mSize.x/2 * Consts::MtoCM, 0,
            mSize.x * Consts::MtoCM, mSize.y * Consts::MtoCM);

    // Draw Remaining Items in list
    for (const auto& item : mItems)
    {
        item->Draw(graphics);
    }

    for (const auto& item : mItemsSparty)
    {
        item->Draw(graphics);
    }

    double x = (-mX * Consts::MtoCM/2) + Height;
    double y = (mY * Consts::MtoCM) -Height - Size;
    graphics->PushState();
    mScoreBoard.Draw(graphics, Size, x, y);
    graphics->PopState();

    //
    // Debug draw the Box2D world so we can see what is going on
    //
    DebugDraw debugDraw(graphics);
    debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
    WorldGet()->SetDebugDraw(&debugDraw);
    WorldGet()->DebugDraw();

    if (mState != State::Game){
        std::wstring print = L"";
        if (mState==State::Ready){
            print = L"Level " +to_string(mLevelNum) + " Begin";
        }
        else if (mState==State::Complete){
            print = L"Level Complete!";
        }
        else if (mState==State::Fail){
            print = L"Level Fail!";
        }
        graphics->SetFont(wxFont(LevelMessageWidth,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD
        ),wxColour(0,0,255));
        graphics->PushState();
        graphics->Scale(1,-1);
        graphics->SetPen(wxColour(0,0,255));
        graphics->DrawText(print,-255,-450);
        graphics->PopState();
    }
    //
    // Draw a crosshair where the mouse is located
    //
    CrossHair(graphics, mMouseLocation);

    graphics->PopState();
}

/**
 * Display a crosshair.
 * @param graphics Graphics context to display on
 * @param position Where to display in meters
 */
void Game::CrossHair(std::shared_ptr<wxGraphicsContext> graphics, const b2Vec2& position)
{
    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    double wid = 10;
    graphics->SetPen(*wxRED_PEN);
    graphics->StrokeLine(x-wid, y, x+wid, y);
    graphics->StrokeLine(x, y-wid, x, y+wid);
}

/**
 * Handle the mouse move event
 * @param event Mouse event
 */
void Game::OnMouseMove(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if(event.LeftIsDown())
        {
            if(mMouseJoint != nullptr)
            {
                mMouseJoint->SetTarget(b2Vec2(x, y));
            }
            else {
                mGrabbedItem->SetTransform(b2Vec2(x, y), 2);
            }
        }
        else
        {
            auto hit_temp = mGrabbedItem->Release(b2Vec2(x, y));
            ItemCounter visitor;
            AcceptVisitor(&visitor);

            // When the left button is released, we release the
            // item.
            if(mMouseJoint != nullptr)
            {
                WorldGet()->DestroyJoint(mMouseJoint);
                mMouseJoint = nullptr;
            }
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 * @param option determines which version is called
 */
void Game::XmlItem(wxXmlNode *node, int option)
{
    if (option == 1)
    {
        // A pointer for the item we are loading
        shared_ptr<Item> item;

        // We have an item. What type?
        auto child = node->GetChildren();
        for (; child; child = child->GetNext()) {
            mCountItems += 1;
            auto type = child->GetName();
            if (type == L"slingshot") {
                item = make_shared<SlingShot>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
            if (type == L"goalposts") {
                item = make_shared<GoalPosts>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
            if (type == L"block") {
                item = make_shared<Block>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
            if (type == L"poly") {
                item = make_shared<Poly>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
            if (type == L"foe") {
                item = make_shared<Foe>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
            if (type == L"background") {
                item = make_shared<Background>(this);
                mItems.push_back(item);
                item->XmlLoad(child);
                continue;
            }
        }
    }
    if (option == 2)
    {
        mAngryCount = 0;
        // A pointer for the item we are loading
        shared_ptr<Item> item;
        shared_ptr<Sparty> itemSparty;
        node->GetAttribute(L"x", L"0").ToDouble(&mSpartyX);
        node->GetAttribute(L"y", L"0").ToDouble(&mSpartyY);
        node->GetAttribute(L"spacing", L"0.6").ToDouble(&mSpartySpacing);
        // We have an item. What type?
        auto child = node->GetChildren();
        for (; child; child = child->GetNext()) {
            mAngryCount += 1;
            item = make_shared<Sparty>(this);
            itemSparty = make_shared<Sparty>(this);
            mItemsSparty.push_back(itemSparty);
            itemSparty->XmlLoad(child);
            itemSparty->SetSpartyCount(mAngryCount);
        }
    }
}

/**
 * Load the game XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param level The number of the level to load the game from.
 */
void Game::Load(int level)
{
    mLevelNum = level % LevelGame.size();
    const wstring filename = LevelGame[mLevelNum];
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }
    Clear();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    double tempX = 0;
    root->GetAttribute(L"width", L"0").ToDouble(&tempX);
    mX = tempX;
    double tempY = 0;
    root->GetAttribute(L"height", L"0").ToDouble(&tempY);
    mY = tempY;
    mSize.x = mX;
    mSize.y = mY;
    for( ; child; child=child->GetNext())
    {
        mCountOuter += 1;
        auto name = child->GetName();
        if(name == L"items")
        {
            XmlItem(child, 1);
        }
        if(name == L"angry")
        {
            XmlItem(child, 2);
        }
    }
    mPhysics = std::make_shared<Physics>(mSize);

    // Install in every item
    for(auto item: mItems)
    {
        item->InstallPhysics(mPhysics);
    }
    for(auto item: mItemsSparty)
    {
        item->InstallPhysics(mPhysics);
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    if (count < Duration){
        count += elapsed;
    }
    else{
        switch (mState) {
        case State::Game: {
            WorldGet()->Step(elapsed, VelocityIterations, PositionIterations);
//            Playing();
            ClearObjects();
            NextLevel();
            break;
        }
        case State::Ready:{
            mState = State::Game;
            break;
        }
        case State::Complete:{
            mState = State::Ready;
            mScoreBoard.UpdateTotalScore();
            if (mLevelNum == 3){
                Load(3);
            } else {
                Load(mLevelNum+1);
            }
            break;
        }
        case State::Fail:{
            mState = State::Ready;
            Load(mLevelNum);
            break;
        }
        default:
            break;
        }
    }
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Accept the ItemVisitor
 * @param visitor Our ItemVisitor
 */
void Game::AcceptVisitor(ItemVisitor* visitor)
{
    for (auto item: mItems)
    {
        item->AcceptVisitor(visitor);
    }
    for (auto item: mItemsSparty)
    {
        item->AcceptVisitor(visitor);
    }
}


void Game::LevelNew()
{
}

void Game::Clear()
{
    mItems.clear();
    mItemsSparty.clear();
    mState = State::Ready;
    mScoreBoard.LevelScore(0);
    count = 0;
}

/**  Test an x,y location to get the first item in
* game that passes a hit test.
* @param x X location
* @param y Y location
* @return smart pointer to the item that passes.
* returns nullptr if none of them pass.
*/
std::shared_ptr<Item> Game::HitTest(double x, double y)
{
    for(auto item: mItems)
    {
        if(item->HitTest(x, y))
        {
            return item;
        }
    }

    for(auto item: mItemsSparty)
    {
        if(item->HitTest(x, y))
        {
            return item;
        }
    }
    return nullptr;
}

/**
 * Key press event
 * @param event Key press event
 */
void Game::OnKeyDown(wxKeyEvent& event)
{
}

/**
 * Key release event
 * @param event Key release event
 */
void Game::OnKeyUp(wxKeyEvent& event)
{
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void Game::OnLeftDown(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    mGrabbedItem = HitTest(x, y);

    if (mGrabbedItem != nullptr)
    {
        auto targetBody = mGrabbedItem->GetBody();
        if(targetBody->GetType() == b2_dynamicBody)
        {
            //
            // Create a mouse joint object we can use
            // to drag items around
            //
            // Only works for dynamic bodies
            //
            b2MouseJointDef jointDef;
            jointDef.bodyA = GroundGet();
            jointDef.bodyB = targetBody;
            jointDef.maxForce = 10000 * targetBody->GetMass();
            jointDef.stiffness = 10000 * targetBody->GetMass();
            jointDef.damping = 125;
            jointDef.target = b2Vec2(x, y);

            mMouseJoint = (b2MouseJoint*)WorldGet()->CreateJoint(&jointDef);
            mMouseJoint->SetTarget(b2Vec2(x, y));
        }
    }
}

/**
 * Clear the Sparty and Foe
 */
void Game::ClearObjects()
{
    for (auto item : mItems){
        if (item->Clear()){
            mKill.push_back(item);
        }
    }
    for (auto item: mKill){
        auto kill = find(mItems.begin(),mItems.end(),item);
        if(kill != mItems.end()){
            mItems.erase(kill);
        }
    }
}

void Game::NextLevel()
{
    Level visitor;
    AcceptVisitor(&visitor);
    if(visitor.Sparty()){
        count = 0;
        mState = State::Fail;
    }
    if(visitor.Foe()){
        count = 0;
        mState = State::Complete;
    }
}

std::shared_ptr<Sparty> Game::Playing()
{
    if(mItemsSparty.size() != 0){
        return mItemsSparty[0];
    }
    return mItemsSpartyPrev;
}

void Game::Launched()
{
    if(mItemsSparty.size() != 0){
        mItemsSpartyPrev = mItemsSparty[0];
        mItemsSparty.erase(mItemsSparty.begin());
    }
}

void Game::AddScore(int score)
{
    mScoreBoard.NewLevel(score);
}