typedef struct Animal
{
    int energyPoint, healthPoint, maximumEnergy;
    Genome gene;
    int x, y;
    Point pointTomove[100];
    int pointindex;
} Animal;
