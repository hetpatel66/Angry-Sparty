/**
 * @file ItemVisitor.h
 * @author Darshil Patel
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class AngrySparty;
class Sparty;
class Foe;
class SlingShot;
class Block;
class Poly;
class Background;
class GoalPosts;
class ScoreBoard;
class ItemBlock;

/**
 * visitor for the angry sparty game
 */
class ItemVisitor {
private:

public:
    virtual ~ItemVisitor() {}

    /**
     * visit a sparty object
     * @param sparty
     */
    virtual void VisitSparty(Sparty * sparty){}

    /**
     * visit a angry sparty object
     * @param angry_sparty
     */
    virtual void VisitAngrySparty(AngrySparty* angry_sparty){}

    /**
     * visit a foe object
     * @param foe
     */
    virtual void VisitFoe(Foe* foe){}

    /**
     * visit a block object
     * @param block
     */
    virtual void VisitBlock(Block* block){}

    /**
     * visit a slingshot object
     * @param slingshot
     */
    virtual void VisitSlingShot(SlingShot* slingshot){}

    /**
     * visit a poly object
     * @param poly
     */
    virtual void VisitPoly(Poly* poly){}

    /**
     * visit a background object
     * @param background
     */
    virtual void VisitBackGround(Background* background){}

    /**
     * visit a goalpost object
     * @param goalpost
     */
    virtual void VisitGoalPosts(GoalPosts* goalpost){}

    /**
     * visit an item block object
     * @param itemBlock
     */
    virtual void VisitItemBlock(ItemBlock* itemBlock){}

};

#endif //PROJECT1_ITEMVISITOR_H
