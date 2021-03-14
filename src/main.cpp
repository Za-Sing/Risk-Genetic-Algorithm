#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Region.h"
#include "Brisk.h"

using namespace std;

int main()
{
	//game setup
	int numPlayers;
	cout << "Enter a number (2-5) of players.\n";
	cin >> numPlayers;
	vector<Player> players;
	for (int i = 0; i < numPlayers; i++)
	{
		Player newPlayer = Player();
		players.push_back(newPlayer);
	}

	// TODO: hard code deck



    //main game loop
	bool inPlay = true;
	int roundIndex = 0;
	while (inPlay)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			// place troops
			cout << "It's player " << to_string(i) << "'s turn. Place your troops.";
			string troopPlacement;
			cin >> troopPlacement


			// attack regions

			// move troops
		}


		//how to intialize Card
		//Card testy{ TERRITORY::China, TROOP::Artillery };



		++roundIndex; // end of round
	}
} 