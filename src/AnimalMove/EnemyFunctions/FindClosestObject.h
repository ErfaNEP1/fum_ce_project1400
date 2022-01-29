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