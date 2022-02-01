/**
 * Find How Many Moves Can Make In One Single Round
 * 
 * @param {int-energyForMoving} energy needed for every single move
 * @param {Point-pointTomove[]} animal path
 * @param {int-pointindex} which step animal is on (from pointToMove array)
 * @param {int-Mcells} maximum number of steps animal can take according to it's genome
 * @param {int-n} path length.
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[]][]} game's map.
 * @param {int-enemyanimalpositionEnergy} character's current energy
 * @param {FoodCell} array of food cells in world.
 * @param {foodcount} number of cells that contain food
 * 
 * @return {int} maximum steps character can make
 */
int cellsToMove(int energyForMoving, struct Point pointTomove[], int pointindex, int Mcells, int n, int wordsize, struct Cell board[][wordsize], int *enemyanimalpositionEnergy, struct Cell foodcell[], int *foodcount)
{
    int p = pointindex;
    Cell defaultcell = {
        .typePlace = "default",
        .foodPlace.energy = 0,
        .identifierPlace = "."};

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].x == pointTomove[pointindex + i].x; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].y == pointTomove[pointindex + i].y; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].x + i == pointTomove[pointindex + i].x && pointTomove[pointindex].y + i == pointTomove[pointindex + i].y; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].x - i == pointTomove[pointindex + i].x && pointTomove[pointindex].y + i == pointTomove[pointindex + i].y; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].x + i == pointTomove[pointindex + i].x && pointTomove[pointindex].y - i == pointTomove[pointindex + i].y; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }

    if (p == pointindex)
    {
        int i;
        //checked the places of board to move (from cur_pointindex in pointToMove)
        for (i = 1; i <= Mcells && pointindex + i < n && pointTomove[pointindex].x - i == pointTomove[pointindex + i].x && pointTomove[pointindex].y - i == pointTomove[pointindex + i].y; i++)
        {
            // if its path is not blocked by anything
            if (check(wordsize, board, pointTomove[pointindex + i].x, pointTomove[pointindex + i].y) && i * energyForMoving <= (*enemyanimalpositionEnergy))
            {
                //add Food energy to enemy
                if (*board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].identifierPlace == 'F')
                {
                    (*enemyanimalpositionEnergy) += board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y].foodPlace.energy;
                    delete_Food(pointTomove[pointindex + i].x, pointTomove[pointindex + i].y, foodcell, &foodcount);
                    board[pointTomove[pointindex + i].x][pointTomove[pointindex + i].y] = defaultcell;
                }
                continue;
            }
            else
                break;
        }
        p = p + i - 1;
    }
    return p;
}