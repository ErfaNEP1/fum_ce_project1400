void findplace(int worldSize, Cell **board[][worldSize], int xMother, int yMother, int xFather, int yFather, char identifier[], Animal **alliedanimalposition[], int AlliedCount)
{
    Cell animalcell = {
        .typePlace = "animal",
        .identifierPlace = *identifier,
        .animalPlace.pointindex = 0};

    int mindis = (worldSize * worldSize), xnewEnemy = -1, ynewEnemy = -1;
    for (int i = 0; i < worldSize; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            int disM = (abs(xMother - i) + abs(yMother - j));
            int disF = (abs(xFather - i) + abs(yFather - j));
            if (disM < mindis && strcmp(board[i][j]->typePlace, "default") == 0)
            {
                mindis = disM;
                xnewEnemy = i;
                ynewEnemy = j;
            }
            if (disF < mindis && strcmp(board[i][j]->typePlace, "default") == 0)
            {
                mindis = disF;
                xnewEnemy = i;
                ynewEnemy = j;
            }
        }
    }
    board[xnewEnemy][ynewEnemy] = animalcell;
    board[xnewEnemy][ynewEnemy]->x = xnewEnemy;
    board[xnewEnemy][ynewEnemy]->y = ynewEnemy;
    alliedanimalposition[AlliedCount]->x = xnewEnemy;
    alliedanimalposition[AlliedCount]->y = ynewEnemy;
}

void reproduction(Animal *enemyMother, Animal *enemyFather, int AlliedCount, Animal *alliedanimalposition[], int worldSize, Cell *board[][worldSize])
{
    enemyMother->energyPoint -= (enemyMother->gene->energyForReproduction / 2);
    enemyFather->energyPoint -= (enemyFather->gene->energyForReproduction / 2);
    alliedanimalposition[AlliedCount]->energyPoint = enemyMother->maximumEnergy;
    alliedanimalposition[AlliedCount]->maximumEnergy = enemyMother->maximumEnergy;
    strcpy(alliedanimalposition[AlliedCount]->gene->character, enemyMother->gene->character);

    alliedanimalposition[AlliedCount]->gene->energyForMoving = random(20, 200);
    alliedanimalposition[AlliedCount]->gene->cellToMove = random(1, 3);
    alliedanimalposition[AlliedCount]->gene->energuForReproduction = random(60, 600);
    alliedanimalposition[AlliedCount]->gene->attackPower = random(20, 500);
    alliedanimalposition[AlliedCount]->gene->defensePower = random(20, 500);

    findplace(worldSize, *board, enemyMother->x, enemyMother->y, enemyFather->x, enemyFather->y, enemyMother->gene->character, *alliedanimalposition, AlliedCount);

    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->energyPoint = alliedanimalposition[AlliedCount]->energyPoint;
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->maximumEnergy = alliedanimalposition[AlliedCount]->maximumEnergy;
    strcpy(board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->character, alliedanimalposition[AlliedCount]->gene->character);
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->energyForMoving = alliedanimalposition[AlliedCount]->gene->energyForMoving;
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->cellToMove = alliedanimalposition[AlliedCount]->gene->cellToMove;
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->energuForReproduction = alliedanimalposition[AlliedCount]->gene->energuForReproduction;
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->attackPower = alliedanimalposition[AlliedCount]->gene->attackPower;
    board[alliedanimalposition[AlliedCount]->x][alliedanimalposition[AlliedCount]->y]->animalPlace->gene->defensePower = alliedanimalposition[AlliedCount]->gene->defensePower;
    AlliedCount++;
}

