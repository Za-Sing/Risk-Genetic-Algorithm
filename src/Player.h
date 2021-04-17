#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include "Region.h"
#include <vector>
#include "Card.h"
#include "GeneticAlgorithm.h"
using namespace std;


class Player
{
private:
	int numTroops;
	vector<Region> ownedRegions;
	vector<Card> hand;
	GeneticAlgorithm* ga = NULL;
	bool defeated = false;

public:
	Player(int numPlayers, bool isBot);
	int getTotalArmySize();
	void updateArmySize(int size);
	vector<Region> getOwnedRegions();
	void updateOwnedRegions(vector<Region> regions);
	vector<Card> getHand();
	void drawCard(vector<Card>* deck);
	void playCards(vector<Card>* deck, vector<int> returnedCards);
	void setDefeated(bool isDefeated);
	bool getDefeated();
};

#endif // !PLAYER_H