#ifndef REGION_H
#define REGION_H

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

// Declare this to avoid circular dependency errors
class Player;

class Region
{
private:
	int id;  // label regions with integer ID's for easier vector access
	int num_borders;
	int troops;
	vector<int> border_ids;
	//Player* commander;
	int commander_id;
	string name;

public:
	Region(int, string, vector<int>);

	int getID();

	string getName();

	vector<int> getBorder_ids();

	void updateTroops(int numTroops);

	void addTroops(int numTroops);

	int getTroops();

	void updateCommander_id(int commander_id);

	int getCommander_id();


};

#endif // !REGION_H