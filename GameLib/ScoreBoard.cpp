/**
 * @file ScoreBoard.cpp
 * @author Elio Moussa, Het Patel
 */

#include "pch.h"
#include <wx/graphics.h>
#include "ScoreBoard.h"
#include "Consts.h"


/**
 * Adds level score to total score and sets level score to 0
 */
void ScoreBoard::UpdateTotalScore()
{
    mTotalScore += mLevelScore;
    mLevelScore = 0;
}

/**
 * Draw the scoreboard on the Game View
 * @param graphics graphics context to draw with
 * @param size size of the scoreboard in int
 * @param x x-axis number
 * @param y y-axis number
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, int size, double x, double y)
{
    graphics->SetFont(wxFont(size,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD), wxColour(255,0,0));

    graphics->DrawText(std::to_string(mLevelScore), x, y);
    graphics->DrawText(std::to_string(mTotalScore),-x - size, y);
}

void ScoreBoard::LevelScore(int value)
{
    mLevelScore = value;
}

void ScoreBoard::NewLevel(int value)
{
    mLevelScore += value;
}

