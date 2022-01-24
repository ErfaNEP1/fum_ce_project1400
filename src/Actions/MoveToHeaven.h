void movetoheaven(World *world, int worldSize, int *winSwitch, Cell board[][worldSize], Animal *animalPtr, int *i)
{
    // Finding the closest Heaven
    int mindist = ClosestObject(animalPtr->x, animalPtr->y, world->heavenCell, world->heavenCount,worldSize,board);
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
    // create a path and store it's distance
    n = printPath(world->size, board, start, end, animalPtr->pointTomove, items, frontPtr, rearPtr);
    // Check if there is a path from start to end and it's possible to move
    if (n != -1)
    {
        reverse(animalPtr->pointTomove, n);
        // found how many moves the enemy can make in a single round
        int finalindex = cellsToMove(animalPtr->gene.energyForMoving, animalPtr->pointTomove, animalPtr->pointindex, animalPtr->gene.cellsToMove, n, world->size, board, &animalPtr->energyPoint,world->foodCell,&world->foodCount);
        int Mcells = finalindex - (animalPtr->pointindex);
        animalPtr->pointindex = finalindex;
        // move the enemy
        move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y, world->enemyanimalposition, *i, Mcells);
    }
    // if there is not a path from start to end and its impossible to move, then we can do a random move for a round
    else
    {
        // Random Move
        if (strcmp(board[start.x + 1][start.y].typePlace, "animal") != 0 && *board[start.x + 1][start.y].identifierPlace != '#' && isValid(start.x + 1, start.y, world->size))
        {
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x + 1, start.y, world->enemyanimalposition, *i, 1);
        }
        else if (strcmp(board[start.x - 1][start.y].typePlace, "animal") != 0 && *board[start.x - 1][start.y].identifierPlace != '#' && isValid(start.x - 1, start.y, world->size))
        {
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x - 1, start.y, world->enemyanimalposition, *i, 1);
        }
        else if (strcmp(board[start.x][start.y + 1].typePlace, "animal") != 0 && *board[start.x][start.y + 1].identifierPlace != '#' && isValid(start.x, start.y + 1, world->size))
        {
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y + 1, world->enemyanimalposition, *i, 1);
        }
        else if (strcmp(board[start.x][start.y - 1].typePlace, "animal") != 0 && *board[start.x][start.y - 1].identifierPlace != '#' && isValid(start.x, start.y - 1, world->size))
        {
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y - 1, world->enemyanimalposition, *i, 1);
        }
    }
    // check if game is finished
    if (*winSwitch == 1)
    {
        snprintf(world->winner, 2, "%s", board[animalPtr->pointTomove[animalPtr->pointindex].x][animalPtr->pointTomove[animalPtr->pointindex].y].identifierPlace);
        return;
    }
    animalPtr->pointindex = 0;
}