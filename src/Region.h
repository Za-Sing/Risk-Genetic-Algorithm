#include <stdlib.h>
#include <vector>
#include <string>
#include "Army.h"
using namespace std;
#pragma once

class Region
{
private:
	int num_borders;
	vector<string> borders;
	vector<Army>* occupants;

public:
	Region(int, vector<string>, vector<Army>*);

	void updateOccupants(vector<Army>* newOccupants);

};

