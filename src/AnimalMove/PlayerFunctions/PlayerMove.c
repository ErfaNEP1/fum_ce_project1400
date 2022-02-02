int initPlayerMove(World *world, int ch, int nPlayer, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < world->alliedCount; i++)
    {
        int k = i;
        Animal *animalPtr;
        animalPtr = &world->alliedanimalposition[i];
        int clickedKey = ch;
        if (clickedKey != 0)
        {

            i = animalTocontrol(&winSwitch, world->animalToControl, world->size, board, i, world->alliedanimalposition, clickedKey, world->foodCell, &world->foodCount, &world->alliedCount,world->enemyanimalposition,&world->enemyCount);
            if (*winSwitch == 1)
                return i;
            clearScreen();
            if (i == k - 1)
                printWorld(world->size, board, k, *world);
            else
            {
                printf("Final Energy = %d\n", animalPtr->energyPoint);
                printWorld(world->size, board, i + 1, *world);
            }
        }

        if (i != world->alliedCount - 1)
            ch = get_code();
    }
}