#include "Player.h"

// Create a player with the default troop size and 3 random cards
Player::Player(int numPlayers, vector<Card>* deck)
{
	// Initial army size depends on number of players
	switch (numPlayers) 
	{
	case 2: this->numTroops = 40;
	case 3: this->numTroops = 35;
	case 4: this->numTroops = 30;
	case 5: this->numTroops = 25;
	case 6: this->numTroops = 20;
	}
	
	this->ownedRegions = vector<Region>();
	
	// Pick 3 random cards
	for (int i = 0; i < 3; ++i) {
		int randIndex = rand() % deck->size(); // Pick random card
		this->hand.push_back(deck->at(randIndex)); // Add card to hand
		deck->erase(deck->begin() + i); // Remove card from deck
	}
}


// Good 'ol getters and setters

int Player::getTotalArmySize()
{
	return numTroops;
}

void Player::updateArmySize(int size)
{
	this->numTroops = size;
}

vector<Region> Player::getOwnedRegions()
{
	return ownedRegions;
}

void Player::updateOwnedRegions(vector<Region> regions)
{
	this->ownedRegions = regions;
}

vector<Card> Player::getHand()
{
	return hand;
}

void Player::updateHand(vector<Card> cards)
{
	this->hand = cards;
}
