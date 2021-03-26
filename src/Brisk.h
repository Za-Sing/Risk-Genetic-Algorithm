#ifndef BRISK_H
#define BRISK_H

//#include "Player.h"
#include "Region.h"
#include <string>
#include <vector>

using namespace std;
class Brisk
{
private:
	int numTurns, numPlayers, currentPlayer, regionsLeft;
	string regionChoice;
public:
	vector<Region> board;
	Brisk();
	//void beginningClaim(vector<Player> players);
};

#endif // !BRISK_H