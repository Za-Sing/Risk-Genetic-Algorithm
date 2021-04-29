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

	// Pre-train the GA
	//GeneticAlgorithm GA = GeneticAlgorithm();
	//GA.preEvolveAttack(100, 100, 0.30);
	
	string input;
	printf("Enter a number (3-5) of players.\n");
	getline(cin, input);
	int numPlayers = stoi(input);
	printf("Indicate how many will be bots.\n");
	getline(cin, input);
	int numBots = stoi(input);
	printf("Indicate how many bots will be pretrained.\n");
	getline(cin, input);
	int numPretrainedBots = stoi(input);
	// Make sure the range is correct
	while (numPlayers < 3 || numPlayers > 5) {
		printf("Please enter a number between 3 & 5.\n");
		getline(cin, input);
		numPlayers = stoi(input);
	}

	// Initialize Players vector
	vector<Player*>* players = new vector<Player*>();
	for (int i = 0; i < numPlayers; i++) {
		if (numBots > 0) {
			Player* newPlayer = new Player(numPlayers, true);
			players->push_back(newPlayer);
			--numBots;
		}
		else {
			Player* newPlayer = new Player(numPlayers, false);
			players->push_back(newPlayer);
		}
	}

	
	game.beginningClaim(players);

    //main game loop
	bool inPlay = true;
	int roundIndex = 0;
	while (inPlay)
	{
		for (int currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
		{
			if (!players->at(currentPlayer)->getDefeated()) {

				game.placeTroops(currentPlayer, players);
		  		bool gainedARegion = false;
			

			  // attack regions
			  printf("Make an attack? y/n\n");
			  char attackResponse;
				cin >> attackResponse;
				while (attackResponse == 'y')
				{

					game.attackSequence(players, currentPlayer, &gainedARegion);
					printf("Make another attack? y/n\n");
					cin >> attackResponse;


				}

				// move troops
				bool inputing = true;
				bool chainExists = false;
				while (inputing)
				{
					string troopMovement;
					printf("Move your troops, Player %i. Enter in the form <Origin Region ID> <Target Region ID> <# of Troops>.\n", currentPlayer);
					getline(cin, troopMovement);
					if (players->at(currentPlayer)->getGA() != NULL) 
					{
						troopMovement = players->at(currentPlayer)->getGA()->gaPlay(8, currentPlayer, -1, game.board);
					}
					else 
					{
						getline(cin, troopMovement);
					}
					
					vector<int> splitInt;
					stringstream ss(troopMovement);
					string element;
					while (getline(ss, element, ' '))
					{
						splitInt.push_back(stoi(element));
					}
					if (splitInt.at(0) != -1)
					{

						if (game.board.at(splitInt.at(0)).getCommander_id() != currentPlayer || game.board.at(splitInt.at(1)).getCommander_id() != currentPlayer)
						{
							printf("You don't own at least one of those regions.\n");
							continue;
						}
						else
						{

							vector<bool> falses(game.board.size(), false);
							if (game.isChain(splitInt.at(0), splitInt.at(1), currentPlayer, falses))	// check for chain
							{
								if (game.board.at(splitInt.at(0)).getTroops() > splitInt.at(2))
								{
									game.board.at(splitInt.at(0)).addTroops(-splitInt.at(2));
									game.board.at(splitInt.at(1)).addTroops(splitInt.at(2));
									inputing = false;
								}
								else
								{
									printf("You don't have that many troops to move.\n");
									continue;
								}


							}
							else
							{
								printf("You don't have a chain of regions along which to move troops.\n");
								continue;
							}
						}
					}
					else
					{
						inputing = false;
					}
				}
			}
		}


		//how to intialize Card
		//Card testy{ TERRITORY::China, TROOP::Artillery };



		++roundIndex; // end of round
	}
	// De-allocate memory
	for (int i = 0; i < players->size(); ++i) {
		delete players->at(i);
	}
	delete players;
}