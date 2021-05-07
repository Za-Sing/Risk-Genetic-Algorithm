#include "Player.h"

// Create a player with the default troop size
Player::Player(int numPlayers, bool isBot)
{
	// Determine if a player is a bot running the GA
	if (isBot) {
		ga = new GeneticAlgorithm();
	}

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

GeneticAlgorithm* Player::getGA()
{
	return ga;
}

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

void Player::setDefeated(bool isDefeated) {
	this->defeated = isDefeated;
}

bool Player::getDefeated() {
	return defeated;
}



// This method will draw and remove a card from the deck and add it to the player's hand
void Player::drawCard(vector<Card>* deck)
{
	int randIndex = rand() % deck->size(); // Pick random card
	this->hand.push_back(deck->at(randIndex)); // Add card to hand
	deck->erase(deck->begin() + randIndex); // Remove card from deck
}

// This method plays a set of three cards and adds them back to the deck
void Player::playCards(vector<Card>* deck, vector<int> returnedCards)
{
	int remFirst = returnedCards.at(0);
	int remSecond;
	int remThird;
	int currentLargest = 0;
	for (int i = 0; i < 3; i++)
	{
		if (returnedCards.at(i) > remFirst)
		{
			remFirst = returnedCards.at(i);
			currentLargest = i;

		}
	}
	returnedCards.erase(returnedCards.begin() + currentLargest);
	if (returnedCards.at(0) > returnedCards.at(1))
	{
		remSecond = returnedCards.at(0);
		remThird = returnedCards.at(1);
	}
	else
	{
		remSecond = returnedCards.at(1);
		remThird = returnedCards.at(0);
	}
	deck->push_back(hand.at(remFirst));
	hand.erase(hand.begin() + remFirst);

	deck->push_back(hand.at(remSecond));
	hand.erase(hand.begin() + remSecond);

	deck->push_back(hand.at(remThird));
	hand.erase(hand.begin() + remThird);

	// Re-shuffle the deck
	random_shuffle(deck->begin(), deck->end());
}
