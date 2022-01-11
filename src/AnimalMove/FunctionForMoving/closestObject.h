int ClosestObject(int animalX, int animalY, struct Cell cell[], int count)
{
    int dis, mindis = 40, mukhtasat;
    for (int i = 0; i < count; i++)
    {
        dis = abs(animalX - cell[i].x) + abs(animalY - cell[i].y);
        if (dis < mindis)
        {
            mindis = dis;
            mukhtasat = i;
        }
    }
    return mukhtasat;
}