void initAImovie(World *world, int nEnemy, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < world->enemyCount; i++)
    {
        Animal *animalPtr;
        animalPtr = &world->enemyanimalposition[i];

        // World Inputs Needed for AI
        int ClosestAllied = ClosestAlly(animalPtr->x, animalPtr->y, world->size, *world, board);
        int ClosestAlliedDistance = ClosestAllyDistance(animalPtr->x, animalPtr->y, world->size, *world, board);
        printf("DISTANCE FROM %d : %d\n", ClosestAllied, ClosestAlliedDistance);
        Animal *fatherPtr;
        fatherPtr = &world->enemyanimalposition[ClosestAllied];

        int ClosestDistanceToHeaven = ClosestDistance(animalPtr->x, animalPtr->y, world->heavenCell, world->heavenCount, worldSize, board);
        int ClosestDistanceToFood = ClosestDistance(animalPtr->x, animalPtr->y, world->foodCell, world->foodCount, worldSize, board);
        int CurrentEnergy = animalPtr->energyPoint;
        int EnergyForMove = animalPtr->gene.energyForMoving;
        int EnergyToReproduceMother = animalPtr->gene.energyForReproduction;
        int EnergyToReproduceFather = fatherPtr->gene.energyForReproduction;
        int MaximumEnergy = animalPtr->maximumEnergy;
        // End World Inputs

        int action; // 0 : Heaven, 1 : Food
        double score = -1;
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                double new_score = MoveToHeavenScore(ClosestDistanceToHeaven, CurrentEnergy, MaximumEnergy, EnergyForMove, world->size);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
            else if (j == 1)
            {
                double new_score = MoveToFoodScore(ClosestDistanceToFood, CurrentEnergy, MaximumEnergy, world->size);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
            else if (j == 2)
            {
                double new_score = ReproductScore(ClosestAlliedDistance, animalPtr->energyPoint, fatherPtr->energyPoint, EnergyToReproduceMother, EnergyToReproduceFather);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
        }
        //Debug
        double FoodScore = MoveToFoodScore(ClosestDistanceToFood, CurrentEnergy, MaximumEnergy, world->size);
        double HeavenScore = MoveToHeavenScore(ClosestDistanceToHeaven, CurrentEnergy, MaximumEnergy, EnergyForMove, world->size);
        double Reproduct = ReproductScore(ClosestAlliedDistance, animalPtr->energyPoint, fatherPtr->energyPoint, EnergyToReproduceMother, EnergyToReproduceFather);

        if (action == 0)
        {
            movetoheaven(world, worldSize, winSwitch, board, animalPtr, &i);
            printf("PLAYER %d GOING TO HEAVEN\nFood Score : %f Heaven Score : %f Reproduce Score : %f\n", i, FoodScore, HeavenScore, Reproduct);
        }
        else if (action == 1)
        {
            movetofood(world, worldSize, winSwitch, board, animalPtr, &i);
            printf("PLAYER %d GOING FOR FOOD\nFood Score : %f Heaven Score : %f Reproduce Score : %f\n", i, FoodScore, HeavenScore, Reproduct);
        }
        else if (action == 2)
        {
            reproduction(animalPtr, fatherPtr, &world->enemyCount, world->enemyanimalposition, worldSize, board);
            printf("PLAYER %d GOING TO REPRODUCE\nFood Score : %f Heaven Score : %f Reproduce Score : %f\n", i, FoodScore, HeavenScore, Reproduct);
        }

        printf("Final Energy = %d\n\n\n", animalPtr->energyPoint);

        // movetoheaven(world, worldSize, winSwitch, board, animalPtr, &i);
        if (*winSwitch == 1)
            break;

        // to check energy of enemy animal at first round to know can it do anything(reproduction or moving or...) or it should die
        if (minenergy(animalPtr->gene) > animalPtr->energyPoint)
        {
            // animal died

            int *foodcount = &world->foodCount;
            int *enemycount = &world->enemyCount;
            animalDeath(worldSize, board, animalPtr->x, animalPtr->y, animalPtr->energyPoint, world->foodCell, &foodcount);
            delete_animal(i, world->enemyanimalposition, &enemycount);
            i--;
        }
        printf("\n");
        clearScreen();
    }
}
