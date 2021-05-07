# CS5073-Large-Project

## GA Design:

Genome:
   * Array of parameters to evolve.

Evolutionary Process:
   * Evolve individual attack parameters first with randomized simulated scenarios.
   * Evolve troop placement individual parameters with randomized scenarios.

Fitness Evaluation:
   * Attacking fitness will be based mainly on attack success against.
     scenarios randomly. Each parameter will be evolved separately.
   * Troop placement will then be evaluated based on the 
     previously evolved attack parameters; i.e. how troop placement 
	   affects a subsequent attack. The parameters will also make
	   sure troop placement does not neglect poorly reinforced regions.
   
Running the Program:
   * We used Microsoft Visual Studio to manage and build our project.
   * Creating a VS project and manually adding the files seems to be the best way to do this.
   * We have not tested simply using gcc or a Makefile on Mac/Linux but we see no reason this would not work.
   * Playing the game is admittedly a bit opaque; all the Regions are entered as their ID ints on the command line.
           The board vector in Brisk.cpp shows each Region's ID for reference. Otherwise, playing with all bots will run by itself.
