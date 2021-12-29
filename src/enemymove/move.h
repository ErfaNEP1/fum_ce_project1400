int moveChech(int worldsize, struct Cell board[][worldsize], int enemyX, int enemyY, struct Point pointTomove[], int index) {

    if (index == -1) index = 0;
    int x = enemyX + pointTomove[index].x;
    int y = enemyY + pointTomove[index].y;

    if (strcmp(board[x][y].identifierplace,"animal") != 0) return 1;
    else return 0;
}