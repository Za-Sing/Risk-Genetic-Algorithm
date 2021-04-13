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
void GeneticAlgorithm::preEvolveAttack(int generations)
{
	bool attackWon = false;
	double mutationProb = 0.0;
	int troopsLost = 0;
	// Will run for i generations
	for (int i = 0; i < generations; ++i) {
		// Attack with current weights

		// Calculate fitness

		// Perform mutation
		if (rand() < mutationProb) {
			// Adds a random number between [-2, 2]
			attackOwnTroops += rand() % 2 - 2;
			attackEnemyTroops += rand() % 2 - 2;
			// Adds a random number between [-0.1, 0.1]
			attackOwnTroopsWeight += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			attackEnemyTroopsWeight += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			contBonusWeight += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
		}
	}
}
