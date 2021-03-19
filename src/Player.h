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

public:
	Player(int numPlayers);
	int getTotalArmySize();
	void updateArmySize(int size);
	vector<Region> getOwnedRegions();
	void updateOwnedRegions(vector<Region> regions);
	vector<Card> getHand();
	void drawCard(vector<Card>* deck);
	void removeCard(Card card);
};

