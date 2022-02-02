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
    ARROW_RIGHTDOWN = 81,
    ARROW_COOPERATION = 99
};

// get Arrow code
int get_code()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        return getch();

    return ch;
}

int animalTocontrol(int **winSwitch, char player[], int worldsize, struct Cell board[][worldsize], int i, struct Animal alliedanimalposition[], int clickedKey, struct Cell Foodcell[], int *foodcount, int *alliedcount, struct Animal enemyanimalposition[], int *enemycount)
{
    Genome *AGptr;
    AGptr = &alliedanimalposition[i].gene;
    int x, y;
    int Mcells, TemporaryEnergy = alliedanimalposition[i].energyPoint;
    char decision;
    x = alliedanimalposition[i].x;
    y = alliedanimalposition[i].y;
    int sw = 1;
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

    // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
    if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint && checkNeighborPlaces(worldsize, board, x, y))
    {
        // animal died
        animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
        delete_animal(i, alliedanimalposition, &alliedcount);
        return i - 1;
    }

    switch (clickedKey)
    {
        // player want to move Up
    case ARROW_UP:

        if (strcmp(board[x - 1][y].typePlace, "animal") == 0)
        {

            //=============Reproduct============//
            if (*board[x - 1][y].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) :\n ");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x - 1, y, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //=============Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x - 1, y, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x - 1][y].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x - k][y].identifierPlace == 'H' && TemporaryEnergy - (Mcells * AGptr->cellsToMove) >= 0)
                    {
                        // add Food enegy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y].foodPlace.energy;
                                delete_Food(x - j, y, Foodcell, &foodcount);
                                board[x - j][y] = defaultCell;
                            }
                        }
                        // player won the game
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
                    else if (strcmp(board[x - k][y].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
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
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food enegy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y].foodPlace.energy;
                                delete_Food(x - j, y, Foodcell, &foodcount);
                                board[x - j][y] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x - Mcells, y, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

        // player want to move Down
    case ARROW_DOWN:

        if (strcmp(board[x + 1][y].typePlace, "animal") == 0)
        {

            //=============Reproduct============//
            if (*board[x + 1][y].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x + 1, y, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //=============Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x + 1, y, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x + 1][y].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x + k][y].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food enegy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y].foodPlace.energy;
                                delete_Food(x + j, y, Foodcell, &foodcount);
                                board[x + j][y] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x + k][y].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
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
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food enegy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y].foodPlace.energy;
                                delete_Food(x + j, y, Foodcell, &foodcount);
                                board[x + j][y] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x + Mcells, y, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;
    // player want to move Right
    case ARROW_RIGHT:

        if (strcmp(board[x][y + 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x][y + 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x, y + 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x, y + 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x][y + 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x][y + k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x][y + j].foodPlace.energy;
                                delete_Food(x, y + j, Foodcell, &foodcount);
                                board[x][y + j] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x][y + k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x][y + k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;
                        break;
                    }
                }
                // player can move Mcells to Right
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x][y + j].foodPlace.energy;
                                delete_Food(x, y + j, Foodcell, &foodcount);
                                board[x][y + j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x, y + Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {

                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;
    // player want to move Left
    case ARROW_LEFT:

        if (strcmp(board[x][y - 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x][y - 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x, y - 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x, y - 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x][y - 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x][y - k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x][y - j].foodPlace.energy;
                                delete_Food(x, y - j, Foodcell, &foodcount);
                                board[x][y - j] = defaultCell;
                            }
                        }
                        // player won the game
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
                    else if (strcmp(board[x][y - k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x][y - k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;

                        break;
                    }
                }
                // player can move Mcells to Left
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x][y - j].foodPlace.energy;
                                delete_Food(x, y - j, Foodcell, &foodcount);
                                board[x][y - j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x, y - Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

    // player want to move LeftTUp
    case ARROW_LEFTUP:

        if (strcmp(board[x - 1][y - 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x - 1][y - 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x - 1, y - 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x - 1, y - 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x - 1][y - 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x - k][y - k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y - j].foodPlace.energy;
                                delete_Food(x - j, y - j, Foodcell, &foodcount);
                                board[x - j][y - j] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x - k][y - k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y - k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;

                        break;
                    }
                }
                // player can move Mcells to LeftTUp
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y - j].foodPlace.energy;
                                delete_Food(x - j, y - j, Foodcell, &foodcount);
                                board[x - j][y - j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x - Mcells, y - Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

        // player want to move RightTUp
    case ARROW_RIGHTUP:

        if (strcmp(board[x - 1][y + 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x - 1][y + 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x - 1, y + 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x - 1, y + 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x - 1][y + 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x - k][y + k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y + j].foodPlace.energy;
                                delete_Food(x - j, y + j, Foodcell, &foodcount);
                                board[x - j][y + j] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x - k][y + k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x - k][y + k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;
                        break;
                    }
                }
                // player can move Mcells to RightTUp
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x - j][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x - j][y + j].foodPlace.energy;
                                delete_Food(x - j, y + j, Foodcell, &foodcount);
                                board[x - j][y + j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x - Mcells, y + Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

        // player want to move RightTDown
    case ARROW_RIGHTDOWN:

        if (strcmp(board[x + 1][y + 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x + 1][y + 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x + 1, y + 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x + 1, y + 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x + 1][y + 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x + k][y + k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y + j].foodPlace.energy;
                                delete_Food(x + j, y + j, Foodcell, &foodcount);
                                board[x + j][y + j] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x + k][y + k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y + k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;
                        break;
                    }
                }
                // player can move Mcells to RightTDown
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y + j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y + j].foodPlace.energy;
                                delete_Food(x + j, y + j, Foodcell, &foodcount);
                                board[x + j][y + j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x + Mcells, y + Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

    // player want to move LeftTDown
    case ARROW_LEFTDOWN:

        if (strcmp(board[x + 1][y - 1].typePlace, "animal") == 0)
        {

            //==========Reproduct===========//
            if (*board[x + 1][y - 1].identifierPlace == *player)
            {
                textcolor(1);
                printf("Do you want to reproduce ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int Mother_num = searchanimal(x + 1, y - 1, alliedanimalposition, *alliedcount);
                    if (alliedanimalposition[i].energyPoint >= AGptr->energyForReproduction / 2 && alliedanimalposition[Mother_num].energyPoint >= alliedanimalposition[Mother_num].gene.energyForReproduction / 2)
                    {
                        Animal *Motherptr, *Fatherptr;
                        Fatherptr = &alliedanimalposition[i];
                        Motherptr = &alliedanimalposition[Mother_num];
                        reproduction(Motherptr, Fatherptr, alliedcount, alliedanimalposition, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR REPRODUCTION\n");
                        i--;
                        break;
                    }
                }
            }

            //===========Attack============//
            else
            {
                textcolor(1);
                printf("Do you want to attack ?\nif Yes enter (y) else enter (n) : \n");
                decision = getch();
                if (decision == 'y')
                {
                    int enemy_num = searchanimal(x + 1, y - 1, enemyanimalposition, *enemycount);
                    if (alliedanimalposition[i].energyPoint >= 3 * AGptr->energyForMoving)
                    {

                        Animal *attacker, *enemy;
                        attacker = &alliedanimalposition[i];
                        enemy = &enemyanimalposition[enemy_num];
                        attack(attacker, enemy, alliedanimalposition, enemyanimalposition, alliedcount, &i, enemycount, enemy_num, worldsize, board);
                        // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                            {
                                // animal died
                                animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                                delete_animal(i, alliedanimalposition, &alliedcount);
                                return i - 1;
                            }
                        break;
                    }
                    else
                    {
                        textcolor(12);
                        printf("DON'T HAVE EANOGH ENERGY FOR ATTACK\n");
                        i--;
                        break;
                    }
                }
            }
        }

        //=============Moving============//
        if (decision != 'y' || strcmp(board[x + 1][y - 1].typePlace, "animal") != 0)
        {
            textcolor(1);
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
                    else if (*board[x + k][y - k].identifierPlace == 'H' && TemporaryEnergy - (k * AGptr->energyForMoving) >= 0)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y - j].foodPlace.energy;
                                delete_Food(x + j, y - j, Foodcell, &foodcount);
                                board[x + j][y - j] = defaultCell;
                            }
                        }

                        // player won the game
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
                    else if (strcmp(board[x + k][y - k].typePlace, "animal") == 0)
                    {
                        // in this place exist an animal
                        textcolor(12);
                        printf("YOU CAN'T GO THERE ! (%s)", board[x + k][y - k].identifierPlace);
                        printf("\n");
                        sw = 0;
                        i--;

                        break;
                    }
                }
                // player can move Mcells to LeftTDown
                if (sw == 1)
                {
                    // check energy of player
                    if (Mcells * AGptr->energyForMoving <= TemporaryEnergy)
                    {
                        // add Food energy to player
                        for (int j = 1; j <= Mcells; j++)
                        {
                            if (*board[x + j][y - j].identifierPlace == 'F')
                            {
                                alliedanimalposition[i].energyPoint += board[x + j][y - j].foodPlace.energy;
                                delete_Food(x + j, y - j, Foodcell, &foodcount);
                                board[x + j][y - j] = defaultCell;
                            }
                        }
                        // player moved
                        move(winSwitch, worldsize, board, player, x, y, x + Mcells, y - Mcells, alliedanimalposition, i, Mcells);

                        // to check that allied animal can do anything(reproduction or moving or...) or shoud be die
                        if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                        {
                            // animal died

                            animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                            delete_animal(i, alliedanimalposition, &alliedcount);
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
        }
        break;

    // player want to cooperat//
    case ARROW_COOPERATION:

        if (alliedanimalposition[i].energyPoint - AGptr->energyForMoving >= 0)
        {
            int animalX, animalY;
            printf("please enter the position of animal for cooperat :");
            scanf("%d %d", &animalX, &animalY);
            printf("\n");
            Animal *helperanimal, *animal;
            helperanimal = &alliedanimalposition[i];
            int find = searchanimal(animalX, animalY, alliedanimalposition, *alliedcount);
            while (find == -1)
            {
                textcolor(12);
                printf("in this position don't exist animal or Out of bounds\npleas enter another position :");
                textcolor(1);
                scanf("%d %d", &animalX, &animalY);
                printf("\n");
                find = searchanimal(animalX, animalY, alliedanimalposition, *alliedcount);
            }
            animal = &alliedanimalposition[find];
            cooperation(helperanimal, animal);
            // to check energy of allied animal at first round to know can it do anything(reproduction or moving or...) or it should be die
            if (minenergy(*AGptr) > alliedanimalposition[i].energyPoint)
                {
                    // animal died
                    animalDeath(worldsize, board, alliedanimalposition[i].x, alliedanimalposition[i].y, alliedanimalposition[i].energyPoint, Foodcell, &foodcount);
                    delete_animal(i, alliedanimalposition, &alliedcount);
                    return i - 1;
                }
        }
        else
        {
            textcolor(12);
            printf("YOU DON'T HAVE ENOUGH ENERGY FOR COOPERATION !");
            printf("\n");
            i--;
        }
        break;

    default:
        // pressed the wrong Key
        i--;
        break;
    }

    return i;
}