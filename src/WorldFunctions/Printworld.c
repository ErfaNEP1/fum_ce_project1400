// #include "Printworld.h"

/**
 * Filling the map with default cells before getting the input from file.
 * 
 * @param {World-world} game's database.
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * 
 * @return {void}
 */
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
/**
 * Prints Map
 * 
 * @param {int worldsize} size of the map.
 * @param {Cell board[][]} game's map.
 * @param {int index} the number of ally character to be highlited in map.
 * @param {World-world} game's database.
 * 
 * @return {void}
 */
void printWorld(int worldSize, struct Cell board[][worldSize], int index, struct World world)
{
    textcolor(13);
    printf("\n  START !!! ( Move With Arrow Keys.) ( DOUBLE CLICK ON \"ESC\" TO EXIT )\n\n- YOU CAN ALSO PLAY WITH NUMPAD FOR BETTER \n  NAVIGATION. TO DO SO, PLEASE TURN OFF YOUR NUMLOCK.\n- TO ATTACK ENEMIES, MOVE TO THEIR POSITION\n  WHEN YOU ARE NEXT TO THEM.\n- TO REPRODUCT MOVE TO YOUR ALLIED CHARACTER'S\n  POSITION WHEN YOU ARE NEXT TO THEM.\n- TO COOPERATE CLICK ON \"C\" IN START OF EACH ROUND\n");
    textcolor(6);
    printf("\n  YOUR CHARACTERS' STATS (ENERGY/ATTACK POWER/DEFENSE POWER/ENERGY TO REPRODUCE/ENERGY TO MOVE)\n");
    for (int i = 0; i < world.alliedCount; i++)
    {
        Animal animal = world.alliedanimalposition[i];
        printf("  %s (%d,%d) : %d/%d/%d/%d/%d\n",world.animalToControl,animal.x,animal.y,animal.energyPoint,animal.gene.attackPower,animal.gene.defensePower,animal.gene.energyForReproduction,animal.gene.energyForMoving);
    }
    for (int i = 0; i < world.enemyCount; i++)
    {
        Animal animal = world.enemyanimalposition[i];
        printf("  %s (%d,%d) : %d/%d/%d/%d/%d\n",board[animal.x][animal.y].identifierPlace,animal.x,animal.y,animal.energyPoint,animal.gene.attackPower,animal.gene.defensePower,animal.gene.energyForReproduction,animal.gene.energyForMoving);
    }
    

    goToXY(105,2);
    textcolor(7);
    printf("%c", 201);
    for (int i = 0; i < (worldSize * 2) + 1; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    goToXY(105,3);
    for (int i = 0; i < worldSize; i++)
    {
        textcolor(7);
        printf("%c ", 186);
        for (int j = 0; j < worldSize; j++)
        {
            int character = 254;
            if (*board[i][j].identifierPlace == 'F')
            {
                textcolor(4);
                character = 149;
            }
            else if (*board[i][j].identifierPlace == 'H')
            {
                textcolor(6);
                character = 254;
            }
            else if (*board[i][j].identifierPlace == '#')
            {
                textcolor(8);
            }
            else if (*board[i][j].identifierPlace == '.')
            {
                textcolor(2);
                character = 254;
            }
            else if (i == world.alliedanimalposition[index].x && j == world.alliedanimalposition[index].y)
            {
                textcolor(3);
                character = board[i][j].identifierPlace[0];
            }
            else
            {
                textcolor(7);
                character = board[i][j].identifierPlace[0];
            }
            printf("%c ", character);
        }
        textcolor(7);
        printf("%c ", 186);
        printf("\n");
        goToXY(105,4+i);
    }
    printf("%c", 200);
    for (int i = 0; i < (worldSize * 2) + 1; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}
