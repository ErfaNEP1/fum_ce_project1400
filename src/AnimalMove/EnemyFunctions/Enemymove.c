void initAImovie(World *world, int nEnemy, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < world->enemyCount; i++)
    {

        int index = i;

        Animal *animalPtr;
        animalPtr = &world->enemyanimalposition[i];

        // World Inputs Needed for AI

        // Reproduct
        int ClosestAllied = ClosestAlly(animalPtr->x, animalPtr->y, world->size, *world, board);
        int ClosestAlliedDistance = ClosestAllyDistance(animalPtr->x, animalPtr->y, world->size, *world, board);
        Animal *fatherPtr;
        fatherPtr = &world->enemyanimalposition[ClosestAllied];
        int EnergyToReproduceMother = animalPtr->gene.energyForReproduction;
        int EnergyToReproduceFather = fatherPtr->gene.energyForReproduction;

        // Attack
        int checker;
        int ClosestEnemyIndex = ClosestEnemy(animalPtr->x, animalPtr->y, world->size, *world, board,&checker);
        int ClosestEnemyDis = ClosestEnemyDistance(animalPtr->x, animalPtr->y, world->size, *world, board);
        Animal *enemyPtr;
        if(checker == 1)
            enemyPtr = &world->alliedanimalposition[ClosestEnemyIndex];
        else
            enemyPtr = &world->enemyanimalposition[ClosestEnemyIndex];
        int EnemyEnergy = enemyPtr->energyPoint;
        int AttackPower = animalPtr->gene.attackPower;
        int DefensePower = enemyPtr->gene.defensePower;

        // Co-Op
        int teammateIndex = -1;
        int ClosestTeamMateDistanceToHeaven = ClosestTeamMateToHeaven(animalPtr->x, animalPtr->y,world->size,*world,board,&teammateIndex);
        Animal *teammatePtr;
        teammatePtr = &world->enemyanimalposition[teammateIndex];
        
        // General
        int ClosestDistanceToHeaven = ClosestDistance(animalPtr->x, animalPtr->y, world->heavenCell, world->heavenCount, worldSize, board);
        int ClosestDistanceToFood = ClosestDistance(animalPtr->x, animalPtr->y, world->foodCell, world->foodCount, worldSize, board);
        int CurrentEnergy = animalPtr->energyPoint;
        int EnergyForMove = animalPtr->gene.energyForMoving;
        
        int MaximumEnergy = animalPtr->maximumEnergy;
        // End World Inputs

        int action; 
        double score = -1;
        for (int j = 0; j < 5; j++)
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
                double new_score = ReproductScore(ClosestAlliedDistance, CurrentEnergy, fatherPtr->energyPoint, EnergyToReproduceMother, EnergyToReproduceFather);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
            else if(j == 3){
                double new_score = AttackScore(ClosestEnemyDis, CurrentEnergy, EnemyEnergy , EnergyForMove * 3, AttackPower, DefensePower);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
            else if(j == 4){
                double new_score = CoopScore(ClosestTeamMateDistanceToHeaven, EnergyForMove, teammatePtr->energyPoint , CurrentEnergy, worldSize);
                if (score < new_score)
                {
                    score = new_score;
                    action = j;
                }
            }
        }
        

        if (action == 0)
        {
            movetoheaven(world, worldSize, winSwitch, board, animalPtr, &i);
        }
        else if (action == 1)
        {
            movetofood(world, worldSize, winSwitch, board, animalPtr, &i);
        }
        else if (action == 2)
        {
            reproduction(animalPtr, fatherPtr, &world->enemyCount, world->enemyanimalposition, worldSize, board);
        }
        else if (action == 3)
        {
            attack(animalPtr, enemyPtr, world->enemyanimalposition, world->enemyanimalposition, &world->enemyCount, &index, &world->enemyCount, ClosestEnemyIndex, worldSize, board);
        }
        else if (action == 4)
        {
            cooperation(animalPtr,teammatePtr);
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
