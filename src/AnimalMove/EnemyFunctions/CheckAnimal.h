int check(int worldSize, struct Cell board[][worldSize], int x, int y)
{
    if (strcmp(board[x][y].typePlace, "animal") == 0)
    {
        return 0;
    }
    else
        return 1;
}