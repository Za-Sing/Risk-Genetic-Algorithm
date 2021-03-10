#pragma once

#include <vector>
#include "Card.h"
#include "Region.h"
using namespace std;


class Player
{
private:
	int numTroops;
	vector<Region> ownedRegions;
	vector<Card> hand;
};

