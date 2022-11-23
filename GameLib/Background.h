/**
 * @file Background.h
 * @author Het Patel
 *
 * Background base class
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H

#include "Item.h"
#include "Image.h"
#include <string>

/**
 * Background base class
 */
class Background : public Item {
private:
    /// Image of block
    wxString mImage;

    /// image to use
    std::shared_ptr<wxBitmap> mPicture;

    /// Width of block
    double mWidth;

    /// Height of block
    double mHeight;

public:
    Background(Game *game);

    /// Default constructor (disabled)
    Background() = delete;

    /// Copy constructor (disabled)
    Background(const Background &) = delete;

    /// Assignment operator
    void operator=(const Background &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override {};

    bool HitTest(double x, double y) override;

};

#endif //PROJECT1_BACKGROUND_H
