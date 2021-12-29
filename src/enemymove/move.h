void revrese(struct Point pointTomove[], int number) {
    int i, j;

    for (i = 0,j = number-2;j > i;i ++,j --) {

        int tempX = pointTomove[i].x;
        int tempY = pointTomove[i].y;
        pointTomove[i].x = pointTomove[j].x;
        pointTomove[i].y = pointTomove[j].y;
        pointTomove[j].x = tempX;
        pointTomove[j].y = tempY;
    }
    return;
}

int check(int worldSize, struct Cell board[][worldSize] , int x, int y){
    if( strcmp (board[x][y].typePlace, "animal")==0){
        return 0;
    }
    else return 1;
}