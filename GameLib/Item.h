/**
 * @file Item.h
 * @author Het Patel, Darshil Patel, Michael Tan
 *
 * Class representing an item object
 *
 * Represents an item in the game
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <string>
#include <memory>
#include "b2_shape.h"
#include "Physics.h"

class Game;
//class Physics;
class b2Fixture;
class b2World;
class ItemVisitor;
class b2Body;
class b2Shape;

/**
 * Base class for all items in game
 */
class Item {
private:
    /// The level this item is contained in
    int  mLevel;
    /// The game this item is contained in
    Game *mGame;
    /// Width of item
    double mWidth  = 0;
    /// Height of item
    double mHeight = 0;
    /// Item filename
    std::wstring mFilename;
    /// The item image
    std::shared_ptr<wxImage> mItemImage;
    /// The item bitmap
    wxGraphicsBitmap mItemBitmap;
    /// ()
    int firstSparty = 0;
    /// position of vector
    b2Vec2 mPosition = {0,0};
    /// kill everything
    bool mKill = false;

protected:
    /// The physics system body
    b2Body *mBody = nullptr;

public:
    /// X location of item
    double  mX = 0;
    /// Y location of item
    double  mY = 0;

    Item();
    Item(Game* game, const std::wstring &filename);

    /**
     * Get the game that item is in
     * @return pointer to said Game
     */
    auto GetGame() {return mGame;}



    virtual ~Item();

    /**
     * The X location of the item
     * @return X location in pixels
     */
    virtual double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    virtual double GetY() const { return mY; }

    /**
     * The specific item's filename
     * @return empty wstring
     */
    virtual std::wstring GetFilename() const { return mFilename; }

    /**
     * Set item image variable
     * @param itemImage smart pointer to wxImage
     */
    virtual void SetImage(const std::shared_ptr<wxImage>& itemImage) { mItemImage = itemImage; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    double DistanceTo(const std::shared_ptr<Item>& item) const;
    virtual void Draw(const std::shared_ptr<wxGraphicsContext> graphics);
    virtual void XmlLoad(wxXmlNode *node);
    b2Fixture* CreateFixture(b2Shape* shape, float density);
    virtual void InstallPhysics(std::shared_ptr<Physics> physics);
    virtual bool HitTest(double x, double y);
    virtual bool Release(b2Vec2);
//    virtual bool Load(int);

    /**
     * Get the underlying Box2D body object if there is any
     * @return b2Body object or nullptr if none
     */
    b2Body* GetBody() {return mBody;}

    b2World* GetWorld();

    void SetTransform(const b2Vec2& location, double angle);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update in seconds
     */
    void Update(double elapsed) {}

    /**
     * Set amount for firstSparty
     * @param ques
     */
    void SetSpartyCount(int ques) {firstSparty = ques;}

    /**
     * Return firstSparty
     * @return int
     */
    int SpartyCount() const {return firstSparty;}

    /**
     * Accept a visitor 
     * @param visitor The visitor we accept
     */
    virtual void AcceptVisitor(ItemVisitor* visitor) {};

    /**
     * Vector item position
     * @return X and Y position of the item
     */
    const b2Vec2& GetPosition() const {return mPosition;}

    /**
     * set the location of the item
     * @param x x location
     * @param y y location
     */
    void GetLocation(float x, float y) {mPosition = {x,y};}

    /**
     * Kill function
     */
    void Kill();

    /**
     * clear everything
     * @return return boolean
     */
    bool Clear() {return mKill;}

    /**
     * velocity check to see if its true or false
     */
    bool Velocity();

};

#endif //PROJECT1_ITEM_H
