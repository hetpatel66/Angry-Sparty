/**
 * @file ItemBlock.h
 * @author Darshil Patel
 */

#include <string>
#include <memory>
#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include "b2_shape.h"
#include "Physics.h"
#include "Item.h"
#include "ItemVisitor.h"

#ifndef PROJECT1_ITEMBLOCK_H
#define PROJECT1_ITEMBLOCK_H

/**
 * Main class for implementing blocks in game.
 */
class ItemBlock : public Item{
private:
    /// Default value for friction, restitution, and density
    const double Friction = 0.5;
    /// Default value for restitution
    const double Restitution = 0.5;
    /// Default value for density
    const double Density = 1.0;
    /// The item image
    std::shared_ptr<wxImage> mItemBlockImage;
    /// The item bitmap
    std::shared_ptr<wxBitmap> mItemBlockBitmap;
    /// The physics
    std::shared_ptr<Physics> mPhysics;
    /// Vector of vertices
    std::vector<b2Vec2> mVertices;
    /// Angle of block
    double mAngle;
protected:
    ItemBlock(Game* game, const std::wstring &filename);
    /// Friction of block
    double mFriction = Friction;
    /// Restitution of block
    double mRestitution = Restitution;
    /// Density of block
    double mDensity = Density;
    /// object is static
    bool mStatic = FALSE;
public:
    /// Default constructor
    ItemBlock() = delete;
    /// Copy constructor
    ItemBlock(ItemBlock&) = delete;
    /// Assignment operator
    void operator=(ItemBlock&) = delete;

    virtual ~ItemBlock();

    /**
     * Return Bitmap
     * @return smart pointer to wxBitmap object
     */
    std::shared_ptr<wxBitmap> Bitmap();

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode *node) override;

    /** Determine if block gets hit by something
     * @param x X location
     * @param y Y location
     * @return bool which determines if we did
     * or didn't interact with the block.
     */
    bool HitTest(double x, double y) override;

    /**
    * Install physics system within ItemBlock
    * @param physics smart pointer to the physics variable used in the function.
    */
    void InstallPhysics(std::shared_ptr<Physics> physics) override;

    /**
    * Getter for block angle
    * @return float angle of block.
    */
    float GetAngle() const {return mAngle;}

    /**
    * Getter for block size
    * @return float size of block.
    */
    const b2Vec2& GetSize() const {return mSize;}

    /**
    * Activate size of set
    * @param size size of block.
    */
    void SizeSet(const b2Vec2& size);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override { visitor->VisitItemBlock(this); }

    /// The vector size
    b2Vec2 mSize = {1,1};

};

#endif //PROJECT1_ITEMBLOCK_H
