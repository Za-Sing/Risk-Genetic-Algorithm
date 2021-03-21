#include "Player.h"

// Create a player with the default troop size
Player::Player(int numPlayers)
{
	// Initial army size depends on number of players
	switch (numPlayers) 
	{
	case 2: this->numTroops = 40; break;
	case 3: this->numTroops = 35; break;
	case 4: this->numTroops = 30; break;
	case 5: this->numTroops = 25; break;
	}
	
	this->ownedRegions = vector<Region>();
	this->hand = vector<Card>();
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


// This method will draw and remove a card from the deck and add it to the player's hand
void Player::drawCard(vector<Card>* deck)
{
	int randIndex = rand() % deck->size(); // Pick random card
	this->hand.push_back(deck->at(randIndex)); // Add card to hand
	deck->erase(deck->begin() + randIndex); // Remove card from deck
}

// This method removes a specific card from the hand
void Player::removeCard(Card card)
{
	vector<Card>::iterator index = find(this->hand.begin(), this->hand.end(), card);
	this->hand.erase(index);
}
