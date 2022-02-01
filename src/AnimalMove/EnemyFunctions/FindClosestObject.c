/**
 * Find Closest Object coordinates
 * 
 * @param {int-animalX} animal x coordinate;
 * @param {int-animalY} animal y coordinate;
 * @param {Cell-cell[]} array of cells we want to look for the nearst one
 * @param {int-count} array length
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[]][]} game's map.
 * 
 * @return {int-index} index of nearst object in array
 */
int ClosestObject(int animalX, int animalY, struct Cell cell[], int count, int worldsize, struct Cell board[][worldsize])
{
    int dis, mindis = 999, mukhtasat;
    struct Animal animal = {
        .x = animalX,
        .y = animalY,
    };
    for (int i = 0; i < count; i++)
    {
        // Initializing Queue Structure
        struct QueueNode items[worldsize * worldsize];
        int front = -1, rear = -1;
        int *frontPtr = &front, *rearPtr = &rear;
        struct Point start = {
            .x = animalX,
            .y = animalY};
        struct Point end = {
            .x = cell[i].x,
            .y = cell[i].y,
        };
        dis = printPath(worldsize, board, start, end, animal.pointTomove, items, frontPtr, rearPtr) - 1;
        if (dis < mindis && dis != -2)
        {
            mindis = dis;
            mukhtasat = i;
        }
    }
    return mukhtasat;
}


/**
 * Find Closest Object Distance
 * 
 * @param {int-animalX} animal x coordinate;
 * @param {int-animalY} animal y coordinate;
 * @param {Cell-cell[]} array of cells we want to look for the nearst one
 * @param {int-count} array length
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[]][]} game's map.
 * 
 * @return {int-distance} distance to nearst object in array
 */
int ClosestDistance(int animalX, int animalY, struct Cell cell[], int count, int worldsize, struct Cell board[][worldsize])
{
    int dis, mindis = 999;
    struct Animal animal = {
        .x = animalX,
        .y = animalY,
    };
    for (int i = 0; i < count; i++)
    {
        // Initializing Queue Structure
        struct QueueNode items[worldsize * worldsize];
        int front = -1, rear = -1;
        int *frontPtr = &front, *rearPtr = &rear;
        struct Point start = {
            .x = animalX,
            .y = animalY};
        struct Point end = {
            .x = cell[i].x,
            .y = cell[i].y,
        };
        dis = printPath(worldsize, board, start, end, animal.pointTomove, items, frontPtr, rearPtr) - 1;
        if (dis < mindis && dis != -2)
        {
            mindis = dis;
        }
    }
    return mindis;
}
/**
 * Find Closest Ally
 * 
 * @param {int-animalX} animal x coordinate;
 * @param {int-animalY} animal y coordinate;
 * @param {int-worldsize} size of the map.
 * @param {World-world} game's database
 * @param {Cell-board[]][]} game's map.
 * 
 * @return {int-index} index of nearst object in array
 */
int ClosestAlly(int animalX, int animalY,int worldsize, World world, struct Cell board[][worldsize])
{
    int mindis = 999;
    int index = -1;
    for (int i = 0; i < world.enemyCount; i++)
    {
        if(world.enemyanimalposition[i].x != animalX || world.enemyanimalposition[i].y != animalY){
            int dis = abs(animalX - world.enemyanimalposition[i].x) + abs(animalY - world.enemyanimalposition[i].y);
            if(dis < mindis && strcmp(board[world.enemyanimalposition[i].x][world.enemyanimalposition[i].y].identifierPlace,board[animalX][animalY].identifierPlace) == 0){
                mindis = dis;
                index = i;
            }
        }
    }
    return index;
    
}
/**
 * Find Closest Ally Distance
 * 
 * @param {int-animalX} animal x coordinate;
 * @param {int-animalY} animal y coordinate;
 * @param {int-worldsize} size of the map.
 * @param {World-world} game's database
 * @param {Cell-board[]][]} game's map.
 * 
 * @return {int-distance} distance of nearst ally in array
 */
int ClosestAllyDistance(int animalX, int animalY,int worldsize, World world, struct Cell board[][worldsize])
{
    int mindis = 999;
    for (int i = 0; i < world.enemyCount; i++)
    {
        if(world.enemyanimalposition[i].x != animalX || world.enemyanimalposition[i].y != animalY){
            int dis = abs(animalX - world.enemyanimalposition[i].x) + abs(animalY - world.enemyanimalposition[i].y);
            if(dis < mindis && strcmp(board[world.enemyanimalposition[i].x][world.enemyanimalposition[i].y].identifierPlace,board[animalX][animalY].identifierPlace) == 0){
                mindis = dis;
            }
        }
    }
    return mindis;
}