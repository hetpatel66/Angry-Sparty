/**
 * @file ItemCounter.h
 * @author Michael Tan
 * Visitor class to count number of items
 */

#include "ItemVisitor.h"
#include "SlingShot.h"
#include "GoalPosts.h"

#ifndef PROJECT1_ITEMCOUNTER_H
#define PROJECT1_ITEMCOUNTER_H

/**
 * The visitor for the launch
 */
class ItemCounter : public ItemVisitor {
public:

    /**
     * Visit slingshot to launch
     * @param slingshot Pointer to a slingshot
     */
    void VisitSlingShot(SlingShot* slingshot){slingshot->Launch();}
    /**
     * Visit goalpost to launch
     * @param goalpost Pointer to a goalpost
     */
    void VisitGoalPosts(GoalPosts* goalpost){goalpost->Launch();}

};


#endif //PROJECT1_ITEMCOUNTER_H
