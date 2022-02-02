// #include "WorldFunctions.h"

/**
 * Gets characters' info and stores them in World struct
 *
 * @param {World-world} game's database.
 * @param {char-player} controlled player symbol.
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * @param {Animal-alliedanimalposition[]} array of allied animals in game.
 * @param {Animal-enemyanimalposition[]} array of enemy animals in game.
 * 
 * @return {nPlayer} number of allied characters.
 */
int saveAnimalinfo(World *world, char player[], int worldsize, struct Cell board[][worldsize], struct Animal alliedanimalposition[], Animal enemyanimalposition[])
{
    int nPlayer = 0, nEnemy = 0, nAnimal = 0;
    for (int i = 0; i < worldsize; i++)
    {
        for (int j = 0; j < worldsize; j++)
        {
            if (strcmp(board[i][j].typePlace, "animal") == 0)
            {
                //save players' info
                if (strcmp(board[i][j].identifierPlace, player) == 0)
                {
                    alliedanimalposition[nPlayer].energyPoint = board[i][j].animalPlace.energyPoint;
                    alliedanimalposition[nPlayer].maximumEnergy = board[i][j].animalPlace.energyPoint;
                    alliedanimalposition[nPlayer].x = i;
                    alliedanimalposition[nPlayer].y = j;
                    alliedanimalposition[nPlayer].gene = board[i][j].animalPlace.gene;
                    nPlayer++;
                }
                //save enemies' info
                else
                {
                    enemyanimalposition[nEnemy].energyPoint = board[i][j].animalPlace.energyPoint;
                    enemyanimalposition[nEnemy].maximumEnergy = board[i][j].animalPlace.maximumEnergy;
                    enemyanimalposition[nEnemy].x = i;
                    enemyanimalposition[nEnemy].y = j;
                    enemyanimalposition[nEnemy].pointindex = 0;
                    enemyanimalposition[nEnemy].gene = board[i][j].animalPlace.gene;
                    nEnemy++;
                }
            }
        }
    }
    world->alliedCount = nPlayer;
    world->enemyCount = nEnemy;

    return (nPlayer);
}
/**
 * Gives the inputed character the inputed gene.
 *
 * @param {Genome-gene} gene to be given.
 * @param {char-player[]} character.
 * @param {int-worldsize} size of the map.
 * @param {Cell-board[][]} game's map.
 * @param {int-energyPoint} energy point.
 * @return {void}
 */
void giveCharactersGenome(Genome gene, char player[], int worldsize, struct Cell board[][worldsize], int energyPoint)
{
    for (int i = 0; i < worldsize; i++)
    {
        for (int j = 0; j < worldsize; j++)
        {
            if (strcmp(board[i][j].identifierPlace, player) == 0)
            {
                board[i][j].animalPlace.energyPoint = energyPoint;
                board[i][j].animalPlace.maximumEnergy = energyPoint;
                board[i][j].animalPlace.gene = gene;
            }
        }
    }
}