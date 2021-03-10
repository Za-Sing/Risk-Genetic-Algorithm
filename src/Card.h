#pragma once
#include <vector>
#include <string>

class Card
{
private:
	typedef const enum {Alaska, Northwest_Territory, Greenland, Alberta, Ontario, Eastern_Canada,
					Western_United_States, Eastern_United_States, Central_America, Venezuela, Brazil, Peru,
					Argentina, Iceland, Scandinavia, Russia, Great_Britain, Northern_Europe,
					Western_Europe, Southern_Europe, Ural, Siberia, Yakutsk, Irkutsk, Kamchatka,
					Afghanistan, China, Mongolia, Japan, Middle_East, India, Southeast_Asia,
					North_Africa, Egypt, East_Africa, Central_Africa, South_Africa, Madagascar,
					Indonesia, New_Guinea, Western_Australia, Eastern_Australia} TERRITORY;
	
	typedef const enum {Infantry=1, Cavalry=5, Artillery=10} TROOP;
	
	/*const vector<string> TERRITORIES = {"Alaska", "Northwest Territory", "Greenland", "Alberta", "Ontario", "Eastern Canada", 
										"Western United States", "Eastern United States", "Central America", "Venezuela", "Brazil", "Peru",
										"Argentina", "Iceland", "Scandinavia", "Russia", "Great Britain", "Northern Europe", 
										"Western Europe", "Southern Europe", "Ural", "Siberia", "Yakutsk", "Irkutsk", "Kamchatka", 
										"Afghanistan", "China", "Mongolia", "Japan", "Middle East", "India", "Southeast Asia",
										"North Africa", "Egypt", "East Africa", "Central Africa", "South Africa", "Madagascar", 
										"Indonesia", "New Guinea", "Western Australia", "Eastern Australia"};
	const vector<int> TROOPS = {1, 5, 10};*/
	
public:  
	TERRITORY territory;
	TROOP troop;

};

