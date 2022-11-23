/**
 * @file AngrySparty.h
 * @author Anand Pinnamaneni
 */

#ifndef PROJECT1_ANGRYSPARTY_H
#define PROJECT1_ANGRYSPARTY_H

#include "Game.h"
#include "Item.h"
#include "SlingShot.h"
#include "Sparty.h"

/**
 * Create AngrySparty character for the game.
 */
class AngrySparty : public Item {
private:
public:
    /// Default constructor (disabled)
    AngrySparty() = delete;

    /// Copy constructor (disabled)
    AngrySparty(const AngrySparty &) = delete;

    /// Assignment operator
    void operator=(const AngrySparty &) = delete;

    /**
     * Constructor
     * @param sparty
     */
    AngrySparty(Sparty* sparty);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override {};

    /**  Test an x,y click location to see if it clicked
     * on some item in the game.
     * @param x X location
     * @param y Y location
     * @return bool which determines if we did or didn't click.
     */
    bool HitTest(double x, double y) override;

};

#endif //PROJECT1_ANGRYSPARTY_H
