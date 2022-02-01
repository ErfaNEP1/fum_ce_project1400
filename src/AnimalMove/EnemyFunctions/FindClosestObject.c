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