#ifndef REGION_H
#define REGION_H

#include <stdlib.h>
#include <vector>
#include <string>
#include "Player.h"
using namespace std;
#pragma once

class Region
{
private:
	int num_borders;
	int troops;
	vector<string> borders;
	Player* commander;

public:
	Region(int, vector<string>, Player*);

	
};

#endif // !REGION_H