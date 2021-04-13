# CS5073-Large-Project

## GA Design:

Genome:
   * Array of parameters to evolve

Evolutionary Process:
   * Evolve individual attack parameters first with preset scenarios
   * Evolve troop placement & movement individual parameters

Fitness Evaluation:
   * Attacking fitness will be based mainly on attack success against
     scenarios we will set. Each parameter will be evolved separately
   * Troop placement and movement will then be evaluated based on the 
     previously evolved attack parameters; i.e. how troop placement/movement 
	   affects a subsequent attack. There should also be some way to make
	   sure troop placement/movement does not neglect poorly reinforced regions.
   * We are also considering testing our final GA against another Risk-playing bot,
     https://github.com/cathal-killeen/risk-bot
