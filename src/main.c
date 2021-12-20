#include <stdio.h>
#include <string.h>
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Food.h"
#include "Models/Cell.h"
#include "Models/World.h"

int main(){
    int worldSize;
    World world;
    scanf("%d",&worldSize);

    world.size = worldSize;

    Cell board[world.size][world.size];

    initWorld(world,world.size,board);

    printWorld(world.size,board);

}