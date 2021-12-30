int searchTypeanimalposition(char player[], int worldsize, struct Cell board[][worldsize], struct Animal alliedanimalposition[],Animal enemyanimalposition[]) {
    int nPlayer = 0, nEnemy = 0;
    for (int i = 0;i < worldsize;i ++) {
        for (int j = 0;j < worldsize;j ++) {
            if (strcmp(board[i][j].typePlace,"animal") == 0) {
               if (strcmp(board[i][j].identifierPlace,player) == 0) {

                   alliedanimalposition[nPlayer].x = i;
                   alliedanimalposition[nPlayer].y = j;
                   nPlayer ++;

                }
                else {
                    enemyanimalposition[nEnemy].x = i;
                    enemyanimalposition[nEnemy].y = j;
                    enemyanimalposition[nEnemy].pointindex = -1;
                    nEnemy ++;
                }
            }
        }
    }
    return (nPlayer);
}