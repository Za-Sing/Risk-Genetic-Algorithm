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

// This method plays a set of three cards and adds them back to the deck
void Player::playCards(vector<Card>* deck, string comboType)
{
	// Handle each possible combination of cards
	
	if (comboType == "3inf") {
		int cardsPlayed = 0, i = 0;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Infantry) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
			}
			++i;
		}
	}
	else if (comboType == "3cav") {
		int cardsPlayed = 0, i = 0;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Cavalry) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
			}
			++i;
		}
	}
	else if (comboType == "3art") {
		int cardsPlayed = 0, i = 0;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Artillery) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
			}
			++i;
		}
	}
	else if (comboType == "2inf1wild") {
		int cardsPlayed = 0, infPlayed = 0, i = 0;
		bool wildPlayed = false;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Infantry && infPlayed < 2) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				++infPlayed;
			}
			if (hand[i].troop == TROOP::WiLD && !wildPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				wildPlayed = true;
			}
			++i;
		}
	}
	else if (comboType == "2cav1wild") {
		int cardsPlayed = 0, cavPlayed = 0, i = 0;
		bool wildPlayed = false;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Cavalry && cavPlayed < 2) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				++cavPlayed;
			}
			if (hand[i].troop == TROOP::WiLD && !wildPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				wildPlayed = true;
			}
			++i;
		}
	}
	else if (comboType == "2art1wild") {
		int cardsPlayed = 0, artPlayed = 0, i = 0;
		bool wildPlayed = false;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Artillery && artPlayed < 2) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				++artPlayed;
			}
			if (hand[i].troop == TROOP::WiLD && !wildPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				wildPlayed = true;
			}
			++i;
		}
	}
	else if (comboType == "1ofeach") {
		int cardsPlayed = 0, i = 0;
		bool infPlayed = false, cavPlayed = false, artPlayed = false;
		while (cardsPlayed < 3) {
			if (hand[i].troop == TROOP::Infantry && !infPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				infPlayed = true;
			}
			if (hand[i].troop == TROOP::Cavalry && !cavPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				cavPlayed = true;
			}
			if (hand[i].troop == TROOP::Artillery && !artPlayed) {
				deck->push_back(hand[i]);
				hand.erase(hand.begin() + i);
				++cardsPlayed;
				artPlayed = true;
			}
			++i;
		}
	}

	// Re-shuffle the deck
	random_shuffle(deck->begin(), deck->end());
}
