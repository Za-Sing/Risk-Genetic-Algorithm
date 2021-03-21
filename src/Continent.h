#ifndef CONTINENT_H
#define CONTINENT_H

#include <stdlib.h>
#include <vector>
#include <string>
#include "Region.h"
using namespace std;

#pragma once
class Continent
{
	private:
		int num_borders, num_regions;
		vector<Region> regions;

	public:
		Continent(int, int, vector<Region>);

};

#endif // !CONTINENT_H