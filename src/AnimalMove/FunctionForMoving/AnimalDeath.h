void animalDeath(int worldsize, struct Cell board[][worldsize],int x, int y, int energy, struct Cell foodcell[], int **foodcount)
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
        textcolor(2);
    }
    else
    {
        board[x][y] = defaultCell;
    }

    return;
}