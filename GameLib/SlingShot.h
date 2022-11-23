/**
 * @file SlingShot.h
 * @author Anand Pinnamaneni
 *
 *
 */

#ifndef PROJECT1_SLINGSHOT_H
#define PROJECT1_SLINGSHOT_H

#include "b2_math.h"
#include "Game.h"
#include "Sparty.h"
#include "Item.h"
#include "Image.h"
#include "ItemVisitor.h"

/**
 * Create slingshot class to launch Spartys.
 */
class SlingShot : public Item{
private:
    /// Size of slingshot
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);
    /// X-axis offset
    double mXOffset = 0;
    /// Y-axis offset
    double mYOffset = 0;
    /// Scale multiplier
    double mScale = 1;
    /// Filename string
    const std::wstring filename = L"images/slingshot.png";
    /// pointer to sparty
    std::shared_ptr<Sparty> mSparty;
    /// The item bitmap
    wxGraphicsBitmap mSlingShotBitmap;
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
    /// Determines where the slingshot is loaded
    b2Vec2 mLoadPoint = b2Vec2(mX, 1.16f);

public:
    /// Default constructor (disabled)
    SlingShot() = delete;

    /// Copy constructor (disabled)
    SlingShot(const SlingShot &) = delete;

    /// Assignment operator
    void operator=(const SlingShot &) = delete;

    /// SlingShot constructor, loads SlingShot into game
    SlingShot(Game *game);

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    bool HitTest(double x, double y) override;

    void Launch();
    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override { visitor->VisitSlingShot(this); }

};

#endif //PROJECT1_SLINGSHOT_H
