/**
 * checks if a cell contains animal or not
 * 
 * @param {int-worldSize} size of map
 * @param {Cell-board[]} world map
 * @param {int-x} x coordinate;
 * @param {int-y} y coordinate;
 * @return {int-bool} 0 : no , 1 : yes
 */
int check(int worldSize, struct Cell board[][worldSize], int x, int y)
{
    if (strcmp(board[x][y].typePlace, "animal") == 0)
    {
        return 0;
    }
    else
        return 1;
}