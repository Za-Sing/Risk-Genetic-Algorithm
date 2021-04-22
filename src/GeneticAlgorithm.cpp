#include "GeneticAlgorithm.h"


using namespace std;
//function for random dice rolls
int GeneticAlgorithm::rollDie()
{
	int roll;
	roll = rand() % 6 + 1; //six sided die roll
	return roll;
}

bool GeneticAlgorithm::divByFour(string s) {
	int len = s.length();
	// If there is single digit
	if (len == 1)
		return ((s[0] - '0') % 4 == 0);
	// If number formed by last two digits is divisible by 4.
	int last = s[len - 1] - '0';
	int secondLast = s[len - 2] - '0';
	return ((secondLast * 10 + last) % 4 == 0);
}

bool sortcol(const vector<double>& v1, const vector<double>& v2) {
	return v1[2] < v2[2];
}

// Constructor, randomizes all decision factors
GeneticAlgorithm::GeneticAlgorithm()
{
	// Start troop weights between 0.0 and 1.0
	troopRatioWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
	contBonusWeight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
}


// Function to pre-evolve the ATTACK decision parameters.
// NOTE: population size MUST be divisible by 4 in order for proper selection, cloning and mutation to occur.
void GeneticAlgorithm::preEvolveAttack(int generations, int popSize, double mutationProb)
{
	srand(time(NULL));
	
	// Lots of temp vars
	bool attackWon = false, firstGen = true;
	// First col is troopWeight, second col is contWeight. Last column in these vectors will be the fitness score for the (whole) individual.
	vector<vector<double>> weightVals(popSize, vector<double>(3, 0)), bestWeightVals(popSize / 4, vector<double>(3, 0));
	// First column is win bool, second column is troops used / troops returned
	vector<vector<double>> results(popSize, vector<double>(2, 0));  
	// A vector to hold the top ten best values over all generations
	vector<vector<double>> globalBest(10, vector<double>(3, 0));

	// Create a variety of Region pairs on which to train. trainingRegions[i][0] is the owned Region, trainingRegions[i][1] is the enemy Region
	vector<vector<Region>> trainingRegions(1000, vector<Region>(2, Region(0, "Alaska", vector<int>{1, 3, 24})));
	for (int i = 0; i < 1000; ++i) {
		trainingRegions[i][0] = Region(0, "Alaska", vector<int>{1, 3, 24});
		trainingRegions[i][0].addTroops(rand() % 35 + 2);
		trainingRegions[i][1] = Region(1, "Northwest_Territory", vector<int>{0, 3, 4, 2});
		trainingRegions[i][1].addTroops(rand() % 35 + 1);
	}

	// Will run for g generations
	for (int g = 0; g < generations; ++g) {
		printf("/*****GENERATION %d*****\\\n", g);
		// Create the initial population
		if (firstGen) {
			for (int i = 0; i < popSize; ++i) {
				weightVals[i][0] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));
				weightVals[i][1] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0));	
			}
		}

		// Attack with current parameters
		vector<double> temp = vector<double>();
		for (int i = 0; i < popSize; ++i) {
			temp = gaAttack(trainingRegions.at(rand() % (trainingRegions.size() - 1)).at(0), trainingRegions.at(rand() % (trainingRegions.size() - 1)).at(1), 
							weightVals[i][0], weightVals[i][1]);  
			results[i][0] = temp[0];
			results[i][1] = temp[1];
		}

		// Calculate fitness. Fitness is determined by 1 - (return troops / sent troops)
		for (int i = 0; i < popSize; ++i) {
			// If the attack was won
			if (results[i][0] == 1.0) {
				weightVals[i][2] = results[i][1];
			}
			if (results[i][0] == 0.0) {
				weightVals[i][2] = 0; 
			}
		}

		// DEBUG
		printf("Population and fitness: \n");
		for (int i = 0; i < popSize; ++i) {
			printf("%d: %f %f %f\n", i, weightVals[i][0], weightVals[i][1], weightVals[i][2]);
		}

		// Select the best 25% of the population
		// Sort the population based on the whole individual's fitness
		sort(weightVals.begin(), weightVals.end(), sortcol);
		for (int i = 0; i < popSize / 4; ++i) {
			bestWeightVals[i][0] = weightVals[popSize - 1 - i][0];
			bestWeightVals[i][1] = weightVals[popSize - 1 - i][1];
			bestWeightVals[i][2] = weightVals[popSize - 1 - i][2];
		}

		// Collect the best ten results and update them if necessary on future generations
		if (firstGen) {
			for (int i = 0; i < 10; ++i) {
				globalBest[i][0] = bestWeightVals[(popSize / 4) - 1 - i][0];
				globalBest[i][1] = bestWeightVals[(popSize / 4) - 1 - i][1];
				globalBest[i][2] = bestWeightVals[(popSize / 4) - 1 - i][2];
			}
			firstGen = false;
		}
		else {
			for (int i = 0; i < popSize / 4; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (bestWeightVals[i][2] > globalBest[j][2]) {
						globalBest[j][0] = bestWeightVals[i][0];
						globalBest[j][1] = bestWeightVals[i][1];
						globalBest[j][2] = bestWeightVals[i][2];
					}
				}
			}
		}

		// DEBUG
		/*printf("Best 25%: \n");
		for (int i = 0; i < popSize / 4; ++i) {
			printf("%d: %f %f\n", i, bestWeightVals[i][0], bestWeightVals[i][1]);
		}*/

		// Perform cloning on best 25% of the population
		int h = 0;
		for (int i = 0; i < popSize / 4; ++i) {
			// Each value will be cloned 4 times
			weightVals[i + h][0] = bestWeightVals[i][0];
			weightVals[i + h][1] = bestWeightVals[i][1];
			weightVals[i + h][2] = bestWeightVals[i][2]; ++h;

			weightVals[i + h][0] = bestWeightVals[i][0];
			weightVals[i + h][1] = bestWeightVals[i][1]; 
			weightVals[i + h][2] = bestWeightVals[i][2]; ++h;
			
			weightVals[i + h][0] = bestWeightVals[i][0];
			weightVals[i + h][1] = bestWeightVals[i][1]; 
			weightVals[i + h][2] = bestWeightVals[i][2]; ++h;
			
			weightVals[i + h][0] = bestWeightVals[i][0];
			weightVals[i + h][1] = bestWeightVals[i][1];
			weightVals[i + h][2] = bestWeightVals[i][2];
		}

		// DEBUG
		/*printf("Cloned population\n");
		for (int i = 0; i < popSize; ++i) {
			printf("%d: %f %f\n", i, weightVals[i][0], weightVals[i][1]);
		}*/

		// Perform mutation on all but the parents
		for (int i = 0; i < popSize; ++i) {
			// Skip the 25% of the population that is the parents.
			if (divByFour(to_string(i + 4))) {
				continue;
			}
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) <= mutationProb)) {
				// Adds a random number between [-0.1, 0.1]
				double randVal = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				if (weightVals[i][0] + randVal >= 0.0 && weightVals[i][0] + randVal <= 1.0) {
					weightVals[i][0] += randVal;
				}
			}
			if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) <= mutationProb)) {
				// Adds a random number between [-0.1, 0.1]
				double randVal = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.1 - 0.1));
				if (weightVals[i][1] + randVal >= 0.0 && weightVals[i][1] + randVal <= 1.0) {
					weightVals[i][1] += randVal;
				}
			}
		}

		// DEBUG
		/*printf("Mutated population\n");
		for (int i = 0; i < popSize; ++i) {
			printf("%d: %f %f\n", i, weightVals[i][0], weightVals[i][1]);
		}*/
		printf("\\**********************/\n");
	}
	//DEBUG
	printf("GLOBAL BEST 10: \n");
	for (int i = 0; i < 10; ++i) {
		printf("%d: %f %f %f\n", i, globalBest[i][0], globalBest[i][1], globalBest[i][2]);
	}
}

void GeneticAlgorithm::gaAttack()
{

}

// This function is for use in pre-training. It simulates an attack sequence and then returns a boolean and the ratio of troops lost
vector<double> GeneticAlgorithm::gaAttack(Region ownRegion, Region enemyRegion, double troopRatioWeight, double contBonusWeight)
{
	bool bonus = false, attackWon = false;
	double attackability = 0, troopLostRatio = 0, continueProb = 0.7;
	vector<double> returnValue(2, 0);
	// Randomly set troop numbers and whether or not a successful attack would complete a cont bonus
	int ownTroops = ownRegion.getTroops(), enemyTroops = enemyRegion.getTroops();
	int attack[3];
	int defend[2];
	if ((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1.0)) <= 0.5)) {
		bonus = true;
	}

	// Calculate attackability score
	attackability = ((double) ownTroops / (double)enemyTroops) * troopRatioWeight;
	if (bonus) {
		attackability + contBonusWeight;
	}
	printf("Attackability: %f\n", attackability);


	int ogOwnTroops = ownTroops;
	int ogEnemyTroops = enemyTroops;
	// Decide if an attack will take place
	if (attackability >= 1.0) {
		while(ownTroops > 1 && enemyTroops > 0){

			//initialize empty dice
			for (int i = 0; i < 2; i++) {
				attack[i] = 0;
				defend[i] = 0;
			}
			attack[2] = 0;

			int attackingTroops = 3;

			if (ownTroops == 3) {
				attackingTroops = 2;
			}
			else if (ownTroops == 2) {
				attackingTroops = 1;
			}


			int defendingTroops = 2;

			if (enemyTroops == 1) {
				defendingTroops = 1;
			}

			// Get attacker dice rolls
			for (int i = 0; i < attackingTroops; i++) {
				attack[i] = rollDie();
			}

			// Get defender dice rolls
			for (int i = 0; i < defendingTroops; i++) {
				defend[i] = rollDie();
			}

			//compare max dice

			int attackLoss = 0;
			int defendLoss = 0;

			int n = sizeof(attack) / sizeof(attack[0]);
			int m = sizeof(defend) / sizeof(defend[0]);

			sort(attack, attack + n);
			sort(defend, defend + m);

			if (attack[2] > defend[1]) {
				defendLoss++;
				enemyTroops--;
			}
			else {
				attackLoss++;
				ownTroops--;
			}

			if (attackingTroops == 2 || attackingTroops == 3) {
				if (defendingTroops == 2) {
					if (attack[1] > defend[0]) {
						defendLoss++;
						enemyTroops--;
					}
					else {
						attackLoss++;
						ownTroops--;
					}
				}
			}

		}

		//pushback return value with 1 if win, 0 if loss
		if (enemyTroops == 0) {
			returnValue[0] = 1.0;
		}
		else {
			returnValue[0] = 0.0;
		}

		//pushback return value with remaining troops / original troops
		returnValue[1] = (double) ownTroops / (double) ogOwnTroops;

		return returnValue;
	}
	else {
		return { -1.0, -1.0 };
	}
}
