#include "GeneticAlgorithm.h"

// Constructor, randomizes all decision factors
GeneticAlgorithm::GeneticAlgorithm(Brisk* game)
{
	this->game = game;
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
	vector<vector<int>> troopVals, bestTroopVals;
	vector<vector<double>> weightVals, bestWeightVals;
	
	// Will run for i generations
	for (int i = 0; i < generations; ++i) {
		// Create the initial population
		if (firstGen) {
			for (int i = 0; i < popSize; ++i) {
				troopVals[0][i] = rand() % 15;
				troopVals[1][i] = rand() % 15;
				weightVals[0][i] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[1][i] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[1][i] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
			}
		}

		// Attack with current weights

		// Calculate fitness

		// Perform cloning on best 25% of the population
		for (int i = 0; i < popSize / 75; ++i) {
			// Each value will be cloned 4 times
			troopVals[0][i + popSize / 75] = bestTroopVals[0][i];
			troopVals[0][i + popSize / 50] = bestTroopVals[0][i];
			troopVals[0][i + popSize / 25] = bestTroopVals[0][i];
			troopVals[0][i] = bestTroopVals[0][i];

			troopVals[1][i + popSize / 75] = bestTroopVals[0][i];
			troopVals[1][i + popSize / 50] = bestTroopVals[0][i];
			troopVals[1][i + popSize / 25] = bestTroopVals[0][i];
			troopVals[1][i] = bestTroopVals[0][i];

			weightVals[0][i + popSize / 75] = bestWeightVals[0][i];
			weightVals[0][i + popSize / 50] = bestWeightVals[0][i];
			weightVals[0][i + popSize / 25] = bestWeightVals[0][i];
			weightVals[0][i] = bestWeightVals[0][i];

			weightVals[1][i + popSize / 75] = bestWeightVals[0][i];
			weightVals[1][i + popSize / 50] = bestWeightVals[0][i];
			weightVals[1][i + popSize / 25] = bestWeightVals[0][i];
			weightVals[1][i] = bestWeightVals[0][i];

			weightVals[2][i + popSize / 75] = bestWeightVals[0][i];
			weightVals[2][i + popSize / 50] = bestWeightVals[0][i];
			weightVals[2][i + popSize / 25] = bestWeightVals[0][i];
			weightVals[2][i] = bestWeightVals[0][i];
		}
		
		// Perform mutation on all but the parents
		for (int i = 0; i < popSize / 25; ++i) {
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) < mutationProb)) {
				// Adds a random number between [-2, 2]
				troopVals[0][i] += rand() % 2 - 2;
				troopVals[1][i] += rand() % 2 - 2;
				// Adds a random number between [-0.1, 0.1]
				weightVals[0][i] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				weightVals[1][i] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				weightVals[2][i] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			}
		}
	}
}
