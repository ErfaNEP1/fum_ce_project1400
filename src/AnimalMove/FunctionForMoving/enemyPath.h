#define SIZE 400
#define ROW 20
#define COL 20

struct QueueNode
{
    struct Point p;
    int distance;
};

int isFull(int front, int rear)
{
    if ((front == rear + 1) || (front == 0 && rear == SIZE - 1))
        return 1;
    return 0;
}

int isEmpty(int front, int rear)
{
    if (front == -1)
        return 1;
    return 0;
}

//add coordinates of past cells in queue
void push(struct QueueNode element, int *front, int *rear, struct QueueNode items[])
{
    if (isFull(*front, *rear) == 0)
    {
        if (*front == -1)
            *front = 0;
        *rear = (*rear + 1) % SIZE;
        items[*rear] = element;
    }
}

//remove coordinates from queue
void pop(int *front, int *rear, struct QueueNode items[])
{
    struct QueueNode element;
    if (isEmpty(*front, *rear) == 0)
    {
        element = items[*front];
        if (*front == *rear)
        {
            *front = -1;
            *rear = -1;
        }
        else
        {
            *front = (*front + 1) % SIZE;
        }
        return;
    }
}

//to check that we're in board or not
int isValid(int row, int col, int worldSize)
{
    return ((row >= 0) && (col >= 0) && (row < worldSize) && (col < worldSize)) ? 1 : 0;
}

int row[8] = {-1, 0, 0, 1, 1, -1, -1, 1};
int col[8] = {0, -1, 1, 0, 1, 1, -1, -1};

//it keeps coordinates of cells that take us to H by the shortest way
int printPath(int worldsize, struct Cell board[][worldsize], struct Point start, struct Point end, struct Point pointTomove[], struct QueueNode items[], int *front, int *rear)
{

    int sw = 0;
    //to mark cells that past
    int visited[ROW][COL]; 

    //it puts a number in all cells of an array 
    memset(visited, 0, sizeof visited);

    //to keep distance from start
    int d[ROW][COL]; 
    memset(d, -1, sizeof d);

    struct QueueNode node = {
        start,
        0};

    visited[start.x][start.y] = 1;
    d[start.x][start.y] = 0;
    
    //add start cell in queue
    push(node, front, rear, items);

    while (isEmpty(*front, *rear) == 0)
    {

        struct QueueNode curr = items[*front];
        struct Point pt = curr.p;

        //to put cells that take us to H in an array(pointtomove)
        if (pt.x == end.x && pt.y == end.y)
        {
            int xx = pt.x, yy = pt.y;
            int dist = curr.distance;
            int counter = 0;
            //put start cell in pointtomve
            pointTomove[counter].x = xx;
            pointTomove[counter].y = yy;
            
            counter++;
            while (xx != start.x || yy != start.y)
            {
                //put coordinates in pointTomove that can make enemy closer to H
                if (xx < worldsize - 1 && yy < worldsize - 1 && d[xx + 1][yy + 1] == dist - 2 && dist - 2 > 0)
                {
                    pointTomove[counter].x = xx + 1;
                    pointTomove[counter].y = yy + 1;
                    xx++;
                    yy++;
                    dist -= 2;
                    counter++;
                    continue;
                }

                if (xx > 0 && yy < worldsize - 1 && d[xx - 1][yy + 1] == dist - 2 && dist - 2 > 0)
                {
                    pointTomove[counter].x = xx - 1;
                    pointTomove[counter].y = yy + 1;
                    xx--;
                    yy++;
                    dist -= 2;
                    counter++;
                    continue;
                }

                if (xx > 0 && yy > 0 && d[xx - 1][yy - 1] == dist - 2 && dist - 2 > 0)
                {
                    pointTomove[counter].x = xx - 1;
                    pointTomove[counter].y = yy - 1;
                    xx--;
                    yy--;
                    dist -= 2;
                    counter++;
                    continue;
                }

                if (xx < worldsize - 1 && yy > 0 && d[xx + 1][yy - 1] == dist - 2 && dist - 2 > 0)
                {
                    pointTomove[counter].x = xx + 1;
                    pointTomove[counter].y = yy - 1;
                    xx++;
                    yy--;
                    dist -= 2;
                    counter++;
                    continue;
                }

                if (xx > 0 && d[xx - 1][yy] == dist - 1)
                {

                    pointTomove[counter].x = xx - 1;
                    pointTomove[counter].y = yy;
                    xx--;
                    counter++;
                    dist--;
                    continue;
                }

                if (xx < worldsize - 1 && d[xx + 1][yy] == dist - 1)
                {

                    pointTomove[counter].x = xx + 1;
                    pointTomove[counter].y = yy;
                    xx++;
                    counter++;
                    dist--;
                    continue;
                }

                if (yy > 0 && d[xx][yy - 1] == dist - 1)
                {

                    pointTomove[counter].x = xx;
                    pointTomove[counter].y = yy - 1;
                    yy--;
                    counter++;
                    dist--;
                    continue;
                }

                if (yy < worldsize - 1 && d[xx][yy + 1] == dist - 1)
                {

                    pointTomove[counter].x = xx;
                    pointTomove[counter].y = yy + 1;
                    yy++;
                    counter++;
                    dist--;
                    continue;
                }
                
            }

            sw = 1; //enemy can reach H
            return counter;
            break;
        }

        pop(front, rear, items);
        for (int i = 0; i < 8; i++)
        {
            int x = pt.x + row[i];
            int y = pt.y + col[i];

            //to keep distance from start
            if (isValid(x, y, worldsize) == 1 && visited[x][y] == 0)
            {
                if (strcmp(board[x][y].typePlace, "animal") != 0 && *board[x][y].identifierPlace != '#')
                {
                    visited[x][y] = 1;
                    struct QueueNode newNode = {
                        {x,
                         y}};
                    if (i > 3)
                    {
                        newNode.distance = curr.distance + 2;
                        d[x][y] = curr.distance + 2;
                    }
                    else
                    {
                        newNode.distance = curr.distance + 1;
                        d[x][y] = curr.distance + 1;
                    }
                    push(newNode, front, rear, items);
                    
                }
            }
        }
    }

    if (sw == 0) //enemy can't reach H
        return -1;
}
