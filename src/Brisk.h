#ifndef BRISK_H
#define BRISK_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Player.h"
#include "Card.h"

class Brisk
{
private:
	int numTurns, numPlayers, currentPlayer, regionsLeft;
	int regionChoice;
	bool succPlace;
	vector<Card>* deck;
	void initDeck(string filename);
public:
	Brisk();
	void beginningClaim(vector<Player> players);
};

#endif // !BRISK_H