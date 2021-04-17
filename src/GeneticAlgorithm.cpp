#include "GeneticAlgorithm.h"

// Constructor, randomizes all decision factors
GeneticAlgorithm::GeneticAlgorithm()
{
	// Start troop factors between 0 and 15 for a reasonable starting value
	attackOwnTroops = rand() % 15;
	attackEnemyTroops = rand() % 15;
	// Start troop weights between 0.0 and 1.0
	attackOwnTroopsWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
	attackEnemyTroopsWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
	contBonusWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
}

// Function to pre-evolve the ATTACK decision parameters
void GeneticAlgorithm::preEvolveAttack(int generations, int popSize, double mutationProb)
{
	// Lots of temp vars
	bool attackWon = false, firstGen = true;
	int troopsLost = 0;
	vector<vector<int>> troopVals(popSize, vector<int>(2, 0)), bestTroopVals(popSize / 4, vector<int>(2, 0));
	vector<vector<double>> weightVals(popSize, vector<double>(3, 0)), bestWeightVals(popSize / 4, vector<double>(3, 0));

	// Create a variety of Region pairs on which to train
	vector<vector<Region>> trainingRegions(10, vector<Region>(2, Region(0, "Alaska", vector<int>{1, 3, 24})));
	for (int i = 0; i < 10; ++i) {
		trainingRegions[i][0] = Region(0, "Alaska", vector<int>{1, 3, 24});
		trainingRegions[i][0].addTroops(rand() % 35 + 1);
		trainingRegions[i][1] = Region(1, "Northwest_Territory", vector<int>{0, 3, 4, 2});
		trainingRegions[i][1].addTroops(rand() % 35 + 1);
	}

	// Will run for i generations
	for (int i = 0; i < generations; ++i) {
		// Create the initial population
		if (firstGen) {
			for (int i = 0; i < popSize; ++i) {
				troopVals[i][0] = rand() % 15;
				troopVals[i][1] = rand() % 15;
				weightVals[i][0] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[i][1] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[i][2] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
			}
		}
		// Attack with current weights

		// Calculate fitness

		// Perform cloning on best 25% of the population
		int j = 1, h = 1;
		for (int i = 0; i < bestTroopVals.size(); ++i) {
			// Each value will be cloned 4 times
			troopVals[i][0] = bestTroopVals[i][0]; 
			troopVals[i][1] = bestTroopVals[i][1]; 
			troopVals[i + j][0] = bestTroopVals[i][0]; 
			troopVals[i + j][1] = bestTroopVals[i][1]; ++j;
			troopVals[i + j][0] = bestTroopVals[i][0]; 			
			troopVals[i + j][1] = bestTroopVals[i][1]; ++j;
			troopVals[i + j][0] = bestTroopVals[i][0]; 
			troopVals[i + j][1] = bestTroopVals[i][1]; ++j;

			weightVals[i][0] = bestWeightVals[0][i];
			weightVals[i][1] = bestWeightVals[0][i];
			weightVals[i][2] = bestWeightVals[0][i]; 

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i];
			weightVals[i + h][2] = bestWeightVals[0][i]; ++h;

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i];
			weightVals[i + h][2] = bestWeightVals[0][i]; ++h;

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i];
			weightVals[i + h][2] = bestWeightVals[0][i]; ++h;
		}

		// Perform mutation on all but the parents
		for (int i = 0; i < popSize / 25; ++i) {
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) < mutationProb)) {
				// Adds a random number between [-2, 2]
				troopVals[i][0] += rand() % 2 - 2;
				troopVals[i][1] += rand() % 2 - 2;
				// Adds a random number between [-0.1, 0.1]
				weightVals[i][0] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				weightVals[i][1] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				weightVals[i][2] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			}
		}
	}
}
