void animalTocontrol(char player[], int n, int worldsize, struct Cell board[][worldsize]) {
    Cell animalTocontrolcell = {
        .typePlace = "animal",
        .identifierPlace = *player
    };
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."
    };

    for (int i = 0;i < n;i ++) {
        int x, y, j;

        for (x = 0, j = i;x < worldsize && j >= 0;x ++) {
            for (y = 0;y <worldsize;y ++) {
                if (strcmp(board[x][y].identifierPlace,player) == 0) j --;
                if (j < 0) break;
            }
        }
        x--;
        printf("you control player(%s%d)\n",player,i);

        char ch = getch();
        if (ch == 0 || ch == 224) {

            switch (getch()) {
                case 72:
                if (x-1 >= 0) {
                    if (*board[x-1][y].identifierPlace == '#') {

                        printf("you can't go hear (#)");
                        printf("\n");
                        i --;
                        break;

                    }
                    else if (*board[x-1][y].identifierPlace == 'H') {

                        board[x-1][y] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Up");
                        printf("\n");
                        printf("you win");
                        printf("\n");

                    }
                    else if (isalpha(*board[x-1][y].identifierPlace) && *board[x-1][y].identifierPlace != 'F') {
                        printf("you can't go hear (%s)",board[x-1][y].identifierPlace);
                        printf("\n");
                        i --;
                        break;
                    }
                    else {
                        board[x-1][y] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Up");
                        printf("\n");
                        
                    }
                }
                else {
                    printf("you can't go hear");
                    printf("\n");
                    i--;
                }
                    break;

                case 80:
                if (x+1 < worldsize) {
                    if (*board[x+1][y].identifierPlace == '#') {

                        printf("you can't go hear (#)");
                        printf("\n");
                        i --;
                        break;

                    }
                    else if (*board[x+1][y].identifierPlace == 'H') {

                        board[x+1][y] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Down");
                        printf("\n");
                        printf("you win");
                        printf("\n");

                    }
                    else if (isalpha(*board[x+1][y].identifierPlace) && *board[x+1][y].identifierPlace != 'F') {
                        printf("you can't go hear (%s)",board[x+1][y].identifierPlace);
                        printf("\n");
                        i --;
                        break;
                    }
                    else {
                        board[x+1][y] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Down");
                        printf("\n");
                        
                    }
                }
                else {
                    printf("you can't go hear");
                    printf("\n");
                    i--;
                }
                    break;

                case 77:
                if (y+1 < worldsize) {
                    if (*board[x][y+1].identifierPlace == '#') {

                        printf("you can't go hear (#)");
                        printf("\n");
                        i --;
                        break;

                    }
                    else if (*board[x][y+1].identifierPlace == 'H') {

                        board[x][y+1] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Right");
                        printf("\n");
                        printf("you win");
                        printf("\n");

                    }
                    else if (isalpha(*board[x][y+1].identifierPlace) && *board[x][y+1].identifierPlace != 'F') {
                        printf("you can't go hear (%s)",board[x][y+1].identifierPlace);
                        printf("\n");
                        i --;
                        break;
                    }
                    else {
                        board[x][y+1] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Right");
                        printf("\n");
                        
                    }
                }
                else {
                    printf("you can't go hear");
                    printf("\n");
                    i--;
                }
                    break;

                case 75:
                if (y-1 >= 0) {
                    if (*board[x][y-1].identifierPlace == '#') {

                        printf("you can't go hear (#)");
                        printf("\n");
                        i --;
                        break;

                    }
                    else if (*board[x][y-1].identifierPlace == 'H') {

                        board[x][y-1] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Left");
                        printf("\n");
                        printf("you win");
                        printf("\n");

                    }
                    else if (isalpha(*board[x][y-1].identifierPlace) && *board[x][y-1].identifierPlace != 'F') {
                        printf("you can't go hear (%s)",board[x][y-1].identifierPlace);
                        printf("\n");
                        i --;
                        break;
                    }
                    else {
                        board[x][y-1] = animalTocontrolcell;
                        board[x][y] = defaultCell;

                        printf("move to Left");
                        printf("\n");
                        
                    }
                }
                else {
                    printf("you can't go hear");
                    printf("\n");
                    i--;

                }
                    break;

                default:
                    break;

            }
        }
    }
}