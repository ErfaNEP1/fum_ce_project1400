void inputDeadEnds(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell deadEndCell = {
        .typePlace = "dead_end",
        .identifierPlace = "#"};
    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &world->deadEndCount);
    tok = strtok(NULL, " \n");

    for (int i = 0; i < world->deadEndCount; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        deadEndCell.x = x;
        deadEndCell.y = y;

        board[x][y] = deadEndCell;
        world->deadEnds[i] = deadEndCell;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputHeavens(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell heavenCell = {
        .typePlace = "heaven",
        .identifierPlace = "H"};
    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &world->heavenCount);
    tok = strtok(NULL, " \n");

    for (int i = 0; i < world->heavenCount; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        heavenCell.x = x;
        heavenCell.y = y;

        board[x][y] = heavenCell;
        world->heavenCell[i] = heavenCell;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputFood(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    tok = strtok(NULL, " ");
    int energy;
    sscanf(tok, "%d", &energy);
    Food energyCell = {
        .energy = energy};

    Cell foodCell = {
        .typePlace = "food",
        .identifierPlace = "F",
        .foodPlace = energyCell};

    tok = strtok(NULL, " ");

    int x, y;
    sscanf(tok, "(%d,%d)", &x, &y);

    foodCell.x = x;
    foodCell.y = y;

    board[x][y] = foodCell;
    world->foodCell[world->foodCount] = foodCell;

    world->foodCount++;
}

void inputAnimals(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    Cell typeanimal = {
        .typePlace = "animal",
        .identifierPlace = *tok,
        .animalPlace.pointindex = 0};
    int nu_typeanimal;

    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &nu_typeanimal);
    world->animalCount += nu_typeanimal;

    tok = strtok(NULL, " \n");

    for (int i = 0; i < nu_typeanimal; i++)
    {
        int x, y;

        sscanf(tok, "(%d,%d)", &x, &y);

        typeanimal.x = x;
        typeanimal.y = y;

        board[x][y] = typeanimal;

        tok = strchr(tok, ')');
        if (tok == NULL)
            break;
        ++tok;
    }
}
void inputGenome(int worldSize, char *tok, World *world, Cell board[][worldSize])
{
    int energy;
    Genome gene = {
        .character = *tok};

    tok = strtok(NULL, " \n");
    sscanf(tok, "%d", &energy);

    tok = strtok(NULL, " \n");

    for (int i = 0; i < 5; i++)
    {
        int gen;

        sscanf(tok, "%d", &gen);

        tok = strchr(tok, '$');

        ++tok;

        if (i == 0)
        {
            gene.energyForMoving = gen;
        }
        else if (i == 1)
        {
            gene.cellsToMove = gen;
        }
        else if (i == 2)
        {
            gene.energyForReproduction = gen;
        }
        else if (i == 3)
        {
            gene.attackPower = gen;
        }
        else if (i == 4)
        {
            gene.defensePower = gen;
        }
    }
    // Give animals their genome
    giveCharactersGenome(gene, gene.character, world->size, board, energy);
}

void initAImovie(World *world, int nEnemy, int worldSize, int *winSwitch, Cell board[][worldSize])
{
    for (int i = 0; i < world->enemyCount; i++)
    {
        Animal *animalPtr;
        animalPtr = &world->enemyanimalposition[i];

        // World Inputs Needed for AI
        int ClosestDistanceToHeaven = ClosestDistance(animalPtr->x,animalPtr->y,world->heavenCell,world->heavenCount,worldSize,board);
        int ClosestDistanceToFood = ClosestDistance(animalPtr->x,animalPtr->y,world->foodCell,world->foodCount,worldSize,board);
        int CurrentEnergy = animalPtr->energyPoint;
        int MaximumEnergy = animalPtr->maximumEnergy;
        // End World Inputs


        int action; // 0 : Heaven, 1 : Food
        double score = -1;
        for (int j = 0; j < 2; j++)
        {     
            if(j == 0){
                double new_score = MoveToHeavenScore(ClosestDistanceToHeaven,CurrentEnergy,MaximumEnergy);
                if(score < new_score){
                    score = new_score;
                    action = j;
                }
            }else if(j == 1){
                double new_score = MoveToFoodScore(ClosestDistanceToFood,CurrentEnergy,MaximumEnergy);
                if(score < new_score){
                    score = new_score;
                    action = j;
                }
            }
            
        }
        //Debug
        double FoodScore = MoveToFoodScore(ClosestDistanceToFood,CurrentEnergy,MaximumEnergy);
        double HeavenScore = MoveToHeavenScore(ClosestDistanceToHeaven,CurrentEnergy,MaximumEnergy);
        if(action == 0) {
            movetoheaven(world, worldSize, winSwitch, board, animalPtr, &i);
            printf("PLAYER %d GOING TO HEAVEN\nFood Score : %f Heaven Score : %f\n",i,FoodScore,HeavenScore);
        }else if(action == 1){
            movetofood(world, worldSize, winSwitch, board, animalPtr, &i);
            printf("PLAYER %d GOING FOR FOOD\nFood Score : %f Heaven Score : %f\n",i,FoodScore,HeavenScore);
        }
        printf("Final Energy = %d\n\n\n",animalPtr->energyPoint);
        
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
            i = animalTocontrol(&winSwitch, world->animalToControl, world->size, board, i, world->alliedanimalposition, clickedKey, world->foodCell, &world->foodCount, &world->alliedCount);
            if (*winSwitch == 1)
                return i;
            if (i == k - 1)
                printWorld(world->size, board, k, *world);
            else
                printf("Final Energy = %d\n",animalPtr->energyPoint);
                printWorld(world->size, board, i + 1, *world);
        }
        if (i != world->alliedCount - 1)
            ch = get_code();
    }
}