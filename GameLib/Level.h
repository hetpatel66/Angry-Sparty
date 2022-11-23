/**
 * @file Level.h
 * @author Elio Moussa
 *
 * Main Level class that supports the three levels of the Game
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H

#include "ItemVisitor.h"

/**
 * Main class for Level implementation
 */
class Level : public ItemVisitor{
private:

    std::shared_ptr<wxBitmap> mLevel;   ///< Level image to use `
    /// Is there a sparty in the level?
    bool mSparty = true;
    /// Is there a foe in the level?
    bool mFoe = true;

public:
    /**
     * Visit sparty to determine if it's in the level
     * @param sparty Pointer to a sparty
     */
    void VisitSparty(Sparty* sparty){mSparty = false;}

    /**
     * Visit foe to determine if it's in the level
     * @param foe Pointer to a foe
     */
    void VisitFoe(Foe* foe){mFoe = false;}

    /**
     * Is there a sparty in the level?
     * @return bool that answers the question
     */
    bool Sparty(){return mSparty;}

    /**
     * Is there a foe in the level?
     * @return bool that answers the question
     */
    bool Foe() {return mFoe;}

    /**
    * Get the width of the level
    * @return Level width in pixels
    */
    int GetWidth() const { return mLevel->GetWidth(); }

    /**
     * Get the height of the level
     * @return Level height in pixels
     */
    int GetHeight() const { return mLevel->GetHeight(); }

};

#endif //PROJECT1_LEVEL_H
