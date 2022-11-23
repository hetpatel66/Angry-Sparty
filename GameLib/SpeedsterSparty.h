/**
 * @file SpeedsterSparty.h
 * @author Het Patel
 */

#ifndef PROJECT1_SPEEDSTERSPARTY_H
#define PROJECT1_SPEEDSTERSPARTY_H

#include "Game.h"
#include "Item.h"
#include "SlingShot.h"
#include "Sparty.h"

/**
 * Create SpeedsterSparty character for the game.
 */
class SpeedsterSparty : public Item {
private:
public:
    /// Default constructor (disabled)
    SpeedsterSparty() = delete;

    /// Copy constructor (disabled)
    SpeedsterSparty(const SpeedsterSparty &) = delete;

    /// Assignment operator
    void operator=(const SpeedsterSparty &) = delete;

    SpeedsterSparty(Sparty* sparty);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void AcceptVisitor(ItemVisitor* visitor) override {};


    bool HitTest(double x, double y) override;

};

#endif //PROJECT1_SPEEDSTERSPARTY_H
