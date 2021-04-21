#include "GeneticAlgorithm.h"

bool sortcol(const vector<double>& v1,
	const vector<double>& v2) {
	return v1[2] < v2[2];
}

// Constructor, randomizes all decision factors
GeneticAlgorithm::GeneticAlgorithm()
{
	srand(time(NULL));

	// Start troop weights between 0.0 and 1.0
	troopRatioWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
	contBonusWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
}


// Function to pre-evolve the ATTACK decision parameters
void GeneticAlgorithm::preEvolveAttack(int generations, int popSize, double mutationProb)
{
	// Lots of temp vars
	bool attackWon = false, firstGen = true;
	// First col is troopWeight, second col is contWeight. Last column in these vectors will be the fitness score for the (whole) individual.
	vector<vector<double>> weightVals(popSize, vector<double>(3, 0)), bestWeightVals(popSize / 4, vector<double>(2, 0));
	// First column is win bool, second column is troops used / troops returned
	vector<vector<double>> results(popSize, vector<double>(2, 0));  

	// Create a variety of Region pairs on which to train. trainingRegions[i][0] is the owned Region, trainingRegions[i][1] is the enemy Region
	vector<vector<Region>> trainingRegions(10, vector<Region>(2, Region(0, "Alaska", vector<int>{1, 3, 24})));
	for (int i = 0; i < 10; ++i) {
		trainingRegions[i][0] = Region(0, "Alaska", vector<int>{1, 3, 24});
		trainingRegions[i][0].addTroops(rand() % 35 + 1);
		trainingRegions[i][1] = Region(1, "Northwest_Territory", vector<int>{0, 3, 4, 2});
		trainingRegions[i][1].addTroops(rand() % 35 + 1);
	}

	// Will run for g generations
	for (int g = 0; g < generations; ++g) {
		// Create the initial population
		if (firstGen) {
			for (int i = 0; i < popSize; ++i) {
				weightVals[i][0] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[i][1] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));			}
			firstGen = false;
		}

		// Attack with current parameters
		vector<double> temp = vector<double>();
		for (int i = 0; i < popSize; ++i) {
			temp = gaAttack(trainingRegions.at(rand() % (trainingRegions.size() - 1)).at(0), trainingRegions.at(rand() % (trainingRegions.size() - 1)).at(1), 
							weightVals[i][0], weightVals[i][1]);  
			results[i][0] = temp[0];
			results[i][1] = temp[1];
		}

		// Calculate fitness. Fitness is determined by 1 - (sent troops / return troops)
		for (int i = 0; i < popSize; ++i) {
			// If the attack was won
			if (results[i][0] == 1) {
				weightVals[i][2] = 1 - results[i][1];
			}
			else {
				weightVals[i][2] = 0;
			}
		}

		// Select the best 25% of the population
		// Sort the population based on the whole individual's fitness
		sort(weightVals.begin(), weightVals.end(), sortcol);
		for (int i = popSize - 1; i >= popSize * 3/4 - 1; --i) {
			bestWeightVals[i][0] = weightVals[i][0];
			bestWeightVals[i][1] = weightVals[i][1];
		}

		// Perform cloning on best 25% of the population
		int j = 1, h = 1;
		for (int i = 0; i < popSize / 4; ++i) {
			// Each value will be cloned 4 times
			weightVals[i][0] = bestWeightVals[0][i];
			weightVals[i][1] = bestWeightVals[0][i];

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i]; ++h;

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i]; ++h;

			weightVals[i + h][0] = bestWeightVals[0][i];
			weightVals[i + h][1] = bestWeightVals[0][i]; ++h;
		}

		// Perform mutation on all but the parents
		for (int i = 0; i < popSize / 25; ++i) {
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) < mutationProb)) {
				// Adds a random number between [-0.1, 0.1]
				weightVals[i][0] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			}
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) < mutationProb)) {
				// Adds a random number between [-0.1, 0.1]
				weightVals[i][1] += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
			}
		}
	}
}

void GeneticAlgorithm::gaAttack()
{

}

vector<double> GeneticAlgorithm::gaAttack(Region ownRegion, Region enemyRegion, double troopRatioWeight, double contBonusWeight)
{
	bool bonus = false, attackWon = false;
	double attackability = 0, troopLostRatio = 0, continueProb = 0.7;
	// Randomly set troop numbers and whether or not a successful attack would complete a cont bonus
	int ownTroops = rand() % 35 + 2, enemyTroops = rand() % 35 + 1;
	if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) < 0.5)) {
		bonus = true;
	}

	// Calculate attackability score
	attackability = (ownTroops / (double)enemyTroops) * troopRatioWeight;
	if (bonus) {
		attackability + contBonusWeight;
	}

	// Decide if an attack will take place
	if (attackability >= 40.0) {
		return vector<double>();
	}
	else {
		return { 0.0, 0.0 };
	}
}
