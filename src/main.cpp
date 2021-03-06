#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Region.h"

int main()
{
	//game setup
	int numPlayers;
	std:cout << "Enter a number (2-6) of players.\n";
	std:cin >> numPlayers;
	vector<Player> players;
	for (int i = 0; i < numPlayers; i++)
	{
		Player newPlayer = Player();
		players.push_back(newPlayer);
	}

    //main game loop
	bool inPlay = true;
	int roundIndex = 0;
	while (inPlay)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			// place troops
			std:cout << "It's player " << to_string(i) << "'s turn. Place your troops.";
			string troopPlacement;
			std:cin >> troopPlacement;


			// attack regions

			// move troops
		}


		++roundIndex; // end of round
	}
} 