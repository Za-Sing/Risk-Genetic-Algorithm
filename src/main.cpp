#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Brisk.h"
#include "Player.h"

using namespace std;

int main()
{
	//game setup
	Brisk game = Brisk();

	int numPlayers;
	cout << "Enter a number (2-5) of players.\n";
	cin >> numPlayers;
	vector<Player> players;
	for (int i = 0; i < numPlayers; i++)
	{

		Player newPlayer = Player(numPlayers);

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
			//calculate player's new troops
			vector<Region> ownedRegions = players.at(i).getOwnedRegions();
			int numRegions = ownedRegions.size();
			int newTroops = numRegions / 3;
			
			// place troops
			printf("It's player %i's turn. You have %i new troops to place.\nInput your troop placement in the form: <Region ID> <# of new troops>.\n", i, newTroops);
			string troopPlacement;
			getline(cin, troopPlacement);
			while (getline(cin, troopPlacement) && newTroops != 0) {


				vector<int> splitInt;
				stringstream ss(troopPlacement);
				string element;
				while (getline(ss, element, ' '))
				{
					splitInt.push_back(stoi(element));
				}
				if (splitInt.at(1) <= newTroops)
				{
					game.board.at(splitInt.at(0)).addTroops(splitInt.at(1));
					newTroops -= splitInt.at(1);
					printf("%i new troops left to place.\n", newTroops);
				}
				else
				{
					printf("You don't have that many troops to place.\n");
				}

			}

			// attack regions
			

			// move troops
		}


		//how to intialize Card
		//Card testy{ TERRITORY::China, TROOP::Artillery };



		++roundIndex; // end of round
	}
}