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

int isValid(int row, int col, int worldSize)
{
    return ((row >= 0) && (col >= 0) && (row < worldSize) && (col < worldSize)) ? 1 : 0;
}

int row[4] = {-1, 0, 0, 1};
int col[4] = {0, -1, 1, 0};

int printPath(int worldsize, struct Cell board[][worldsize], struct Point start, struct Point end, struct Point pointTomove[], struct QueueNode items[], int *front, int *rear)
{

    int sw = 0;

    int visited[ROW][COL];
    memset(visited, 0, sizeof visited);

    int d[ROW][COL];
    memset(d, -1, sizeof d);

    struct QueueNode node = {
        start,
        0};

    visited[start.x][start.y] = 1;
    d[start.x][start.y] = 0;

    push(node, front, rear, items);

    while (isEmpty(*front, *rear) == 0)
    {

        struct QueueNode curr = items[*front];
        struct Point pt = curr.p;
        if (pt.x == end.x && pt.y == end.y)
        {
            int xx = pt.x, yy = pt.y;
            int dist = curr.distance;
            int counter = 0;
            pointTomove[counter].x = xx;
            pointTomove[counter].y = yy;
            counter++;
            while (xx != start.x || yy != start.y)
            {

                if (xx > 0 && d[xx - 1][yy] == dist - 1)
                {

                    pointTomove[counter].x = xx - 1;
                    pointTomove[counter].y = yy;
                    xx--;
                    counter++;
                }

                if (xx < ROW - 1 && d[xx + 1][yy] == dist - 1)
                {

                    pointTomove[counter].x = xx + 1;
                    pointTomove[counter].y = yy;
                    xx++;
                    counter++;
                }

                if (yy > 0 && d[xx][yy - 1] == dist - 1)
                {

                    pointTomove[counter].x = xx;
                    pointTomove[counter].y = yy - 1;
                    yy--;
                    counter++;
                }

                if (yy < COL - 1 && d[xx][yy + 1] == dist - 1)
                {

                    pointTomove[counter].x = xx;
                    pointTomove[counter].y = yy + 1;
                    yy++;
                    counter++;
                }
                dist--;
            }

            sw = 1;
            return counter;
            break;
        }

        pop(front, rear, items);
        for (int i = 0; i < 4; i++)
        {
            int x = pt.x + row[i];
            int y = pt.y + col[i];

            if (isValid(x, y,worldsize) == 1 && visited[x][y] == 0)
            {
                if (strcmp(board[x][y].identifierPlace, "F") == 0 || strcmp(board[x][y].identifierPlace, "H") == 0 || strcmp(board[x][y].identifierPlace, ".") == 0)
                {
                    visited[x][y] = 1;
                    struct QueueNode newNode = {
                        {x,
                         y},
                        curr.distance + 1};
                    push(newNode, front, rear, items);
                    d[x][y] = curr.distance + 1;
                }
            }
        }
    }

    if (sw == 0)
        return -1;
}
