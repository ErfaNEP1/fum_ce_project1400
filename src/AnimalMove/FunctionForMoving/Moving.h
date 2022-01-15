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
    printf("Fnal Energy = %d\n",animalposition[i].energyPoint);
}