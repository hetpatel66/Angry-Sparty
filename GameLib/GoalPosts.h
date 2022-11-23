/**
 * @file GoalPosts.h
 * @author Darshil Patel
 *
 *
 */

#ifndef PROJECT1_GOALPOSTS_H
#define PROJECT1_GOALPOSTS_H


#include "b2_math.h"
#include "Game.h"
#include "Sparty.h"
#include "Item.h"
#include "Image.h"
#include "ItemVisitor.h"

/**
 * Class for the goalposts
 */
class GoalPosts : public Item{
private:
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
    /// Size of slingshot
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);
    /// X-axis offset
    double mXOffset = 0;
    /// Y-axis offset
    double mYOffset = 0;
    /// Scale multiplier
    double mScale = 1;
    /// Filename string
    const std::wstring filename = L"images/goalposts.png";
    /**
     * sparty
     */
    std::shared_ptr<Sparty> mSparty;
    /// Determines where the slingshot is loaded
    b2Vec2 mLoadPoint = b2Vec2(mX, 2.31f);

public:
    /// Default constructor (disabled)
    GoalPosts() = delete;
    /// Copy constructor (disabled)
    GoalPosts(const GoalPosts &) = delete;
    /// Assignment operator
    void operator=(const GoalPosts &) = delete;
    /// SlingShot constructor, loads SlingShot into game
    GoalPosts(Game *game);

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    bool HitTest(double x, double y) override;

    void Launch();

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override { visitor->VisitGoalPosts(this); }
};

#endif //PROJECT1_GOALPOSTS_H
