enum
{
    KEY_ESC = 27,
    ARROW_UP = 72,
    ARROW_DOWN = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77,
    ARROW_LEFTUP = 71,
    ARROW_LEFTDOWN = 79,
    ARROW_RIGHTUP = 73,
    ARROW_RIGHTDOWN = 81
};

// get Arrow code
int get_code()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        return getch();

    return getch();
}

int animalTocontrol(int **winSwitch, char player[], int worldsize, struct Cell board[][worldsize], int i, struct Animal alliedanimalposition[], int clickedKey, struct Cell Foodcell[], int *foodcount, int *alliedcount)
{
    Genome *AGptr;
    AGptr = &alliedanimalposition[i].gene;
    int x, y;
    x = alliedanimalposition[i].x;
    y = alliedanimalposition[i].y;
    int sw = 1;
    Cell foodCell = {
        .typePlace = "food",
        .identifierPlace = "F"};
    Cell animalTocontrolcell = {
        .typePlace = "animal",
        .identifierPlace = *player};
    Cell defaultCell = {
        .typePlace = "default",
        .foodPlace.energy = 0,
        .identifierPlace = "."};

    //========preparation for PlayerMove============//
    textcolor(1);
    printf("you control player %s (%d,%d)\n", player, alliedanimalposition[i].x + 1, alliedanimalposition[i].y + 1);
    printf("energy = %d\n", alliedanimalposition[i].energyPoint);

    //to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die 
    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
    {
        //animal died

        //if energy of allied animal=0 it should save as default not food
        if (alliedanimalposition[i].energyPoint > 0)
        {

            board[x][y] = foodCell;
            board[x][y].foodPlace.energy = alliedanimalposition[i].energyPoint;
            Foodcell[*foodcount].x = x;
            Foodcell[*foodcount].y = y;
            *foodcount++;
        }
        else
        {
            board[x][y] = defaultCell;
        }
        textcolor(14);
        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
        delete_allied(i, alliedanimalposition, &alliedcount);
        return i-1;
    }

    printf("Maximum number for moving : %d\n", AGptr->cellsToMove);
    printf("Enter number : ");
    int Mcells, TemporaryEnergy = alliedanimalposition[i].energyPoint;
    scanf("%d", &Mcells);
    while (Mcells <= 0 || Mcells > AGptr->cellsToMove)
    {
        textcolor(12);
        printf("It's wrong.\n");
        textcolor(1);
        printf("Enter another number :");
        scanf("%d", &Mcells);
    }
    //========End of preparation for PlayerMove============//

    switch (clickedKey)
    {
        // player want to move Up
    case ARROW_UP:
        if (x - Mcells >= 0)
        {
            // checked the places of board for Mcells move
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x - k][y].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x - k][y].identifierPlace == 'H')
                {
                    //player won the game
                    board[x - k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x -= k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x - k][y].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x - k][y].foodPlace.energy;
                }
                else if (isalpha(*board[x - k][y].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
            }
            // player can move Mcells to Up
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food enegy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x - j][y].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x - j][y].foodPlace.energy;
                            board[x - j][y] = defaultCell;
                        }
                    }
                    // player moved
                    board[x - Mcells][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x -= Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x - Mcells][y] = foodCell;
                            board[x - Mcells][y].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x - Mcells;
                            Foodcell[*foodcount].y = y;
                            *foodcount++;
                        }
                        else
                        {
                            board[x - Mcells][y] = defaultCell;
                        }
                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go Up (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x + k][y].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;
                    break;
                }
                else if (*board[x + k][y].identifierPlace == 'H')
                {

                    //player won the game
                    board[x + k][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x += k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x + k][y].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x + k][y].foodPlace.energy;
                }
                else if (isalpha(*board[x + k][y].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
            }
            // player can move Mcells to Down
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food enegy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x + j][y].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x + j][y].foodPlace.energy;
                            board[x + j][y] = defaultCell;
                        }
                    }
                    //player moved
                    board[x + Mcells][y] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x += Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x + Mcells][y] = foodCell;
                            board[x + Mcells][y].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x + Mcells;
                            Foodcell[*foodcount].y = y;
                            *foodcount++;
                        }
                        else
                        {
                            board[x + Mcells][y] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go Down (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x][y + k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x][y + k].identifierPlace == 'H')
                {

                    //player von the game
                    board[x][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x][y + k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x][y + k].foodPlace.energy;
                }
                else if (isalpha(*board[x][y + k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y + k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;
                    break;
                }
            }
            //player can move Mcells to Right
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x][y + j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x][y + j].foodPlace.energy;
                            board[x][y + j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x][y + Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {

                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x][y + Mcells] = foodCell;
                            board[x][y + Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x;
                            Foodcell[*foodcount].y = y + Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x][y + Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go Right (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x][y - k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x][y - k].identifierPlace == 'H')
                {
                    //player von the game
                    board[x][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y -= k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x][y - k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x][y - k].foodPlace.energy;
                }
                else if (isalpha(*board[x][y - k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x][y - k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
            }
            //player can move Mcells to Left
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x][y - j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x][y - j].foodPlace.energy;
                            board[x][y - j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x][y - Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y -= Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x][y - Mcells] = foodCell;
                            board[x][y - Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x;
                            Foodcell[*foodcount].y = y - Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x][y - Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go Left (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x - k][y - k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x - k][y - k].identifierPlace == 'H')
                {

                    //player won the game
                    board[x - k][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y -= k;
                    alliedanimalposition[i].x -= k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x - k][y - k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x - k][y - k].foodPlace.energy;
                }
                else if (isalpha(*board[x - k][y - k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y - k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
            }
            //player can move Mcells to LeftTUp
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x - j][y - j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x - j][y - j].foodPlace.energy;
                            board[x - j][y - j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x - Mcells][y - Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y -= Mcells;
                    alliedanimalposition[i].x -= Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x - Mcells][y - Mcells] = foodCell;
                            board[x - Mcells][y - Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x - Mcells;
                            Foodcell[*foodcount].y = y - Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x - Mcells][y - Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go LeftTUp (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x - k][y + k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x - k][y + k].identifierPlace == 'H')
                {

                    //player won the game
                    board[x - k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += k;
                    alliedanimalposition[i].x -= k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x - k][y + k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x - k][y + k].foodPlace.energy;
                }
                else if (isalpha(*board[x - k][y + k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y + k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;
                    break;
                }
            }
            //player can move Mcells to RightTUp
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x - j][y + j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x - j][y + j].foodPlace.energy;
                            board[x - j][y + j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x - Mcells][y + Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += Mcells;
                    alliedanimalposition[i].x -= Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x - Mcells][y + Mcells] = foodCell;
                            board[x - Mcells][y + Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x - Mcells;
                            Foodcell[*foodcount].y = y + Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x - Mcells][y + Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }

        else
        {
            // player can't Go RightTUp (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x + k][y + k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x + k][y + k].identifierPlace == 'H')
                {

                    //player won the game
                    board[x + k][y + k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += k;
                    alliedanimalposition[i].x += k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x + k][y + k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x + k][y + k].foodPlace.energy;
                }
                else if (isalpha(*board[x + k][y + k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y + k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;
                    break;
                }
            }
            //player can move Mcells to RightTDown
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x + j][y + j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x + j][y + j].foodPlace.energy;
                            board[x + j][y + j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x + Mcells][y + Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y += Mcells;
                    alliedanimalposition[i].x += Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x + Mcells][y + Mcells] = foodCell;
                            board[x + Mcells][y + Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x + Mcells;
                            Foodcell[*foodcount].y = y + Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x + Mcells][y + Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go RightTDown (go out of board)
            textcolor(12);
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
            for (int k = 1; k <= Mcells; k++)
            {

                if (*board[x + k][y - k].identifierPlace == '#')
                {
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (#)");
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
                else if (*board[x + k][y - k].identifierPlace == 'H')
                {

                    //player won the game
                    board[x + k][y - k] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].y -= k;
                    alliedanimalposition[i].x += k;

                    printf("\n");
                    sw = 0;
                    **winSwitch = 1;
                    printf("\n");
                    break;
                }
                else if (*board[x + k][y - k].identifierPlace == 'F')
                {
                    TemporaryEnergy += board[x + k][y - k].foodPlace.energy;
                }
                else if (isalpha(*board[x + k][y - k].identifierPlace))
                {
                    //in this place exist an animal
                    textcolor(12);
                    printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y - k].identifierPlace);
                    printf("\n");
                    sw = 0;
                    i--;

                    break;
                }
            }
            //player can move Mcells to LeftTDown
            if (sw == 1)
            {
                //check energy of player
                if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                {
                    //add Food energy to player
                    for (int j = 1; j <= Mcells; j++)
                    {
                        if (*board[x + j][y - j].identifierPlace == 'F')
                        {
                            alliedanimalposition[i].energyPoint += board[x + j][y - j].foodPlace.energy;
                            board[x + j][y - j] = defaultCell;
                        }
                    }
                    //player moved
                    board[x + Mcells][y - Mcells] = animalTocontrolcell;
                    board[x][y] = defaultCell;
                    alliedanimalposition[i].x += Mcells;
                    alliedanimalposition[i].y -= Mcells;
                    //decreased energy
                    alliedanimalposition[i].energyPoint -= (Mcells * AGptr->energyForMoving);

                    //to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                    {
                        //animal died

                        //if energy of allied animal=0 it should save as default not food
                        if (alliedanimalposition[i].energyPoint > 0)
                        {

                            board[x + Mcells][y - Mcells] = foodCell;
                            board[x + Mcells][y - Mcells].foodPlace.energy = alliedanimalposition[i].energyPoint;
                            Foodcell[*foodcount].x = x + Mcells;
                            Foodcell[*foodcount].y = y - Mcells;
                            *foodcount++;
                        }
                        else
                        {
                            board[x + Mcells][y - Mcells] = defaultCell;
                        }

                        textcolor(14);
                        printf("Animal %s(%d,%d) died", player, alliedanimalposition[i].x, alliedanimalposition[i].y);
                        delete_allied(i, alliedanimalposition, &alliedcount);
                        i--;
                    }

                    printf("\n");
                }
                // player don't have enough energy(moving)
                else
                {
                    textcolor(12);
                    printf("YOU DON'T HAVE ENOUGH ENERGY FOR %d MOVING", Mcells);
                    printf("\n");
                    i--;
                    break;
                }
            }
        }
        else
        {
            // player can't Go LeftTDown (go out of board)
            textcolor(12);
            printf("YOU CAN'T GO THERE !");
            printf("\n");
            i--;
        }
        break;

    default:
        //pressed the wrong Key
        i--;
        break;
    }

    return i;
}