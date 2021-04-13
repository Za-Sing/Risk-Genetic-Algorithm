#ifndef BRISK_H
#define BRISK_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "Player.h"
#include "Card.h"

class Brisk
{
private:
	const int NUM_REGIONS = 42;
	
	// Declare the continents here
	const vector<Region> NORTH_AMERICA = { Region(0, "Alaska", vector<int>{1, 3, 24}), Region(1, "Northwest_Territory", vector<int>{0, 3, 4, 2}),
		Region(2, "Greenland", vector<int>{1, 4, 5, 13}), Region(3, "Alberta", vector<int>{0, 1, 4, 6}),
		Region(4, "Ontario", vector<int>{1, 2, 5, 7, 6, 3}), Region(5, "Eastern_Canada", vector<int>{4, 2, 7}),
		Region(6, "Western_United_States", vector<int>{3, 4, 7, 8}), Region(7, "Eastern_United_States", vector<int>{6, 4, 5, 8}),
		Region(8, "Central_America", vector<int>{6, 7}) };
	
	const vector<Region> SOUTH_AMERICA = { Region(9, "Venezuela", vector<int>{8, 10, 11}), Region(10, "Brazil", vector<int>{9, 11, 12}),
		Region(11, "Peru", vector<int>{9, 10, 12}), Region(12, "Argentina", vector<int>{10, 11}) };
	
	const vector<Region> EUROPE = { Region(13, "Iceland", vector<int>{2, 14, 16}), Region(14, "Scandinavia", vector<int>{13, 15, 16, 17}),
		Region(15, "Russia", vector<int>{14, 17, 19, 20, 25, 29}), Region(16, "Great_Britain", vector<int>{13, 14, 17}),
		Region(17, "Northern_Europe", vector<int>{14, 15, 16, 18, 19}), Region(18, "Western_Europe", vector<int>{16, 17, 19, 32}),
		Region(19, "Southern_Europe", vector<int>{15, 17, 18, 32, 33}) };
	
	const vector<Region> ASIA = { Region(20, "Ural", vector<int>{15, 21, 25, 26}), Region(21, "Siberia", vector<int>{20, 22, 23, 26, 27}),
		Region(22, "Yakutsk", vector<int>{21, 23, 24}), Region(23, "Irkutsk", vector<int>{21, 22, 24, 27}),
		Region(24, "Kamchatka", vector<int>{0, 22, 23, 27, 28}), Region(25, "Afghanistan", vector<int>{15, 20, 26, 29, 30}),
		Region(26, "China", vector<int>{20, 25, 27, 30, 31}), Region(27, "Mongolia", vector<int>{21, 23, 24, 26, 28}),
		Region(28, "Japan", vector<int>{24, 27}), Region(29, "Middle_East", vector<int>{15, 19, 25, 30, 33, 34}),
		Region(30, "India", vector<int>{25, 26, 29, 31}), Region(31, "Southeast_Asia", vector<int>{26, 30, 38}) };

	const vector<Region> AFRICA = { Region(32, "North_Africa", vector<int>{10, 18, 19, 33, 34, 35}),
		Region(33, "Egypt", vector<int>{19, 29, 32, 34}), Region(34, "East_Africa", vector<int>{29, 32, 33, 35, 36, 37}),
		Region(35, "Central_Africa", vector<int>{32, 34, 36}), Region(36, "South_Africa", vector<int>{34, 35, 37}),
		Region(37, "Madagascar", vector<int>{34, 36}) };

	const vector<Region> AUSTRALIA = { Region(38, "Indonesia", vector<int>{31, 39, 40}), Region(39, "New_Guinea", vector<int>{38, 41}),
		Region(40, "Western_Australia", vector<int>{38, 41}), Region(41, "Eastern_Australia", vector<int>{39, 40}) };
	
	int numTurns, numPlayers, currentPlayer, regionsLeft, regionChoice, attackFrom, attackTo, setsTraded = 0, defender, attackLoss, defendLoss;
	int attack[3];
	int defend[2];
	bool succPlaceRegion, succPlaceTroop, captured, defended, repeat;
	vector<Card>* deck;
	void initDeck(string filename);
public:
	Brisk();
	int continentBonus(vector<Region> ownedRegions);
	int cardBonus(Player* currentPlayer, vector<int>* plusTwoRegions, int turn);
	bool isChain(int startID, int endID, int currentPlayer, vector<bool> visited);
	void beginningClaim(vector<Player*>* players);
	void placeTroops(int currentPlayer, vector<Player*>* players);
	void attackSequence(vector<Player*>* players, int currentPlayer);
	vector<Region> board;
};

#endif // !BRISK_H
