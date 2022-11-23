/**
 * @file Foe.h
 * @author Michael Tan, Darshil Patel
 *
 * Main class for foe
 */

#ifndef PROJECT1_FOE_H
#define PROJECT1_FOE_H

#include "b2_math.h"
#include "Item.h"
#include "Image.h"
#include "ItemVisitor.h"
#include "Game.h"
#include "Sparty.h"
#include "Physics.h"

/**
 * Class for the foes
 */
class Foe : public Item{
private:
    /// X of foe
    double mX;
    /// Y of foe
    double mY;
    /// Angle of foe
    double mAngle;
    /// Radius of foe
    double mRadius;
    /// Lower limit of foe
    double mDown;
    /// Type of foe
    wxString mType;
    /// Image of foe
    wxString mImage;
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
    /// Image for foe
    std::shared_ptr<Image> mFoeImage;
    /// Foe bit map
    wxGraphicsBitmap mFoeBitmap;
    /// If ground touched
    bool mGroundTouched = false;
    /// position of foe (X)
    double mPositionX = 0;
    /// position of foe (Y)
    double mPositionY = 0;
    /// Score for the level
    double mScore = 100;

public:
    /// Default constructor (disabled)
    Foe() = delete;

    /// Copy constructor (disabled)
    Foe(const Foe &) = delete;

    /// Destructor
    ~Foe();

    /// Assignment operator
    void operator=(const Foe &) = delete;

    Foe(Game *game);

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override {visitor->VisitFoe(this);}

    //bool HitTest(double x, double y) override;

    void XmlLoad(wxXmlNode* node) override;

    void InstallPhysics(std::shared_ptr<Physics> physics) override;

};

#endif //PROJECT1_FOE_H