/**
 * @file ScoreBoard.h
 * @author Elio Moussa, Het Patel
 *
 * Keeps track of the score of each level and the total score
 *
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H


/**
 * Main class for Score implementation
 */
class ScoreBoard {
private:
    /// Total score that will be displayed on the left side
    int mTotalScore = 0;
    /// Level score that will be displayed on the right side
    int mLevelScore = 0;
    /// X location to draw the level score
    double mLevelScoreX = 0;
    /// Y location to draw the level score
    double mLevelScoreY = -900;
    /// X location to draw the total score
    double mTotalScoreX = 0;
    /// Y location to draw the total score
    double mTotalScoreY = -900;


public:

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int size, double x, double y);

    void UpdateTotalScore();

    /** New Level score
     * @param value int of level to be loaded
     */
    void NewLevel(int value);


    /** Level score
     * @param value int of value to be added
     */
    void LevelScore(int value);

    /** Total score
     * @param value int of value to be added
     */
    void TotalScore(int value);

};

#endif //PROJECT1_SCOREBOARD_H
