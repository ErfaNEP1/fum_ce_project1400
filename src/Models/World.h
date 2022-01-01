typedef struct World
{
    int size;
    int deadEndCount, heavenCount, foodCount, animalCount, alliedCount, enemyCount;
    char animalToControl[2];
    char winner[2];
    Cell deadEnds[100];
    Cell heavenCell[100];
    Cell foodCell[100];
    Animal alliedanimalposition[100];
    Animal enemyanimalposition[100];
} World;

void initWorld(struct World world, int worldSize, struct Cell board[][worldSize])
{
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."
    };
    
    for (int i = 0; i < worldSize; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            board[i][j] = defaultCell;
        }
    }
}

void printWorld(int worldSize, struct Cell board[][worldSize], int index, struct World world)
{
    for (int i = 0; i < worldSize; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            if (*board[i][j].identifierPlace == 'F')
                textcolor(4);
            else if (*board[i][j].identifierPlace == 'H')
                textcolor(6);
            else if (*board[i][j].identifierPlace == '#')
                textcolor(8);
            else if (*board[i][j].identifierPlace == '.')
                textcolor(2);
            else if (i == world.alliedanimalposition[index].x && j == world.alliedanimalposition[index].y)
                textcolor(3);
            else
                textcolor(7);

            printf("%s ", board[i][j].identifierPlace);
        }
        printf("\n");
    }
}
void printWorldDetails(World world)
{
    printf("Animal count : %d\n", world.animalCount);
    printf("DeadEnd count : %d\n", world.deadEndCount);
    printf("HeavenCell count : %d\n", world.heavenCount);
    printf("Food count : %d\n", world.foodCount);
}
void printFoodsDetails(int worldSize, struct Cell board[][worldSize])
{
    for (int i = 0; i < worldSize; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            if (strcmp(board[i][j].typePlace, "animal") == 0)
            {
                printf("ANIMAL %s (%d,%d) \n", board[i][j].identifierPlace, board[i][j].animalPlace.energyPoint,board[i][j].animalPlace.gene.attackPower) ;
            }
        }
    }
}
void giveCharactersGenome(Genome gene,char player[], int worldsize, struct Cell board[][worldsize], int energyPoint){
    for (int i = 0; i < worldsize; i++)
    {
        for (int j = 0; j < worldsize; j++)
        {
            if (strcmp(board[i][j].identifierPlace, player) == 0)
            {
                board[i][j].animalPlace.energyPoint = energyPoint;
                board[i][j].animalPlace.gene = gene;
            }
        }
    }
}
