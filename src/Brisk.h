#ifndef BRISK_H
#define BRISK_H

#include "Player.h"
#include <string>

class Brisk
{
private:
	int numTurns, numPlayers, currentPlayer, regionsLeft;
	string regionChoice;
public:
	Brisk();
	void beginningClaim(vector<Player> players);
};

#endif // !BRISK_H