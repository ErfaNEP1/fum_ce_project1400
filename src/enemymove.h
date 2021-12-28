
int FindtheClosestWaytoH(int enemyX, int enemyY, struct Cell heavencell[], int heavencount){
    int dis, mindis =40,mukhtasat ;
    for(int i=0; i<heavencount; i++){
        dis=sqrt( pow(abs(enemyX-heavencell[i].x) ,2) + pow(abs(enemyY-heavencell[i].y) ,2) );
        if(dis < mindis){
            mindis=dis;
            mukhtasat=i;
        }
    }
    return mukhtasat;
}

#define SIZE 400
#define ROW 20
#define COL 20


struct point
{
    int x, y;
};

struct QueueNode
{
    struct point p;
    int distance;
};

struct QueueNode items[SIZE];
int front = -1, rear = -1;

int isFull()
{
    if ((front == rear + 1) || (front == 0 && rear == SIZE - 1))
        return 1;
    return 0;
}

int isEmpty()
{
    if (front == -1)
        return 1;
    return 0;
}

void push(struct QueueNode element)
{
    if (isFull() == 0)
    {
        if (front == -1)
            front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
    }
}

void pop()
{
    struct QueueNode element;
    if (isEmpty() == 0)
    {
        element = items[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }
        return;
    }
}

void display()
{
    int i;
    if (isEmpty())
        printf(" \n Empty Queue\n");
    else
    {
        for (i = front; i != rear; i = (i + 1) % SIZE)
        {
            printf("%d %d\n", items[i].p.x,items[i].p.y);
        }
    }
}

int isValid(int row, int col)
{
    return ((row >= 0) && (col >= 0) && (row < ROW) && (col < COL)) ? 1 : 0;
}

int row[4] = {-1, 0, 0, 1};
int col[4] = {0, -1, 1, 0};

int printPath(int worldsize , struct Cell board[][worldsize], struct Animal enemyanimalposition[], struct point start, struct point end, int n, char enemy[])
{
    Cell enemyanimal = {
        .typePlace = "animal",
        .identifierPlace = *enemy};
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};

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

    push(node);

    while (isEmpty() == 0)
    {

        struct QueueNode curr = items[front];
        struct point pt = curr.p;
        if (pt.x == end.x && pt.y == end.y)
        {
            int xx = pt.x, yy = pt.y;
            int dist = curr.distance;

            while (xx != start.x || yy != start.y) {

                if (xx > 0 && d[xx - 1][yy] == dist - 1) {
                    board[xx-1][yy]=enemyanimal;
                    board[xx][yy]=defaultCell;
                    enemyanimalposition[n].x--;
                    printf("enemy(%s) go to Up",enemy);
                    xx--;
                }

                if (xx < ROW - 1 && d[xx + 1][yy] == dist - 1) {
                    board[xx + 1][yy]=enemyanimal;
                    board[xx][yy]=defaultCell;
                    enemyanimalposition[n].x++;
                    printf("enemy(%s) go to Down",enemy);
                    
                    xx++;
                }

                if (yy > 0 && d[xx][yy - 1] == dist - 1) {
                    board[xx][yy-1]=enemyanimal;
                    board[xx][yy]=defaultCell;
                    enemyanimalposition[n].y--;
                    printf("enemy(%s) go to Left",enemy);

                    yy--;
                }

                if (yy < COL - 1 && d[xx][yy + 1] == dist - 1) {
                    board[xx][yy+1]=enemyanimal;
                    board[xx][yy]=defaultCell;
                    enemyanimalposition[n].y++;
                    printf("enemy(%s) go to Right",enemy);

                    yy++;
                }
                dist--;
            }

            sw = 1;
            break;
        }

        pop();
        for (int i = 0; i < 4; i++)
        {
            int x = pt.x + row[i];
            int y = pt.y + col[i];

            if (isValid(x, y) == 1  )
            {
                if(strcmp(board[x][y].identifierPlace,"F")==0  || strcmp(board[x][y].identifierPlace , "H")==0  || strcmp(board[x][y].identifierPlace , ".")==0 )
                {
                    visited[x][y] = 1;
                    struct QueueNode newNode = {
                        {x,
                        y},
                        curr.distance + 1};
                    push(newNode);
                    d[x][y] = curr.distance + 1;

                }
            }
        }
    }

    if(sw == 0)
        printf("Impossible !");
}



