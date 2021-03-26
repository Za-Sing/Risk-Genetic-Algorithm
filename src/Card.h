#ifndef CARD_H
#define CARD_H

// Enumeration for all possible territories
typedef enum TERRITORY {
	WILD, Alaska, Northwest_Territory, Greenland, Alberta, Ontario, Eastern_Canada,
	Western_United_States, Eastern_United_States, Central_America, Venezuela, Brazil, Peru,
	Argentina, Iceland, Scandinavia, Russia, Great_Britain, Northern_Europe,
	Western_Europe, Southern_Europe, Ural, Siberia, Yakutsk, Irkutsk, Kamchatka,
	Afghanistan, China, Mongolia, Japan, Middle_East, India, Southeast_Asia,
	North_Africa, Egypt, East_Africa, Central_Africa, South_Africa, Madagascar,
	Indonesia, New_Guinea, Western_Australia, Eastern_Australia
};

// Enumeration for all troop names & values
typedef enum TROOP {WiLD = 0, Infantry = 1, Cavalry = 5, Artillery = 10};

// Simple struct for the card's values
typedef struct Card
{
	TERRITORY territory;
	TROOP troop;

	// Overload == operator as it is needed to use find() in Player.cpp
	friend bool operator== (const Card& card1, const Card& card2) {
		if (card1.territory == card2.territory && card1.troop == card2.troop) {
			return true;
		}
		else {
			return false;
		}
	}
};

#endif