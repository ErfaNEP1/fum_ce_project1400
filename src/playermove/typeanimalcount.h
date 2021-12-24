int searchTypeanimalposition(char player[], int worldsize, struct Cell board[][worldsize], struct Animal animalposition[]) {
    int n = 0;
    for (int i = 0;i < worldsize;i ++) {
        for (int j = 0;j < worldsize;j ++) {
            if (strcmp(board[i][j].identifierPlace,player) == 0) {

                 animalposition[n].x = i;
                 animalposition[n].y = j;
                 n ++;

            }
        }
    }
    return (n);
}