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
    // goToXY(70,0);
    textcolor(7);
    printf("%c",201);
    for (int i = 0; i < (worldSize*2)+1; i++)
    {
        printf("%c",205);
    }
    printf("%c\n",187);
    // goToXY(70,1);
    for (int i = 0; i < worldSize; i++)
    {
        textcolor(7);
        printf("%c ",186);
        for (int j = 0; j < worldSize; j++)
        {
            int character = 254;
            if (*board[i][j].identifierPlace == 'F'){
                textcolor(4);
                character = 149;
            }else if (*board[i][j].identifierPlace == 'H'){
                textcolor(6);
                character = 254;
            }else if (*board[i][j].identifierPlace == '#'){
                textcolor(8);
            }else if (*board[i][j].identifierPlace == '.'){
                textcolor(2);
                character = 254;
            }else if (i == world.alliedanimalposition[index].x && j == world.alliedanimalposition[index].y){
                textcolor(3);
                character = board[i][j].identifierPlace[0];
            }else{
                textcolor(7);
                character = board[i][j].identifierPlace[0];
            }
            printf("%c ",character);
        }
        textcolor(7);
        printf("%c ",186);
        printf("\n");
        // goToXY(70,2+i);
    }
    printf("%c",200);
    for (int i = 0; i < (worldSize*2)+1; i++)
    {
        printf("%c",205);
    }
    printf("%c\n",188);
}
