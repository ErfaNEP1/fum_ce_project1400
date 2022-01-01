int animalTocontrol(int *winSwitch,char player[], int n, int worldsize, struct Cell board[][worldsize], int x, int y, int i, struct Animal alliedanimalposition[], int clickedKey, int cellsToMove)
{
    int sw=1;
    Cell animalTocontrolcell = {
        .typePlace = "animal",
        .identifierPlace = *player};
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};

    printf("you control player(%s%d)\n", player, i);
    printf("Maximum number for moving:%d\n",cellsToMove);
    printf("Enter number");
    int Mcells;
    do{
        scanf("%d",&Mcells);
    }while(Mcells>cellsToMove || Mcells<=0);

    switch (clickedKey)
    {
    case 72:
        if (x - Mcells >= 0)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x - k][y].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
                else if (*board[x - k][y].identifierPlace == 'H')
                {

                    board[x - k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x-= k;

                    printf("move to Up");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                }
                else if (isalpha(*board[x - k][y].identifierPlace) && *board[x - k][y].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
            }
            if(sw==1)
            {
                board[x - Mcells][y] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x-=Mcells;

                printf("move to Up");
                printf("\n");
            }
        }
        else
        {
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    case 80:
        if (x + Mcells < worldsize)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x + k][y].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    break;
                }
                else if (*board[x + k][y].identifierPlace == 'H')
                {

                    board[x + k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x+= k;

                    printf("move to Down");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                }
                else if (isalpha(*board[x + k][y].identifierPlace) && *board[x + k][y].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            if(sw==1)
            {
                board[x + Mcells][y] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x+= Mcells;

                printf("move to Down");
                printf("\n");
            }
        }
        else
        {
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    case 77:
        if (y + Mcells < worldsize)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x][y + k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
                else if (*board[x][y + k].identifierPlace == 'H')
                {

                    board[x][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;

                    printf("move to Right");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                }
                else if (isalpha(*board[x][y + k].identifierPlace) && *board[x][y + k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            if(sw==1)
            {
                board[x][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;

                printf("move to Right");
                printf("\n");
            }
        }
        else
        {
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    case 75:
        if (y - Mcells >= 0)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x][y - k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
                else if (*board[x][y - k].identifierPlace == 'H')
                {

                    board[x][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;

                    printf("move to Left");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                }
                else if (isalpha(*board[x][y - k].identifierPlace) && *board[x][y - k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y - k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            if(sw==1)
            {
                board[x][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y-= Mcells;

                printf("move to Left");
                printf("\n");
            }
        }
        else
        {
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    default:

        printf("default");
        break;
    }

    return i;
}