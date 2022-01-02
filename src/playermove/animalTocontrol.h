enum
{
  KEY_ESC     = 27,
  ARROW_UP    = 72,
  ARROW_DOWN  = 80,
  ARROW_LEFT  = 75,
  ARROW_RIGHT = 77,
  ARROW_LEFTUP  = 71,
  ARROW_LEFTDOWN  = 79,
  ARROW_RIGHTUP  = 73,
  ARROW_RIGHTDOWN  = 81
};

int get_code()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        return getch();

    return getch();
}

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
    printf("Maximum number for moving :%d\n",cellsToMove);
    printf("Enter number :");
    int Mcells;
    scanf("%d",&Mcells);
    while(Mcells<=0 || Mcells>cellsToMove){
        printf("It's wrong.\nEnter another number :");
        scanf("%d",&Mcells);
    }
    

    switch (clickedKey)
    {
    case ARROW_UP:
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
                    break;
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
                for(int j=1; j<Mcells; j++){
                    if(*board[x - j][y].identifierPlace == 'F'){
                        board[x - j][y] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x - j][y].foodPlace.energy ;
                    }
                }
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

    case ARROW_DOWN:
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
                    break;
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
                for(int j=1; j<Mcells; j++){
                    if(*board[x + j][y].identifierPlace == 'F'){
                        board[x + j][y] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x + j][y].foodPlace.energy ;
                    }
                }
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

    case ARROW_RIGHT:
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
                    break;
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
                for(int j=1; j<Mcells; j++){
                    if(*board[x][y + j].identifierPlace == 'F'){
                        board[x][y + j] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x][y + j].foodPlace.energy ;
                    }
                }
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

    case ARROW_LEFT:
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
                    break;
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
                for(int j=1; j<Mcells; j++){
                    if(*board[x][y - j].identifierPlace == 'F'){
                        board[x][y - j] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x][y - j].foodPlace.energy ;
                    }
                }
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
    case ARROW_LEFTUP:
        if (y - Mcells >= 0 && x - Mcells >= 0)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x-k][y - k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
                else if (*board[x-k][y - k].identifierPlace == 'H')
                {

                    board[x-k][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;
                    alliedanimalposition[i].x-= k;

                    printf("move to LefttoUp");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x-k][y - k].identifierPlace) && *board[x-k][y - k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x-k][y - k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            if(sw==1)
            {
                for(int j=1; j<Mcells; j++){
                    if(*board[x - j][y - j].identifierPlace == 'F'){
                        board[x - j][y - j] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x - j][y - j].foodPlace.energy ;
                    }
                }
                board[x - Mcells][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y-= Mcells;
                alliedanimalposition[i].x-= Mcells;

                printf("move to LefttoUp");
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
   case ARROW_RIGHTUP:
        if (y + Mcells < worldsize && x - Mcells >= 0)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x-k][y + k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
                else if (*board[x-k][y + k].identifierPlace == 'H')
                {

                    board[x-k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;
                    alliedanimalposition[i].x-= k;

                    printf("move to RighttoUp");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x-k][y + k].identifierPlace) && *board[x-k][y + k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x-k][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            if(sw==1)
            {
                for(int j=1; j<Mcells; j++){
                    if(*board[x - j][y + 1].identifierPlace == 'F'){
                        board[x - j][y + 1] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x - j][y + 1].foodPlace.energy ;
                    }
                }
                board[x - Mcells][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;
                alliedanimalposition[i].x-= Mcells;

                printf("move to RighttoUp");
                printf("\n");
            }
        }
            
        else {
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;
   case ARROW_RIGHTDOWN:
        if (y + Mcells < worldsize && x + Mcells < worldsize)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x+k][y + k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
                else if (*board[x+k][y + k].identifierPlace == 'H')
                {

                    board[x+k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;
                    alliedanimalposition[i].x+= k;

                    printf("move to RighttoDown");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x+k][y + k].identifierPlace) && *board[x+k][y + k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x+k][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            if(sw==1)
            {
                for(int j=1; j<Mcells; j++){
                    if(*board[x + j][y + 1].identifierPlace == 'F'){
                        board[x + j][y + 1] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                    }
                }
                board[x + Mcells][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;
                alliedanimalposition[i].x+= Mcells;

                printf("move to RighttoDown");
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
    case ARROW_LEFTDOWN:
        if (x + Mcells < worldsize && y - Mcells >= 0)
        {
            for(int k=1; k<=Mcells; k++){
                if (*board[x + k][y-k].identifierPlace == '#')
                {

                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
                else if (*board[x + k][y-k].identifierPlace == 'H')
                {

                    board[x + k][y-k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;
                    alliedanimalposition[i].x+= k;

                    printf("move to LefttoDown");
                    printf("\n");
                    sw=0;
                    *winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x + k][y-k].identifierPlace) && *board[x + k][y-k].identifierPlace != 'F')
                {
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y-k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
            }
            if(sw==1)
            {
                for(int j=1; j<Mcells; j++){
                    if(*board[x + j][y - j].identifierPlace == 'F'){
                        board[x + j][y - j] = defaultCell ;
                        alliedanimalposition[i].energyPoint += board[x + j][y - j].foodPlace.energy ;
                    }
                }
                board[x + Mcells][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x+=Mcells;
                alliedanimalposition[i].y-=Mcells;

                printf("move to LefttoDown");
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
        printf("\n");
        i --;
        break;
    }

    return i;
}