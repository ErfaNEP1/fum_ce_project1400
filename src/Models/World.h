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
        .identifierPlace = "."};

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
            if (strcmp(board[i][j].typePlace, "food") == 0)
            {
                printf("food(%d,%d) : %d\n", i, j, board[i][j].foodPlace.energy);
            }
        }
    }
}
