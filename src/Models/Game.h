void inputDeadEnds(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell deadEndCell = {
        .typePlace = "dead_end",
        .identifierPlace = "#"};
    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &world->deadEndCount);
    tok = strtok(NULL, " \n");

    for (int i = 0; i < world->deadEndCount; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        deadEndCell.x = x;
        deadEndCell.y = y;

        board[x][y] = deadEndCell;
        world->deadEnds[i] = deadEndCell;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputHeavens(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell heavenCell = {
        .typePlace = "heaven",
        .identifierPlace = "H"};
    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &world->heavenCount);
    tok = strtok(NULL, " \n");

    for (int i = 0; i < world->heavenCount; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        heavenCell.x = x;
        heavenCell.y = y;

        board[x][y] = heavenCell;
        world->heavenCell[i] = heavenCell;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputFood(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    tok = strtok(NULL, " ");
    int energy;
    sscanf(tok, "%d", &energy);
    Food energyCell = {
        .energy = energy};

    Cell foodCell = {
        .typePlace = "food",
        .identifierPlace = "F",
        .foodPlace = energyCell};

    tok = strtok(NULL, " ");

    int x, y;
    sscanf(tok, "(%d,%d)", &x, &y);

    foodCell.x = x;
    foodCell.y = y;

    board[x][y] = foodCell;
    world->foodCell[world->foodCount] = foodCell;

    world->foodCount++;
}

void inputAnimals(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell typeanimal = {
        .typePlace = "animal",
        .identifierPlace = *tok,
        .animalPlace.pointindex = -1};
    int nu_typeanimal;

    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &nu_typeanimal);
    world->animalCount += nu_typeanimal;

    tok = strtok(NULL, " \n");

    for (int i = 0; i < nu_typeanimal; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        typeanimal.x = x;
        typeanimal.y = y;

        board[x][y] = typeanimal;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputGenome(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    int energy;
    Genome gene = {
        .character = *tok};

    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &energy);

    tok = strtok(NULL, " \n");

    for (int i = 0; i < 5; i++)
    {
        int gen;

        sscanf(tok, "%d", &gen);

        tok = strchr(tok, '$');

        ++tok;

        if (i == 0)
        {
            gene.energyForMoving = gen;
        }
        else if (i == 1)
        {
            gene.cellsToMove = gen;
        }
        else if (i == 2)
        {
            gene.energyForReproduction = gen;
        }
        else if (i == 3)
        {
            gene.attackPower = gen;
        }
        else if (i == 4)
        {
            gene.defensePower = gen;
        }
    }
    // Give animals their genome
    giveCharactersGenome(gene, gene.character, world->size, board, energy);
}

void initAImovie(World *world, int nEnemy, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < nEnemy; i++)
    {
        Animal *animalPtr;
        animalPtr = &world->enemyanimalposition[i];
        // Finding the closest Heaven
        int mindist = ClosestObject(animalPtr->x, animalPtr->y, world->heavenCell, world->heavenCount);
        // Initializing Queue Structure
        struct QueueNode items[world->size * world->size];
        int front = -1, rear = -1;
        int *frontPtr = &front, *rearPtr = &rear;
        struct Point start = {
            .x = animalPtr->x,
            .y = animalPtr->y};
        struct Point end = {
            .x = world->heavenCell[mindist].x,
            .y = world->heavenCell[mindist].y};
        int n;
        // if enemy doesn't have a path to move it should create one
        if (animalPtr->pointindex == -1)
        {
            // create a path and store it's distance
            n = printPath(world->size, board, start, end, animalPtr->pointTomove, items, frontPtr, rearPtr);
            // Check if there is a path from start to end and it's possible to move
            if (n != -1)
            {
                reverse(animalPtr->pointTomove, n);
                animalPtr->pointindex++;
                // found how many moves the enemy can make in a single round
                animalPtr->pointindex = cellsToMove(animalPtr->pointTomove, animalPtr->pointindex, animalPtr->gene.cellsToMove, n, world->size, board, animalPtr->energyPoint);
                // move the enemy
                move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y, world->enemyanimalposition, i);
                // check if game is finished
                if (*winSwitch == 1)
                {
                    snprintf(world->winner, 2, "%s", board[animalPtr->pointTomove[animalPtr->pointindex].x][animalPtr->pointTomove[animalPtr->pointindex].y].identifierPlace);
                    break;
                }
            }
            // if there is not a path from start to end and its impossible to move, then we can do a random move for a round
            else
            {
                //Random Move
                if (strcmp(board[start.x + 1][start.y].typePlace,"animal") != 0 && *board[start.x + 1][start.y].identifierPlace != '#' && isValid(start.x + 1, start.y, world->size))
                {
                    move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x + 1, start.y, world->enemyanimalposition, i);
                }
                else if (strcmp(board[start.x - 1][start.y].typePlace,"animal") != 0 && *board[start.x - 1][start.y].identifierPlace != '#' && isValid(start.x - 1, start.y, world->size))
                {
                    move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x - 1, start.y, world->enemyanimalposition, i);
                }
                else if (strcmp(board[start.x][start.y + 1].typePlace,"animal") != 0 && *board[start.x][start.y + 1].identifierPlace != '#' && isValid(start.x, start.y + 1, world->size))
                {
                    move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y + 1, world->enemyanimalposition, i);
                }
                else if (strcmp(board[start.x][start.y - 1].typePlace,"animal") != 0 && *board[start.x][start.y - 1].identifierPlace != '#' && isValid(start.x, start.y - 1, world->size))
                {
                    move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y - 1, world->enemyanimalposition, i);
                }
            }
        }
        // if enemy already has a path to move, then it should continue it's path
        else
        {
            // if its path is not blocked by anything
            if (check(worldSize, board, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y))
            {
                animalPtr->pointindex = cellsToMove(animalPtr->pointTomove, animalPtr->pointindex, animalPtr->gene.cellsToMove, n, world->size, board, animalPtr->energyPoint);
                move(*world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y, world->enemyanimalposition, i);
                if (*winSwitch == 1)
                {
                    snprintf(world->winner, 2, "%s", board[animalPtr->pointTomove[animalPtr->pointindex].x][animalPtr->pointTomove[animalPtr->pointindex].y].identifierPlace);
                    break;
                }
            }
            else
            // if it's blocked, then it should find another path
            {
                animalPtr->pointindex = -1;
                // here we make the for loop to iterate this enemy once again
                i--;
            }
        }
        printf("\n");
        clearScreen();
    }
}

int initPlayerMove(World *world, int ch, int nPlayer, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < world->alliedCount; i++)
    {
        printf("%d\n",world->alliedCount);
        int k=i;
        Animal *animalPtr;
        animalPtr = &world->alliedanimalposition[i];
        int clickedKey = ch;
        if (clickedKey != 0)
        {
            i = animalTocontrol(&winSwitch, world->animalToControl, world->size, board, i, world->alliedanimalposition, clickedKey, world->foodCell, &world->foodCount, &world->alliedCount);
            if(*winSwitch == 1) return i;
            if(i == k-1)
                printWorld(world->size, board, k, *world);
            else
                printWorld(world->size, board, i+1, *world);
            
            
        }
        if (i != world->alliedCount - 1)
            ch = get_code();
    }
}