typedef struct World
{
    int size;
    int deadEndCount, heavenCount, foodCount, animalCount, alliedCount, enemyCount;
    char animalToControl[2];
    char winner[2];
    Cell deadEnds[100];
    Cell heavenCell[100];
    Cell foodCell[100];
    Animal alliedanimalposition[100];
    Animal enemyanimalposition[100];
} World;