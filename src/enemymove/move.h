int FindtheClosestWaytoH(int enemyX, int enemyY, struct Cell heavencell[], int heavencount)
{
    int dis, mindis = 40, mukhtasat;
    for (int i = 0; i < heavencount; i++)
    {
        dis = abs(enemyX - heavencell[i].x) + abs(enemyY - heavencell[i].y);
        if (dis < mindis)
        {
            mindis = dis;
            mukhtasat = i;
        }
    }
    return mukhtasat;
}

void reverse(struct Point pointTomove[], int number)
{
    int i, j;

    for (i = 0, j = number - 2; j > i; i++, j--)
    {

        int tempX = pointTomove[i].x;
        int tempY = pointTomove[i].y;
        pointTomove[i].x = pointTomove[j].x;
        pointTomove[i].y = pointTomove[j].y;
        pointTomove[j].x = tempX;
        pointTomove[j].y = tempY;
    }
    return;
}

int check(int worldSize, struct Cell board[][worldSize], int x, int y)
{
    if (strcmp(board[x][y].typePlace, "animal") == 0)
    {
        return 0;
    }
    else
        return 1;
}

void move(World world, int *winSwitch, int worldSize, struct Cell board[][worldSize], char enemy[], int x, int y, int xx, int yy, struct Animal enemyanimalposition[], int i)
{
    Cell enemyCell = {
        .typePlace = "animal",
        .identifierPlace = *enemy};
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};
    // if (xx > x)
    //     printf("enemy(%s(%d,%d)) move to Down", enemy, x, y);
    // if (xx < x)
    //     printf("enemy(%s(%d,%d)) move to Up", enemy, x, y);
    // if (yy > y)
    //     printf("enemy(%s(%d,%d)) move to Right", enemy, x, y);
    // if (yy < y)
    //     printf("enemy(%s(%d,%d)) move to Left", enemy, x, y);

    if (*board[xx][yy].identifierPlace == 'H')
    {
        *winSwitch = 1;
    }

    board[xx][yy] = enemyCell;
    board[x][y] = defaultCell;
    enemyanimalposition[i].x = xx;
    enemyanimalposition[i].y = yy;
    // printWorld(worldSize, board, 0, world);
}

int cellsToMove(struct Point pointTomove[], int pointindex, int Mcells, int n, int wordsize, struct Cell board[][wordsize], int enemyanimalpositionEnergy) {
    int p = pointindex;
    Cell defaultcell = {
        .typePlace = "default",
        .identifierPlace = "."};

        if (p == pointindex) {
            int i;
            for (i = 1; i < Mcells, pointindex+i < n, pointTomove[pointindex].x == pointTomove[pointindex+i].x;i ++) {
                 if (check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)) {
                     if (*board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].identifierPlace == 'F') {
                        enemyanimalpositionEnergy += board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                        board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                continue;
                }
                 else break;
            }
            p+i-1;
        }

        if (p == pointindex) {
            int i;
            for (i = 1; i < Mcells, pointindex+i < n, pointTomove[pointindex].y == pointTomove[pointindex+i].y;i ++) {
                 if (check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)) {
                     if (*board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].identifierPlace == 'F') {
                         enemyanimalpositionEnergy = board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                         board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                continue;
                }
                 else break;
            }
            p+i-1;
        }

        if(p == pointindex) {
            int i;
            for(i=1; i < Mcells, pointindex+i < n, pointTomove[pointindex].x +1 == pointTomove[pointindex + i].x, pointTomove[pointindex].y +1 == pointTomove[pointindex + i].y; i++){
                if(check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)){
                    if(*board[pointTomove[pointindex + i].x][pointTomove[pointindex +i].y].identifierPlace == 'F') {
                         enemyanimalpositionEnergy = board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                         board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                    continue;
                }
                else break;
            }
            p+i-1;
        }

        if(p == pointindex) {
            int i;
            for(i=1; i < Mcells, pointindex+i < n, pointTomove[pointindex].x -1 == pointTomove[pointindex + i].x, pointTomove[pointindex].y +1 == pointTomove[pointindex + i].y; i++){
                if(check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)){
                    if(*board[pointTomove[pointindex + i].x][pointTomove[pointindex +i].y].identifierPlace == 'F') {
                         enemyanimalpositionEnergy = board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                         board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                    continue;
                }
                else break;
            }
            p+i-1;
        }

        if(p == pointindex) {
            int i;
            for(i=1; i < Mcells, pointindex+i < n, pointTomove[pointindex].x +1 == pointTomove[pointindex + i].x, pointTomove[pointindex].y -1 == pointTomove[pointindex + i].y; i++){
                if(check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)){
                    if(*board[pointTomove[pointindex + i].x][pointTomove[pointindex +i].y].identifierPlace == 'F') {
                         enemyanimalpositionEnergy = board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                         board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                    continue;
                }
                else break;
            }
            p+i-1;
        }

        if(p == pointindex) {
            int i;
            for(i=1; i < Mcells, pointindex+i < n, pointTomove[pointindex].x -1 == pointTomove[pointindex + i].x, pointTomove[pointindex].y -1 == pointTomove[pointindex + i].y; i++){
                if(check(wordsize,board,pointTomove[pointindex+i].x,pointTomove[pointindex+i].y)){
                    if(*board[pointTomove[pointindex + i].x][pointTomove[pointindex +i].y].identifierPlace == 'F') {
                         enemyanimalpositionEnergy = board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y].foodPlace.energy;
                         board[pointTomove[pointindex+i].x][pointTomove[pointindex+i].y] = defaultcell;
                    }
                    continue;
                }
                else break;
            }
            p+i-1;
        }

    return p;
}