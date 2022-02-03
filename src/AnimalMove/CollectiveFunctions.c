/**
 * gets the minimum amount of energy needed to do anything (Move, Attack, Reproduct, etc)
 * 
 * @param {Genome-gene} character's genome.
 * 
 * @return {void}
 */
int minenergy(struct Genome gene)
{
    int MinEnergy = 600;
    if (gene.energyForMoving < MinEnergy)
    {
        MinEnergy = gene.energyForMoving;
    }
    if (gene.energyForReproduction < MinEnergy)
    {
        MinEnergy = gene.energyForReproduction;
    }
    if (gene.attackPower < MinEnergy)
    {
        MinEnergy = gene.attackPower;
    }
    if (gene.defensePower < MinEnergy)
    {
        MinEnergy = gene.defensePower;
    }
    return MinEnergy;
}
/**
 * move the animal in a direction
 * 
 * @param {int-winSwitch} pointer to global winSwitch, we change it to 1 if the character reached Heaven.
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * @param {char-animal} the animal to move
 * @param {int-x} animal's current x coordinate
 * @param {int-y} animal's current y coordinate
 * @param {int-xx} animal's dest x coordinate
 * @param {int-yy} animal's dest y coordinate
 * @param {Animal-animalposition[]} array of allied animals in game.
 * @param {int-i} index of animal in animal position array
 * @param {int-Mcells} number of cells that is possible to move in one round according to genome
 * 
 * @return {void}
 */
void move(int **winSwitch, int worldSize, struct Cell board[][worldSize], char animal[], int x, int y, int xx, int yy, struct Animal animalposition[], int i, int Mcells)
{
    Cell animalCell = {
        .typePlace = "animal",
        .identifierPlace = *animal};
    Cell defaultCell = {
        .typePlace = "default",
        .foodPlace.energy = 0,
        .identifierPlace = "."};
    //enemy won the game
    if (*board[xx][yy].identifierPlace == 'H')
    {
        **winSwitch = 1;
    }
    //enemy moved
    board[xx][yy] = animalCell;
    board[x][y] = defaultCell;
    animalposition[i].x = xx;
    animalposition[i].y = yy;
    animalposition[i].energyPoint -= (Mcells * animalposition[i].gene.energyForMoving);
}
/**
 * kills the character and make it a food
 * 
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * @param {int-x} animal's current x coordinate
 * @param {int-y} animal's current y coordinate
 * @param {int-energy} animal's current energy.
 * @param {Cell-foodcell[]} array of food cells in world.
 * @param {int-foodcount} number of cells that contain food
 * 
 * @return {void}
 */
void animalDeath(int worldsize, struct Cell board[][worldsize], int x, int y, int energy, struct Cell foodcell[], int **foodcount)
{

    textcolor(14);
    printf("Animal %s(%d,%d) died\n", board[x][y].identifierPlace, x, y);

    struct Cell defaultCell = {
        .typePlace = "default",
        .foodPlace.energy = 0,
        .identifierPlace = "."};
    struct Cell foodCell = {
        .typePlace = "food",
        .identifierPlace = "F"};
    // if energy of allied animal=0 it should save as default not food
    if (energy > 0)
    {

        board[x][y] = foodCell;
        board[x][y].foodPlace.energy = energy;
        foodcell[**foodcount].x = x;
        foodcell[**foodcount].y = y;
        ++**foodcount;
    }
    else
    {
        board[x][y] = defaultCell;
    }

    return;
}
/**
 * deletes the character from world and reinitialize array
 * 
 * @param {int-positionofallied} index of dead character in array.
 * @param {Animal-animalposition[]} character array.
 * @param {int-animalcount} count of animals in that array
 * 
 * @return {void}
 */
void delete_animal(int positionofallied, struct Animal animalposition[], int **animalcount)
{
    for (int k = positionofallied; k < (**animalcount) - 1; k++)
    {
        animalposition[k] = animalposition[k + 1];
    }
    (**animalcount)--;
    return;
}
/**
 * deletes the food from world and reinitialize array
 * 
 * @param {int-x} food x coordinate
 * @param {int-y} food y coordinate
 * @param {Cell-FoodCell[]} array of food cells in world.
 * @param {int-foodcount} number of cells that contain food
 * 
 * @return {void}
 */
void delete_Food(int x, int y, struct Cell FoodCell[], int **Foodcount)
{
    int i;
    for (i = 0; i < (**Foodcount); i++)
    {
        if (FoodCell[i].x == x && FoodCell[i].y == y)
            break;
    }
    for (int k = i; k < (**Foodcount) - 1; k++)
    {
        FoodCell[k] = FoodCell[k + 1];
    }
    (**Foodcount)--;
    return;
}
/**
 * returns index of character in a cell
 * 
 * @param {int-x} x coordinate
 * @param {int-y} y coordinate
 * @param {Animal-animal[]} animal array from world struct.
 * @param {int-animalcount} number of cells that contain specific animal type
 * 
 * @return {number} index of character in animal array
 */
int searchanimal(int x, int y, struct Animal animal[], int animalcount)
{
    int i;
    for (i = 0; i < (animalcount); i++)
    {
        if (animal[i].x == x && animal[i].y == y)
            return i;
    }
    return -1;
}
/**
 * returns number of specific characters
 * 
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * @param {char-player} character type.
 * 
 * @return {number} character count
 */
int countAnimalType(int worldSize, struct Cell board[][worldSize], char player[])
{
    int count = 0;
    for (int i = 0; i < worldSize; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            if (strcmp(board[i][j].identifierPlace, player) == 0)
            {
                count++;
            }
        }
    }
    return count;
}

int checkNeighborPlaces(int worldsize, struct Cell board[][worldsize], int x, int y) {
    int Neighbors[8][2] = {
        {-1,-1},
        {-1,0},
        {-1,1},
        {0,1},
        {1,1},
        {1,0},
        {1,-1},
    };
    for (int i = 0;i < 8;i ++) {
        int xx = x+Neighbors[i][0];
        int yy = y+Neighbors[i][1];
        if (strcmp(board[xx][yy].identifierPlace,"animal") == 0) return 0;
    }
    return 1;
}