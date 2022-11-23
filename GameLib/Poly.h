/**
 * @file Poly.h
 * @author Het Patel
 * Used for Sparty, AngrySparty, and Foe
 */

#ifndef PROJECT1_POLY_H
#define PROJECT1_POLY_H

#include <b2_world.h>
#include "Game.h"
#include <string>
#include "ItemVisitor.h"
#include "Physics.h"
#include "ItemBlock.h"

/**
 * Describes a single Poly object that is shaped like a polygon
 */
class Poly : public ItemBlock{
private:
    /// X of poly
    double mX;
    /// Y of poly
    double mY;
    /// Angle of poly
    double mAngle;
    /// Position of poly
    double mPosition;
    /// Vertices
    std::vector<b2Vec2> mVertices;
    /// Image of poly
    wxString mImage;
    /// image to use
    std::shared_ptr<wxBitmap> mPicture;
public:
    /// Default constructor (disabled)
    Poly() = delete;
    /// Copy constructor (disabled)
    Poly(const Poly &) = delete;
    /// Assignment operator
    void operator=(const Poly &) = delete;
    Poly(Game *game);

    void Draw(const std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    bool HitTest(double x, double y) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override { visitor->VisitPoly(this); }

    void InstallPhysics(std::shared_ptr<Physics> physics) override;

};

#endif //PROJECT1_POLY_H
