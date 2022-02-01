// Input Data From File
void inputDeadEnds(int worldSize, char *tok, World *world, Cell board[][worldSize]);
void inputHeavens(int worldSize, char *tok, World *world, Cell board[][worldSize]);
void inputFood(int worldSize, char *tok, World *world, Cell board[][worldSize]);
void inputAnimals(int worldSize, char *tok, World *world, Cell board[][worldSize]);
void inputGenome(int worldSize, char *tok, World *world, Cell board[][worldSize]);
// End Input Data

// World Print
void initWorld(struct World world, int worldSize, struct Cell board[][worldSize]);
void printWorld(int worldSize, struct Cell board[][worldSize], int index, struct World world);
void printWorldDetails(World world);

// Save Info
int saveAnimalinfo(World *world, char player[], int worldsize, struct Cell board[][worldsize], struct Animal alliedanimalposition[], Animal enemyanimalposition[]);
void giveCharactersGenome(Genome gene, char player[], int worldsize, struct Cell board[][worldsize], int energyPoint);