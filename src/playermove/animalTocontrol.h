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

// get Arrow code
int get_code()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        return getch();

    return getch();
}

int animalTocontrol(int **winSwitch,char player[], int n, int worldsize, struct Cell board[][worldsize], int x, int y, int i, struct Animal alliedanimalposition[], int clickedKey, int cellsToMove)
{
    int sw=1;
    Cell animalTocontrolcell = {
        .typePlace = "animal",
        .identifierPlace = *player};
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};

    //========preparation for PlayerMove============//
    printf("you control player(%s%d)\n", player, i);
    printf("energy = %d\n",alliedanimalposition[i].energyPoint);
    printf("Maximum number for moving :%d\n",cellsToMove);
    printf("Enter number :");
    int Mcells;
    scanf("%d",&Mcells);
    while(Mcells<=0 || Mcells>cellsToMove){
        printf("It's wrong.\nEnter another number :");
        scanf("%d",&Mcells);
    }
    //========End of preparation for PlayerMove============//

    switch (clickedKey)
    {
        // player want to move Up
    case ARROW_UP:
        if (x - Mcells >= 0)
        {
            // checked the places of board for Mcells move
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
                    //player won the game
                    board[x - k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x-= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x - k][y].identifierPlace) && *board[x - k][y].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
            }
            // player can move Mcells to Up
            if(sw==1)
            {
                //add Food enegy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x - j][y].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x - j][y] = defaultCell ;

                    }
                }
                // player moved
                board[x - Mcells][y] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x-=Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go Up (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

        // player want to move Down
    case ARROW_DOWN:
        if (x + Mcells < worldsize)
        {
            // checked the places of board for Mcells move
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
                    
                    //player won the game
                    board[x + k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x+= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x + k][y].identifierPlace) && *board[x + k][y].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            // player can move Mcells to Down
            if(sw==1)
            {
                //add Food enegy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x + j][y].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x + j][y] = defaultCell ;

                    }
                }
                //player moved
                board[x + Mcells][y] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x+= Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go Down (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;
    //player want to move Right
    case ARROW_RIGHT:
        if (y + Mcells < worldsize)
        {
            // checked the places of board for Mcells move
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

                    //player von the game
                    board[x][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x][y + k].identifierPlace) && *board[x][y + k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            //player can move Mcells to Right
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x][y + j].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x][y + j] = defaultCell ;

                    }
                }
                //player moved
                board[x][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go Right (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;
    //player want to move Left
    case ARROW_LEFT:
        if (y - Mcells >= 0)
        {
            // checked the places of board for Mcells move
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
                    //player von the game
                    board[x][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x][y - k].identifierPlace) && *board[x][y - k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y - k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            //player can move Mcells to Left
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x][y - j].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x][y - j] = defaultCell ;

                    }
                }
                //player moved
                board[x][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y-= Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go Left (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    //player want to move LeftTUp
    case ARROW_LEFTUP:
        if (y - Mcells >= 0 && x - Mcells >= 0)
        {
            // checked the places of board for Mcells move
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

                    //player won the game
                    board[x-k][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;
                    alliedanimalposition[i].x-= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x-k][y - k].identifierPlace) && *board[x-k][y - k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x-k][y - k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;

                    break;
                }
            }
            //player can move Mcells to LeftTUp
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x - j][y - j].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x - j][y - j] = defaultCell ;

                    }
                }
                //player moved
                board[x - Mcells][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y-= Mcells;
                alliedanimalposition[i].x-= Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go LeftTUp (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    //player want to move RightTUp
   case ARROW_RIGHTUP:
        if (y + Mcells < worldsize && x - Mcells >= 0)
        {
            // checked the places of board for Mcells move
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

                    //player won the game
                    board[x-k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;
                    alliedanimalposition[i].x-= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x-k][y + k].identifierPlace) && *board[x-k][y + k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x-k][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            //player can move Mcells to RightTUp
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x - j][y + 1].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x - j][y + 1] = defaultCell ;

                    }
                }
                //player moved
                board[x - Mcells][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;
                alliedanimalposition[i].x-= Mcells;

                printf("\n");
            }
        }
            
        else {
            // player can't Go RightTUp (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    //player want to move RightTDown
   case ARROW_RIGHTDOWN:
        if (y + Mcells < worldsize && x + Mcells < worldsize)
        {
            // checked the places of board for Mcells move
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

                    //player won the game
                    board[x+k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y+= k;
                    alliedanimalposition[i].x+= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x+k][y + k].identifierPlace) && *board[x+k][y + k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x+k][y + k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    break;

                }
            }
            //player can move Mcells to RightTDown
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x + j][y + 1].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x + j][y + 1] = defaultCell ;

                    }
                }
                //player moved
                board[x + Mcells][y + Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].y+= Mcells;
                alliedanimalposition[i].x+= Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go RightTDown (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    //player want to move LeftTDown
    case ARROW_LEFTDOWN:
        if (x + Mcells < worldsize && y - Mcells >= 0)
        {
            // checked the places of board for Mcells move
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

                    //player won the game
                    board[x + k][y-k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y-= k;
                    alliedanimalposition[i].x+= k;

                    printf("\n");
                    sw=0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (isalpha(*board[x + k][y-k].identifierPlace) && *board[x + k][y-k].identifierPlace != 'F')
                {
                    //in this place exist an animal
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y-k].identifierPlace);
                    printf("\n");
                    sw=0;
                    i--;
                    
                    break;
                }
            }
            //player can move Mcells to LeftTDown
            if(sw==1)
            {
                //add Food energy to player
                for(int j=1; j<=Mcells; j++){
                    if(*board[x + j][y - j].identifierPlace == 'F'){
                        alliedanimalposition[i].energyPoint += board[x + j][y + 1].foodPlace.energy ;
                        board[x + j][y - j] = defaultCell ;

                    }
                }
                //player moved
                board[x + Mcells][y - Mcells] = animalTocontrolcell;
                board[x][y] = defaultCell;
                alliedanimalposition[i].x+=Mcells;
                alliedanimalposition[i].y-=Mcells;

                printf("\n");
            }
        }
        else
        {
            // player can't Go LeftTDown (go out of board)
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;


    default:
        //pressed the wrong Key 
        i --;
        break;
    }

    return i;
}