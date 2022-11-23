/**
 * @file Game.h
 * @author Michael Tan, Darshil Patel
 *
 * Main class for game
 *
 * Manages items and levels
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "Image.h"
#include "Item.h"
#include "ScoreBoard.h"
#include "Sparty.h"
#include "Block.h"
#include "Physics.h"
#include <vector>
#include <memory>
#include <b2_math.h>
#include <b2_world.h>
#include <b2_body.h>
#include "Image.h"
#include <map>

class Item;
class b2MouseJoint;

/**
 * Describes a Game object
 */
class Game{
private:

    /// The level state possibilities
    enum class State {Ready, Game, Complete, Fail};

    /// The current level state
    State mState = State::Ready;

    /// count
    double count = 0;

    void ClearObjects();

    /// Scoreboard
    ScoreBoard mScoreBoard;
    /// Single list of items in game
    std::vector<std::shared_ptr<Item>> mItems;
    /// temp vect for sparty
    std::vector<std::shared_ptr<Sparty>> mItemsSparty;
    /// temp vect for Sparty prev
    std::shared_ptr<Sparty> mItemsSpartyPrev = nullptr;
    /// Single list of items in game
    std::vector<std::vector<std::shared_ptr<Item>>> mItemsMain;

    /// Any item we have grabbed and are moving
    std::shared_ptr<Item> mGrabbedItem;
    /// Smart pointer to physics system
    std::shared_ptr<Physics> mPhysics;
    /// Items that are meant to be destroyed
    std::vector<std::shared_ptr<Item>> mKill;
    /// Image Cache
    std::vector<std::pair<std::wstring, std::shared_ptr<Image>>> mImages;
    void XmlItem(wxXmlNode* node, int option);
    /// X of background (width)
    float mX;
    /// Y of background (height)
    float mY;
    /// Size of the playing area in meters
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);
    /// Mouse location
    b2Vec2 mMouseLocation;
    /// Mouse joint for moving things
    b2MouseJoint* mMouseJoint = nullptr;

    void CrossHair(std::shared_ptr<wxGraphicsContext> graphics, const b2Vec2& position);
    /// Indicates the level we are on
    int mLevelNum = 1;
    /// X-axis of offset for drawing
    double mXOffset = 0;
    /// Y-axis of offset for drawing
    double mYOffset = 0;
    /// Helps determine the scale for various measurements
    double mScale = 1;
    /// Size of playing area
    const int Size = 58;
    /// Height of playing area
    const double Height = 35;
    /// number of outer tags
    int mCountOuter = 0;
    /// number of nested tags (items)
    int mCountItems = 0;
    /// number of nested tags (Angry)
    int mAngryCount = 0;
    /// X of sparty (start location)
    double mSpartyX;
    /// Y of sparty (start location)
    double mSpartyY;
    /// Spacing of sparty
    double mSpartySpacing;
    ///LevelMessageWidth
    const int LevelMessageWidth = 60;

    /// Filename wstring for Level0 xml
    const std::wstring Level0 = L"../resources/levels/level0.xml";
    /// Filename wstring for Level1 xml
    const std::wstring Level1 = L"../resources/levels/level1.xml";
    /// Filename wstring for Level2 xml
    const std::wstring Level2 = L"../resources/levels/level2.xml";
    /// Filename wstring for Level3 xml
    const std::wstring Level3 = L"../resources/levels/level3.xml";
    /// Vector for each level filename
    const std::vector<std::wstring> LevelGame = {Level0,Level1,Level2,Level3};

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent& event);
    void Load(int level);
    void Update(double elapsed);

    /**
    * Get the width of the level
    * @return Level width in pixels
    */
    float GetWidth() const { return mX; }

    /**
     * Get the height of the level
     * @return Level height in pixels
     */
    float GetHeight() const { return mY; }

    /**
     * Get the X-axis location of starting sparty
     * @return X-axis coordinate of sparty (double)
     */
    const double GetSpartyX() const { return mSpartyX; }

    /**
     * Get the Y-axis location of starting sparty
     * @return Y-axis coordinate of sparty (double)
     */
    const double GetSpartyY() const { return mSpartyY; }

    /**
     * Get the spacings for starting sparties
     * @return Spacing for each sparty (double)
     */
    const double GetSpartySpacing() const { return mSpartySpacing; }

    /**
    * Getter for block size
    * @return float size of block.
    */
    b2Vec2 GetSize() const { return mSize; }

    /**
    * Get the number of outer tags
    * @return Number of outer tags
    */
    int GetOuterCount () {return  mCountOuter;}

    /**
    * Get the number of items tags
    * @return Number of items tags
    */
    int GetItemsCount () {return  mCountItems;}

    /**
     * Get the number of angry tags
     * @return Number of angry tags
     */
    int GetAngryCount() {return mAngryCount;}

    void Add(std::shared_ptr<Item> item);

    /**
     * Add an image to the game
     * @param filename wstring of image name to add
     */
    void AddImage(const std::wstring& filename);

    void AcceptVisitor(ItemVisitor* visitor);

    /**
     * Set in-game level number
     * @param level number of level to set
     */
    void SetLevel(int level);

    /**
     * Change the state of the game
     */
    void NextLevel();

    /**
     * Playing the game
     */
    std::shared_ptr<Sparty> Playing();

    /**
     * Checks to see if Sparty has been launched
     */
    void Launched();

    /**
     * Get physics for the world
     * @return pointer to b2World object
     */
    b2World* WorldGet() {return mPhysics->GetWorld();}

    /**
     * Get physics for the ground
     * @return pointer to b2Body object
     */
    b2Body* GroundGet() {return mPhysics->GetGround();}

    /// LevelNew
    void LevelNew();
    /// Clear
    void Clear();

    std::shared_ptr<Item> HitTest(double x, double y);

    /**
     * Adds score to scoreboard
     * @param level
     */
    void AddScore(int level);
};

#endif //PROJECT1_GAME_H



