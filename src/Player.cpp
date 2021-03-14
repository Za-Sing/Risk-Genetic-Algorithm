#include "Player.h"

// Create a player with the default troop size and 3 random cards
Player::Player(int numPlayers, vector<Card>* deck)
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
	
	// Pick 3 random cards
	for (int i = 0; i < 3; ++i) {
		int randIndex = rand() % deck->size(); // Pick random card
		this->hand.push_back(deck->at(randIndex)); // Add card to hand
		deck->erase(deck->begin() + randIndex); // Remove card from deck
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


//UPDATE 3/14 JOSH:
//changed to add card to a vector of cards

// TODO: add method to 
void Player::addCard(Card card)
{
	vector<Card> currentCards;
	this->getHand() = currentCards;
	currentCards.push_back(card);
	this->hand = currentCards;
}

//UPDATE 3/14 JOSH
//added method to remove card

// TODO: add method to check if card exists in deck
void Player::removeCard(Card card)
{
	vector<Card> currentCards;
	this->getHand() = currentCards;
	int index = find(currentCards.begin(), currentCards.end(), card);
	this->hand = currentCards.erase(index);
}
