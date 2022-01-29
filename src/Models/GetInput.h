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