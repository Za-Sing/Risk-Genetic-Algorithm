/*
* Brisk is for encapsulating the main game loop. In it, there is the initial pre-game setup for territory claiming
* and reinforcing. It is also used for accessing game data at will, and for updating the status of the game.
*/
#include "Brisk.h"

using namespace std;
//function for random dice rolls
int rollDie()
{
	int roll;
	roll = rand() % 6 + 1; //six sided die roll
	return roll;
}

// Initialize the card deck from a file
void Brisk::initDeck(string filename) {
	ifstream file;
	file.open(filename);
	string line;
	deck = new vector<Card>();
	// Read through the file
	while (getline(file, line)) {
		Card card;
		// Read in the enum property for territory
		card.territory = static_cast<TERRITORY>(stoi(line));
		// Read next line
		if (!getline(file, line))
			break;
		// Assign troop type
		card.troop = static_cast<TROOP>(stoi(line));
		// Add card to deck
		deck->push_back(card);
	}
	// Shuffle the deck now that it is initialized
	random_shuffle(deck->begin(), deck->end());
	file.close();
}

Brisk::Brisk()
{
	//initialize board (vector of regions)
	board.push_back(Region(0, "Alaska", vector<int>{1, 3, 24}));
	board.push_back(Region(1, "Northwest_Territory", vector<int>{0, 3, 4, 2}));
	board.push_back(Region(2, "Greenland", vector<int>{1, 4, 5, 13}));
	board.push_back(Region(3, "Alberta", vector<int>{0, 1, 4, 6}));
	board.push_back(Region(4, "Ontario", vector<int>{1, 2, 5, 7, 6, 3}));
	board.push_back(Region(5, "Eastern_Canada", vector<int>{4, 2, 7}));
	board.push_back(Region(6, "Western_United_States", vector<int>{3, 4, 7, 8}));
	board.push_back(Region(7, "Eastern_United_States", vector<int>{6, 4, 5, 8}));
	board.push_back(Region(8, "Central_America", vector<int>{6, 7}));
	board.push_back(Region(9, "Venezuela", vector<int>{8, 10, 11})); 
	board.push_back(Region(10, "Brazil", vector<int>{9, 11, 12})); 
	board.push_back(Region(11, "Peru", vector<int>{9, 10, 12}));
	board.push_back(Region(12, "Argentina", vector<int>{10, 11})); 
	board.push_back(Region(13, "Iceland", vector<int>{2, 14, 16})); 
	board.push_back(Region(14, "Scandinavia", vector<int>{13, 15, 16, 17})); 
	board.push_back(Region(15, "Russia", vector<int>{14, 17, 19, 20, 25, 29})); 
	board.push_back(Region(16, "Great_Britain", vector<int>{13, 14, 17})); 
	board.push_back(Region(17, "Northern_Europe", vector<int>{14, 15, 16, 18, 19}));
	board.push_back(Region(18, "Western_Europe", vector<int>{16, 17, 19, 32})); 
	board.push_back(Region(19, "Southern_Europe", vector<int>{15, 17, 18, 32, 33})); 
	board.push_back(Region(20, "Ural", vector<int>{15, 21, 25, 26})); 
	board.push_back(Region(21, "Siberia", vector<int>{20, 22, 23, 26, 27})); 
	board.push_back(Region(22, "Yakutsk", vector<int>{21, 23, 24})); 
	board.push_back(Region(23, "Irkutsk", vector<int>{21, 22, 24, 27})); 
	board.push_back(Region(24, "Kamchatka", vector<int>{0, 22, 23, 27, 28}));
	board.push_back(Region(25, "Afghanistan", vector<int>{15, 20, 26, 29, 30})); 
	board.push_back(Region(26, "China", vector<int>{20, 25, 27, 30, 31})); 
	board.push_back(Region(27, "Mongolia", vector<int>{21, 23, 24, 26, 28})); 
	board.push_back(Region(28, "Japan", vector<int>{24, 27})); 
	board.push_back(Region(29, "Middle_East", vector<int>{15, 19, 25, 30, 33, 34})); 
	board.push_back(Region(30, "India", vector<int>{25, 26, 29, 31})); 
	board.push_back(Region(31, "Southeast_Asia", vector<int>{26, 30, 38}));
	board.push_back(Region(32, "North_Africa", vector<int>{10, 18, 19, 33, 34, 35})); 
	board.push_back(Region(33, "Egypt", vector<int>{19, 29, 32, 34})); 
	board.push_back(Region(34, "East_Africa", vector<int>{29, 32, 33, 35, 36, 37})); 
	board.push_back(Region(35, "Central_Africa", vector<int>{32, 34, 36})); 
	board.push_back(Region(36, "South_Africa", vector<int>{34, 35, 37})); 
	board.push_back(Region(37, "Madagascar", vector<int>{34, 36}));
	board.push_back(Region(38, "Indonesia", vector<int>{31, 39, 40})); 
	board.push_back(Region(39, "New_Guinea", vector<int>{38, 41})); 
	board.push_back(Region(40, "Western_Australia", vector<int>{38, 41})); 
	board.push_back(Region(41, "Eastern_Australia", vector<int>{39, 40}));

	// Initialize shuffled deck
	initDeck("Resources/card_deck.txt");
}

// Helper function to handle player card bonus
int Brisk::cardBonus(Player* currentPlayer, vector<int>* plusTwoRegions, int turn) 
{
	int newTroops = 0;
	vector<Card> currentHand = currentPlayer->getHand();
	// Determine what types of cards the player has
	int numInf = 0, numCav = 0, numArt = 0, numWild = 0;
	for (int i = 0; i < currentHand.size(); ++i) {
		if (currentHand[i].troop == TROOP::Infantry)
			++numInf;
		if (currentHand[i].troop == TROOP::Cavalry)
			++numCav;
		if (currentHand[i].troop == TROOP::Artillery)
			++numArt;
		if (currentHand[i].troop == TROOP::WiLD)
			++numWild;
	}
	// Now determine what combinations they have
	string comboType = "";
	if (numInf >= 3)
		comboType = "3inf";
	if (numCav >= 3)
		comboType = "3cav";
	if (numArt >= 3)
		comboType = "3art";
	if (numInf == 2 && numWild >= 1)
		comboType = "2inf1wild";
	if (numCav == 2 && numWild >= 1)
		comboType = "2cav1wild";
	if (numArt == 2 && numWild >= 1)
		comboType = "2art1wild";
	if (numInf >= 1 && numCav >= 1 && numArt >= 1)
		comboType = "1ofeach";

	if (comboType != "") {
		if (currentHand.size() >= 5) {
			printf("You have five cards, so a set must be traded in.\n");
			printf("Which cards would you like to trade in?\n");
			string cards;
			getline(cin, cards);
			vector<int> returnedCards;
			stringstream ss(cards);
			string element;
			while (getline(ss, element, ' '))
			{
				returnedCards.push_back(stoi(element));
			}
			for (int i = 0; i < 3; i++)
			{
				if (board.at(currentPlayer->getHand().at(i).territory).getCommander_id() == turn)
				{
					plusTwoRegions->push_back(board.at(currentPlayer->getHand().at(i).territory).getID());
				}
			}
			currentPlayer->playCards(deck, returnedCards);
			switch (setsTraded) {
			case 0: newTroops += 4; ++setsTraded; break;
			case 1: newTroops += 6; ++setsTraded; break;
			case 2: newTroops += 8; ++setsTraded; break;
			case 3: newTroops += 10; ++setsTraded; break;
			case 4: newTroops += 12; ++setsTraded; break;
			case 5: newTroops += 15; ++setsTraded; break;
			default: newTroops += (setsTraded - 2) * 5;
			}
		}
		else {
			string choice;
			bool choiceMade = false;
			printf("Would you like to trade a set of cards? Enter y or n.\n");
			while (getline(cin, choice) && !choiceMade) {
				if (choice == "y") {
					printf("Which cards would you like to trade in?\n");
					string cards;
					getline(cin, cards);
					vector<int> returnedCards;
					stringstream ss(cards);
					string element;
					while (getline(ss, element, ' '))
					{
						returnedCards.push_back(stoi(element));
					}
					for (int i = 0; i < 3; i++)
					{
						if (board.at(currentPlayer->getHand().at(i).territory).getCommander_id() == turn)
						{
							plusTwoRegions->push_back(board.at(currentPlayer->getHand().at(i).territory).getID());
						}
					}
					currentPlayer->playCards(deck, returnedCards);

					switch (setsTraded) {
					case 0: newTroops += 4; ++setsTraded; break;
					case 1: newTroops += 6; ++setsTraded; break;
					case 2: newTroops += 8; ++setsTraded; break;
					case 3: newTroops += 10; ++setsTraded; break;
					case 4: newTroops += 12; ++setsTraded; break;
					case 5: newTroops += 15; ++setsTraded; break;
					default: newTroops += (setsTraded - 2) * 5;
					}
					choiceMade = true;
				}
				else if (choice == "n") {
					choiceMade = true;
				}
				else {
					printf("Please enter y or n.\n");
				}
			}
		}
	}
	return newTroops;
}

// Helper function to check if a player gets a continent bonus
int Brisk::continentBonus(vector<Region> ownedRegions) 
{
	int numRegions = ownedRegions.size();
	int newTroops = 0;

	// Check if player owns North America
	int matches = 0;
	for (int i = 0; i < NORTH_AMERICA.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == NORTH_AMERICA.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == NORTH_AMERICA.size()) {
		newTroops += 5;
	}

	// Check if player owns South America
	matches = 0;
	for (int i = 0; i < SOUTH_AMERICA.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == SOUTH_AMERICA.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == SOUTH_AMERICA.size()) {
		newTroops += 2;
	}

	// Check if player owns Europe
	matches = 0;
	for (int i = 0; i < EUROPE.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == EUROPE.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == EUROPE.size()) {
		newTroops += 5;
	}

	// Check if player owns Asia
	matches = 0;
	for (int i = 0; i < ASIA.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == ASIA.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == ASIA.size()) {
		newTroops += 7;
	}

	// Check if player owns Africa
	matches = 0;
	for (int i = 0; i < AFRICA.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == AFRICA.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == AFRICA.size()) {
		newTroops += 3;
	}

	// Check if player owns Australia
	matches = 0;
	for (int i = 0; i < AUSTRALIA.size(); ++i) {
		for (int j = 0; j < numRegions; ++j) {
			if (ownedRegions[j].getID() == AUSTRALIA.at(i).getID()) {
				++matches;
			}
		}
	}
	if (matches == AUSTRALIA.size()) {
		newTroops += 2;
	}

	return newTroops;
}

/*
* Recursive method to be used in troop movement phase.
* Returns true if the current player controls a connected
* "chain" of regions from the beginning to the end of the
* troop movement.
*/
bool Brisk::isChain(int startID, int endID, int currentPlayer, vector<bool> visited)
{
	visited.at(startID) = true;
	for (int i = 0; i < board.at(startID).getBorder_ids().size(); i++)
	{
		if (visited.at(board.at(startID).getBorder_ids().at(i)))
		{
			continue;
		}
		if (board.at(board.at(startID).getBorder_ids().at(i)).getCommander_id() != currentPlayer)
		{
			continue;
		}
		if (board.at(startID).getBorder_ids().at(i) == endID)
		{
			return true;
		}
		if (isChain(board.at(startID).getBorder_ids().at(i), endID, currentPlayer, visited))
		{
			return true;
		}
	}

	return false;
}

void Brisk::beginningClaim(vector<Player*>* players) {

	//For dice roll, need only call this once so this is a good place for it.
	//srand(time(NULL));


	numPlayers = players->size();

	//find number of turns total after regions are chosen
	switch (numPlayers)
	{
	case 3: numTurns = 35; break;
	case 4: numTurns = 30; break;
	case 5: numTurns = 25; break;
	}

	regionsLeft = NUM_REGIONS;

	//claim new territories until territories gone

	//go for the number of regions left to choose from
		for (int i = 0; i < numTurns * numPlayers; i++) {
		//cycle through players
		currentPlayer = (i % numPlayers);

		//if empty regions exist
		if (regionsLeft != 0) {

			//set exit condition to false
			succPlaceRegion = false;
			//loop until exit condition is true
			while (succPlaceRegion == false) {
				//print and take player's region choice
				printf("Player %i, please choose next region ID for region to occupy.\n", currentPlayer);
				if (players->at(currentPlayer)->getGA() != NULL)
				{
					regionChoice = stoi(players->at(currentPlayer)->getGA()->gaPlay(0, currentPlayer, -1, &board));
				}
				else
				{
					cin >> regionChoice;
				}


				// update each region to be owned by the player that chooses it
				// the region is removed from the selectable pool of regions

				//Error catching for invalid region
				if ((regionChoice < 0) || (regionChoice > 41)){
					cout << "Invalid choice! Please choose a real region ID.\n\n\n";
				}
				//if the region chosen has not been claimed
				else if (board[regionChoice].getCommander_id() == 99) {
					vector<Region> currentRegions = players->at(currentPlayer)->getOwnedRegions();
					currentRegions.push_back(board[regionChoice]);
					board[regionChoice].addTroops(1);
					board[regionChoice].updateCommander_id(currentPlayer);
					players->at(currentPlayer)->updateOwnedRegions(currentRegions);
					succPlaceRegion = true;
				}
				else {
					cout << "Invalid choice! That region has already been claimed.\n\n\n";
				}
			}
			//remove troop from player's troop count
			players->at(currentPlayer)->updateArmySize(players->at(currentPlayer)->getTotalArmySize() - 1);

			//remove region left
			regionsLeft--;
		}
		//else if there are no regions left
		else {
			//if the player has troops left to place
			if (players->at(currentPlayer)->getTotalArmySize() > 0) {

				printf("Player %i, please add a troop to one of your owned regions.\n", currentPlayer);

				// update each region the player puts a troop on to.

				succPlaceTroop = false;
				while (succPlaceTroop == false) {

					if (players->at(currentPlayer)->getGA() != NULL)
					{
						regionChoice = stoi(players->at(currentPlayer)->getGA()->gaPlay(1, currentPlayer, -1, &board));
					}
					else
					{
						cin >> regionChoice;
					}

					// check that they own the region
					if (board[regionChoice].getCommander_id() == currentPlayer) {
						board[regionChoice].addTroops(1);
						succPlaceTroop = true;
					}
					else {
						cout << "Invalid choice! Please choose a region you own.";
					}
				}

				//remove troop from player's troop count
				players->at(currentPlayer)->updateArmySize(players->at(currentPlayer)->getTotalArmySize() - 1);
			}
		}
	}
}

void Brisk::placeTroops(int currentPlayer, vector<Player*>* players)
{
	//calculate player's new troops
	vector<Region> ownedRegions = players->at(currentPlayer)->getOwnedRegions();
	int numRegions = ownedRegions.size();
	int newTroops = numRegions / 3;		//Fix to align with rules
	


	printf("Your hand: ");
	vector<Card> hand = players->at(currentPlayer)->getHand();
	for (int i = 0; i < hand.size(); i++)
	{
		int cardRegion = hand.at(i).territory;
		int cardTroopType = hand.at(i).troop;
		printf("%i %i    \n", cardRegion, cardTroopType);
	}
	

	// Check if the player gets a card bonus
	
	vector<int> plusTwoRegions;
	newTroops += cardBonus(players->at(currentPlayer), &plusTwoRegions, currentPlayer);
	for (int i = 0; i < plusTwoRegions.size(); i++)
	{
		board.at(plusTwoRegions.at(i)).addTroops(2);
	}


	// Check if the player gets a continent bonus
	newTroops += continentBonus(ownedRegions);

	// Now place troops
	printf("It's player %i's turn. You have %i new troops to place.\nInput your troop placement in the form: <Region ID> <# of new troops>.\n", currentPlayer, newTroops);
	string troopPlacement;
	if (players->at(currentPlayer)->getGA() != NULL)
	{
		players->at(currentPlayer)->getGA()->gaPlay(2, currentPlayer, newTroops, &board);
	}
	else
	{
		getline(cin, troopPlacement);
		while (getline(cin, troopPlacement) && newTroops != 0) {


			vector<int> splitInt;
			stringstream ss(troopPlacement);
			string element;
			while (getline(ss, element, ' '))
			{
				splitInt.push_back(stoi(element));
			}
			if (board.at(splitInt.at(0)).getCommander_id() != currentPlayer)
			{
				printf("You don't control that region.");
				continue;
			}
			if (splitInt.at(1) <= newTroops)
			{
				board.at(splitInt.at(0)).addTroops(splitInt.at(1));
				newTroops -= splitInt.at(1);
				printf("%i new troops left to place.\n", newTroops);
			}
			else
			{
				printf("You don't have that many troops to place.\n");
			}

		}
	}
	
}

// This handles the attack/defend sequence
void Brisk::attackSequence(vector<Player*>* players, int currentPlayer, bool* gainedARegion)
{
	string input;
	bool badChoice = true;
	captured = false;
	defended = false;
	repeat = true;

	// Get the region to be attacked
	printf("Player %i, which region would you like to attack?\n", currentPlayer);
	// Check if the player is a GA
	if (players->at(currentPlayer)->getGA() != NULL) {
		input = players->at(currentPlayer)->getGA()->gaPlay(4, currentPlayer, -1, &board);
	}
	else {
		getline(cin, input);
		getline(cin, input);
	}
	attackTo = stoi(input);

	// Make sure the player doesn't already own this region
	while (badChoice == true) {
		for (int i = 0; i < players->at(currentPlayer)->getOwnedRegions().size(); ++i) {
			if (players->at(currentPlayer)->getOwnedRegions()[i].getID() == attackTo) {
				printf("You already own this region! Please select again.\n");
				getline(cin, input);
				attackTo = stoi(input);
				badChoice = true;
			}
			else {
				badChoice = false;
			}
		}
	}
	badChoice = true;

	// Now get the region from which to attack
	printf("Where would you like to attack from?");
	if (players->at(currentPlayer)->getGA() != NULL) {
		input = players->at(currentPlayer)->getGA()->gaPlay(5, currentPlayer, -1, &board);
	}
	else {
		getline(cin, input);
	}
	attackFrom = stoi(input);

	// Make sure the player owns this region, and that it borders the region to be attacked
	while (badChoice == true) {

		vector<int> ownedRegionIDs;
		for (int i = 0; i < players->at(currentPlayer)->getOwnedRegions().size(); ++i)
		{
			ownedRegionIDs.push_back(players->at(currentPlayer)->getOwnedRegions().at(i).getID());
		}

		if (count(ownedRegionIDs.begin(), ownedRegionIDs.end(), attackFrom))
		{
			badChoice = false;
		}
		else
		{
			printf("You do not own this region! Please select again.\n");
		}
		vector<int> borders = board[attackFrom].getBorder_ids();
		if (!badChoice && count(borders.begin(), borders.end(), attackTo) == 0) {
			printf("This region does not border the one you wish to attack! Please select again.\n");
			getline(cin, input);
			attackFrom = stoi(input);
			badChoice = true;
		}
		else {
			badChoice = false;
		}
	}
	badChoice = true;

	while (repeat == true) {

		// Now get number of troops to attack with
		printf("How many troops would you like to use? choose 1 through 3.\n");
		if (players->at(currentPlayer)->getGA() != NULL) {
			input = players->at(currentPlayer)->getGA()->gaPlay(6, currentPlayer, -1, &board);
		}
		else {
			getline(cin, input);
		}

		int attackTroops = stoi(input);
		//check that it's a valid number of troops
		while (badChoice == true) {
			if (attackTroops < 1 || attackTroops > 3) {
				printf("You must choose between 1, 2, or 3! Please select again.\n");
				getline(cin, input);
				attackTroops = stoi(input);
			}
			else {
				badChoice = false;
			}
		}
		badChoice = true;

		bool badChoice2 = true;

		// Make sure the player has enough troops
		while (badChoice == true) {
			if (board[attackFrom].getTroops() - attackTroops < 1) {
				printf("You must leave at least 1 troop left in the territory! Please select again.\n");
				getline(cin, input);
				attackTroops = stoi(input);


				while (badChoice2 == true) {
					if (attackTroops < 1 || attackTroops > 3) {
						printf("You must choose between 1, 2, or 3! Please select again.\n");
						getline(cin, input);
						attackTroops = stoi(input);
					}
					else {
						badChoice2 = false;
					}
				}
			}
			else {
				badChoice = false;
			}
		}
		badChoice = true;

		//initialize empty dice
		for (int i = 0; i < 2; i++) {
			attack[i] = 0;
			defend[i] = 0;
		}
		attack[2] = 0;

		// Get attacker dice rolls
		for (int i = 0; i < attackTroops; i++) {
			printf("Player %i, Say something to roll! (press enter)\n", currentPlayer);
			if (players->at(currentPlayer)->getGA() != NULL) {
				input = "";
			}
			else {
				getline(cin, input);
			}
			//devtool
			if (input == "ULTRA_CRITICAL_DICE_ROLL_FRICKAA") {
				printf("What is thy bidding, my master?\n");
				getline(cin, input);
				attack[i] = stoi(input);
				printf("So be it, it be like it, sometimes, but especially now.\nManual Dice recorded.\n");
			}
			else {
				attack[i] = rollDie();
			}
		}


		//get defender dice rolls
		defender = board[attackTo].getCommander_id();
		printf("Player %i, choose how many troops to defend with!\n", defender);
		if (players->at(currentPlayer)->getGA() != NULL) {
			input = players->at(currentPlayer)->getGA()->gaPlay(7, defender, -1, &board);
		}
		else {
			getline(cin, input);
		}
		int defendTroops = stoi(input);

		//check that it's a valid number of troops
		while (badChoice == true) {
			if (defendTroops < 1 || defendTroops > 2) {
				printf("You must choose between 1 or 2! Please select again.\n");
				getline(cin, input);
				defendTroops = stoi(input);
			}
			else {
				badChoice = false;
			}
		}
		badChoice = true;
		badChoice2 = true;

		// Make sure the player has enough troops
		while (badChoice == true) {
			if (board[attackTo].getTroops() - defendTroops < 0) {
				printf("You must choose a number of troops you actually have here! Please select again.\n");
				getline(cin, input);
				defendTroops = stoi(input);

				while (badChoice2 == true) {
					if (defendTroops < 1 || defendTroops > 2) {
						printf("You must choose between 1 or 2! Please select again.\n");
						getline(cin, input);
						defendTroops = stoi(input);
					}
					else {
						badChoice2 = false;
					}
				}
			}
			else {
				badChoice = false;
			}
		}
		badChoice = true;


		// Get defender dice rolls
		for (int i = 0; i < defendTroops; i++) {
			printf("Player %i, Say something to roll! (press enter)\n", defender);
			if (players->at(currentPlayer)->getGA() != NULL) {
				input = "";
			}
			else {
				getline(cin, input);
			}
			//devtool
			if (input == "ULTRA_CRITICAL_DICE_ROLL_FRICKAA") {
				printf("Hello There!\n");
				getline(cin, input);
				defend[i] = stoi(input);
				printf("GENERAL KENOBI!\nManual Dice recorded.\n");
			}
			else {
				defend[i] = rollDie();
			}
		}

		//print dice rolls
		printf("\nPlayer %i, your attack rolls were:\n", currentPlayer);
		for (int i = 0; i < attackTroops; i++) {
			cout << i + 1 << ": " << attack[i] << "\n";
		}

		printf("\nPlayer %i, your defend rolls were:\n", defender);
		for (int i = 0; i < defendTroops; i++) {
			cout << i + 1 << ": " << defend[i] << "\n";
		}

		//compare max dice

		attackLoss = 0;
		defendLoss = 0;

		int n = sizeof(attack) / sizeof(attack[0]);
		int m = sizeof(defend) / sizeof(defend[0]);

		sort(attack, attack + n);
		sort(defend, defend + m);

		if (attack[2] > defend[1]) {
			defendLoss++;
		}
		else {
			attackLoss++;
		}

		if (attackTroops == 2 || attackTroops == 3) {
			if (defendTroops == 2) {
				if (attack[1] > defend[0]) {
					defendLoss++;
				}
				else {
					attackLoss++;
				}
			}
		}


		//print player troop loss
		printf("Player %i lost %i troops!\n", currentPlayer, attackLoss);
		printf("Player %i lost %i troops!\n\n", defender, defendLoss);

		//remove troops from region count
		board[attackFrom].addTroops(attackLoss * -1);
		board[attackTo].addTroops(defendLoss * -1);

		//print it
		printf("Player %i now has %i troops in the region.\n", currentPlayer, board[attackFrom].getTroops());
		printf("Player %i now has %i troops in the region.\n", defender, board[attackTo].getTroops());

		//check if defender has lost region
		if (board[attackTo].getTroops() == 0) {
			printf("Player %i has lost the region!\nPlayer %i now owns the region.\n\n", defender, currentPlayer);

			vector<Region> currentRegions = players->at(defender)->getOwnedRegions();
			int deleteI = 0;
			for (int i = 0; i < currentRegions.size(); ++i) {
				if (currentRegions.at(i).getID() == attackTo) {
					deleteI = i;
					break;
				}
			}
			currentRegions.erase(currentRegions.begin() + deleteI);
			players->at(defender)->updateOwnedRegions(currentRegions);

			currentRegions = players->at(currentPlayer)->getOwnedRegions();
			currentRegions.push_back(board[attackTo]);
			players->at(currentPlayer)->updateOwnedRegions(currentRegions);

			if (players->at(defender)->getOwnedRegions().size() == 0) {
				printf("Player %i has been defeated!\n", defender);

				players->at(defender)->setDefeated(true);
			}

			board[attackTo].updateCommander_id(currentPlayer);
			board[attackTo].updateTroops(attackTroops - attackLoss);
			printf("Player %i now has %i troops in the region.\n", currentPlayer, attackTroops - attackLoss);
			captured = true;
			if (*gainedARegion == false)
			{
				players->at(currentPlayer)->drawCard(deck);
				*gainedARegion = true;
			}
		}

		//else check if defender has defended against attacker
		else if ((board[attackTo].getTroops() > 0) && (board[attackFrom].getTroops() == 1)) {
				printf("Player %i has defended his region against Player %i! Player %i retreats.\n", defender, currentPlayer, currentPlayer);
				defended = true;
		}

		string reAttack;
		if ((captured == false) && (defended == false)) {
			printf("attack again? y / n\n");
			if (players->at(currentPlayer)->getGA() != NULL) {
				reAttack = players->at(currentPlayer)->getGA()->gaPlay(8, currentPlayer, -1, &board);
			}
			else {
				getline(cin, reAttack);
			}
			if (reAttack == "y") {
				repeat = true;
			}
			else {
				repeat = false;
			}
		}
		else {
			repeat = false;
		}

	}
}

// TODO: implement game data access methods



// TODO: implement game status update methods
