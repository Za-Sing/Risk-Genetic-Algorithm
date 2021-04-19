#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include "Region.h"

class GeneticAlgorithm
{
private:

	// For ATTACK decision process
	int attackOwnTroops;
	int attackEnemyTroops;
	double attackOwnTroopsWeight;
	double attackEnemyTroopsWeight;
	bool contributeContBonus;
	double contBonusWeight;

	// For TROOP PLACEMENT decision process
	//blank 4 now

	// For TROOP MOVEMENT decision process
	//blank 4 now

public:
	GeneticAlgorithm();
	void preEvolveAttack(int generations, int popSize, double mutationProb);
	void gaAttack();
	vector<double> gaAttack(int attackOwnTroops, int attackEnemyTroops, double attackOwnTroopsWeight,
		double attackEnemyTroopsWeight, double contBonusWeight);
};

#endif // !GENETICALGORITHM_H
