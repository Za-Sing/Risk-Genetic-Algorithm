#ifndef REGION_H
#define REGION_H

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;


class Region
{
private:
	int id;  // label regions with integer IDs for easier vector access
	int troops;
	vector<int> border_ids;
	int commander_id;
	string name;

public:
	Region(int, string, vector<int>);

	int getID() const;

	string getName() const;

	vector<int> getBorder_ids() const;

	void updateTroops(int numTroops);

	void addTroops(int numTroops);

	int getTroops() const;

	void updateCommander_id(int commander_id);

	int getCommander_id() const;
};

#endif // !REGION_H