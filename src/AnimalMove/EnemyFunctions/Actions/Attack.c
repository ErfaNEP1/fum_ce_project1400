/**
 * attacking given two animals
 *
 * @param {Animal-attacker} attacker
 * @param {Animal-enemy} enemy
 * @param {Animal-attackerPosition[]} array of attacker animals
 * @param {Animal-enemyPosition[]} array of enemy animals
 * @param {int-attackerCount} number of attacker animals
 * @param {int-attackerposition} position of attacher in array
 * @param {int-enemyCount} number of enemy animals
 * @param {int-enemyposition} position of enemy in array
 * @param {int-worldSize} size of map
 * @param {Cell-board[]} world map
 *
 * @return {void}
 */
void attack(Animal *attacker, Animal *enemy, Animal attackerPosition[], Animal enemyPosition[], int *attackerCount, int *attackerposition, int *enemyCount, int enemyposition, int worldSize, Cell board[][worldSize])
{
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};
    if (attacker->energyPoint >= 3 * attacker->gene.energyForMoving)
    {
        if (attacker->gene.attackPower == enemy->gene.defensePower)
        {
            return;
        }
        if (attacker->gene.attackPower > enemy->gene.defensePower)
        {
            attacker->energyPoint += enemy->energyPoint;
            attacker->energyPoint -= (3 * attacker->gene.energyForMoving);
            board[enemy->x][enemy->y] = defaultCell;
            delete_animal(enemyposition, enemyPosition, &enemyCount);
        }
        else
        {
            enemy->energyPoint += attacker->energyPoint;
            enemy->energyPoint -= (3 * enemy->gene.energyForMoving);
            board[attacker->x][attacker->y] = defaultCell;
            delete_animal(*attackerposition, attackerPosition, &attackerCount);
            --*attackerposition;
        }
    }
}