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

void delete_animal(int positionofallied, struct Animal animalposition[], int **animalcount)
{
    for (int k = positionofallied; k < (**animalcount) - 1; k++)
    {
        animalposition[k] = animalposition[k + 1];
    }
    (**animalcount)--;
    return;
}

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