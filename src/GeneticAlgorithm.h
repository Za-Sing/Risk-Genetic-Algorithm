#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Brisk.h"

class GeneticAlgorithm
{
private:
	Brisk* game;

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
	GeneticAlgorithm(Brisk* game);
	void preEvolveAttack(int generations);
};

#endif // !GENETICALGORITHM_H
