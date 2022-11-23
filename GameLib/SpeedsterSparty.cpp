/**
 * @file SpeedsterSparty.cpp
 * @author Het Patel
 */

#include "pch.h"
#include "SpeedsterSparty.h"
#include "Item.h"
#include <b2_fixture.h>

using namespace std;

/// Sparty filename
const wstring SpartyImageName = L"gruff-sparty.png"; // put the file name of the sparty (.png)

/**
 * Constructor
 * @param sparty pointer to sparty class we derive from
 */
SpeedsterSparty::SpeedsterSparty(Sparty *sparty) : Item()
{
}

/**
 * Test an x,y to see if SpeedsterSparty is hit
* @param x X location
* @param y Y location
* @return bool which determines if we did or didn't click.
*/
bool SpeedsterSparty::HitTest(double x, double y)
{
    auto fixture = GetBody()->GetFixtureList();
    for( ; fixture != nullptr; fixture = fixture->GetNext())
    {
        if(fixture->TestPoint(b2Vec2(x, y)))
        {
            return true;
        }
    }

    return false;
}