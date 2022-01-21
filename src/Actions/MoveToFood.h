void movetofood(World *world, int worldSize, int *winSwitch, Cell board[][worldSize], Animal *animalPtr, int *i)
{
    // Finding the closest Heaven
    int mindist = ClosestObject(animalPtr->x, animalPtr->y, world->foodCell, world->foodCount);
    // Initializing Queue Structure
    struct QueueNode items[world->size * world->size];
    int front = -1, rear = -1;
    int *frontPtr = &front, *rearPtr = &rear;
    struct Point start = {
        .x = animalPtr->x,
        .y = animalPtr->y};
    struct Point end = {
        .x = world->foodCell[mindist].x,
        .y = world->foodCell[mindist].y};
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
            int finalindex = cellsToMove(animalPtr->gene.energyForMoving, animalPtr->pointTomove, animalPtr->pointindex, animalPtr->gene.cellsToMove, n, world->size, board, animalPtr->energyPoint);
            int Mcells = finalindex - (animalPtr->pointindex);
            animalPtr->pointindex = finalindex;
            // move the enemy
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y, world->enemyanimalposition, *i, Mcells);
            // check if game is finished
            if (*winSwitch == 1)
            {
                *winSwitch = 0;
                snprintf(world->winner, 2, "%s", board[animalPtr->pointTomove[animalPtr->pointindex].x][animalPtr->pointTomove[animalPtr->pointindex].y].identifierPlace);
                return;
            }
        }
        // if there is not a path from start to end and its impossible to move, then we can do a random move for a round
        else
        {
            //Random Move
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
    }
    // if enemy already has a path to move, then it should continue it's path
    else
    {
        // if its path is not blocked by anything
        if (check(worldSize, board, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y))
        {
            int finalindex = cellsToMove(animalPtr->gene.energyForMoving, animalPtr->pointTomove, animalPtr->pointindex, animalPtr->gene.cellsToMove, n, world->size, board, animalPtr->energyPoint);
            int Mcells = finalindex - (animalPtr->pointindex);
            animalPtr->pointindex = finalindex;
            move(&winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, animalPtr->pointTomove[animalPtr->pointindex].x, animalPtr->pointTomove[animalPtr->pointindex].y, world->enemyanimalposition, *i, Mcells);
            if (*winSwitch == 1)
            {
                *winSwitch = 0;
                snprintf(world->winner, 2, "%s", board[animalPtr->pointTomove[animalPtr->pointindex].x][animalPtr->pointTomove[animalPtr->pointindex].y].identifierPlace);
                return;
            }
        }
        else
        // if it's blocked, then it should find another path
        {
            animalPtr->pointindex = -1;
            // here we make the for loop to iterate this enemy once again
            --*i;
        }
    }
}