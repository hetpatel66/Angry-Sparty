/**
 * @file Block.h
 * @author Het Patel
 *
 * Derived class representing blocks in the game
 *
 * Blocks are used as platforms for foes
 */

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H

#include "Item.h"
#include "ItemBlock.h"
#include "Image.h"
#include <string>
#include <b2_world.h>

/**
 * Describes a single block object
 */
class Block : public ItemBlock {
private:

    /// Default value for friction
    const double Friction = 0.5;
    /// Default value for restitution
    const double Restitution = 0.5;
    /// X of block
    double mX;
    /// Y of block
    double mY;
    /// Width of block
    double mWidth;
    /// Height of block
    double mHeight;
    /// Repeat of block
    double mRepeatX;
    /// Angle of block
    double mAngle;
    /// Friction of block
    double mFriction = Friction;
    /// Restitution of block
    double mRestitution = Restitution;
    /// Type of block
    wxString mType;
    /// Image of block
    wxString mImage;
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
    /// Image for block
    std::shared_ptr<Image> mBlockImage;
    ///Block bit map
    std::shared_ptr<wxBitmap> mBlockBitmap;

public:
    /// Default constructor (disabled)
    Block() = delete;

    /// Copy constructor (disabled)
    Block(const Block &) = delete;

    /// Assignment operator
    void operator=(const Block &) = delete;

    Block(Game *game);

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override {};

    bool HitTest(double x, double y) override;


    void InstallPhysics(std::shared_ptr<Physics> physics) override;

};

#endif //PROJECT1_BLOCK_H
