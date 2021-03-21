/*
* Brisk is for encapsulating the main game loop. In it, there is the initial pre-game setup for territory claiming
* and reinforcing. It is also used for accessing game data at will, and for updating the status of the game.
*/
#include "Brisk.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Brisk::Brisk()
{

}

void Brisk::beginningClaim(vector<Player> players) {

	numPlayers = players.size();

	//find number of turns total after regions are chosen
	switch (numPlayers)
	{
	case 2: numTurns = 40; break;
	case 3: numTurns = 35; break;
	case 4: numTurns = 30; break;
	case 5: numTurns = 25; break;
	}

	regionsLeft = 42;

	//claim new territories until territories gone

	//go for the number of regions left to choose from
	for (int i = 0; i < numTurns; i-=-1) {
		//cycle through players
		currentPlayer = (i % numPlayers);

		//if empty regions exist
		if (regionsLeft != 0) {
			//print and take player's region choice
			printf("Player %s, please choose next region to occupy.\n", to_string(currentPlayer + 1));
			cin >> regionChoice;

			// TODO: once region is implemented, update each region to be owned by the player that chooses it
			// make sure the region is removed from the selectable pool of regions

			//remove troop from player's troop count
			players[currentPlayer].updateArmySize(players[currentPlayer].getTotalArmySize() - 1);

			//remove region left
			regionsLeft -= 1;
		}
		//else if there are no regions left
		else {
			//if the player has troops left to place
			if (players[currentPlayer].getTotalArmySize() > 0) {

				// TODO: once region is implemented, update each region the player puts a troop on to.
				
				//remove troop from player's troop count
				players[currentPlayer].updateArmySize(players[currentPlayer].getTotalArmySize() - 1);
			}
		}
	}
}

// TODO: implement game data access methods

// TODO: implement game status update methods