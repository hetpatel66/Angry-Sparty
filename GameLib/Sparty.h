/**
 * @file Sparty.h
 * @author Michael Tan
 *
 * Main class for sparty
 */

#ifndef PROJECT1_SPARTY_H
#define PROJECT1_SPARTY_H

#include <memory>
#include <b2_world.h>
#include "Item.h"
#include "Consts.h"
#include "Physics.h"
#include "ItemVisitor.h"

class Game;

/**
 * Main class for sparty implementation
 */
class Sparty : public Item {
private:
    /// The sparty state possibilities
    enum class State {Static,Loading,Dynamic};
    /// The current sparty state
    State mState = State::Static;

    bool mStateDynamic = false;
    /// X of sparty
    double mX;
    /// Y of sparty
    double mY;
    /// X of sparty sling
    float mXsling;
    /// Y of sparty sling
    float mYsling;
    /// Counter of sparty
    int mSpartyCount;
    /// type of sparty
    wxString mType;
    /// velocity factor of sparty
    float velocityFactor = 12.0;
    /// Angle of sparty
    double mSpacing;
    /// Lower limit of sparty
    double mDown;
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
    /// Image of sparty
    wxString mImage;
    /// x position of sparty
    double mPositionX = 0;
    /// y position of sparty
    double mPositionY = 0;
    /// angle of the sparty
    double mAngle = 0;
    /// radius of sparty
    double mRadius = .25;
    /// Item filename
    std::wstring mFilename;
    /// The sparty image
    std::shared_ptr<wxImage> mSpartyImage;
    /// The sparty bitmap
    wxGraphicsBitmap mSpartyBitmap;
    /// The physics
    std::shared_ptr<Physics> mPhysics;

    /// The physics system body
    b2Vec2 mRelease;

    int firstSparty = 0;
    // Check if released
    bool mIfRelease = false;


protected:

public:
    Sparty(Game *game);
    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty &) = delete;
    /// Getter for mIfRelease

    bool GetIfReleased() const {return mIfRelease;}
    ///Getter for mState
    bool GetState() const {return mStateDynamic;}

    /// Assignment operator
    void operator=(const Sparty &) = delete;

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    bool Release(b2Vec2 location) override;

    /**
     * Get the location of the slingshot
     * @return pointer to sparty
     */
    Sparty* SlingshotLocation(b2Vec2 );


    bool HitTest(double x, double y) override;

    void InstallPhysics(std::shared_ptr<Physics> physics) override;
    /// Accept a visitor
    void DynamicMovement(b2Vec2 direction);
    void DynamicMovement2();

    /**
     * Load sparty onto slingshot
     * @return b2Vec2 variable
     */
    b2Vec2 SlingshotLoad();
    /// load sparty onto slingshot

    void Load(b2Vec2 slingshot);


    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

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
};


#endif //PROJECT1_SPARTY_H
