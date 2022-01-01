int searchTypeanimalposition(World world,char player[], int worldsize, struct Cell board[][worldsize], struct Animal alliedanimalposition[],Animal enemyanimalposition[]) {
    int nPlayer = 0, nEnemy = 0;
    for (int i = 0;i < worldsize;i ++) {
        for (int j = 0;j < worldsize;j ++) {
            if (strcmp(board[i][j].typePlace,"animal") == 0) {
               if (strcmp(board[i][j].identifierPlace,player) == 0) {

                   alliedanimalposition[nPlayer].x = i;
                   alliedanimalposition[nPlayer].y = j;
                   alliedanimalposition[nPlayer].gene = board[i][j].animalPlace.gene;
                   nPlayer ++;

                }
                else {
                    enemyanimalposition[nEnemy].x = i;
                    enemyanimalposition[nEnemy].y = j;
                    enemyanimalposition[nEnemy].pointindex = -1;
                    enemyanimalposition[nEnemy].gene = board[i][j].animalPlace.gene;
                    nEnemy ++;
                }
            }
        }
    }
    world.alliedCount = nPlayer;
    world.enemyCount = nEnemy;

    return (nPlayer);
}