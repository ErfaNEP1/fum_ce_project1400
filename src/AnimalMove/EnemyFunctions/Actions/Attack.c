void attack(Animal *attacker, Animal *enemy, Animal attackerPosition[], Animal enemyPosition[], int *attacherCount, int attackerposition, int *enemyCount, int enemyposition, int worldSize, Cell board[][worldSize])
{
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."};
    if (attacker->energyPoint >= 3 * attacker->gene.energyForMoving)
    {
        if (attacker->gene.attackPower > enemy->gene.defensePower)
        {
            attacker->energyPoint += enemy->energyPoint;
            delete_animal(enemyposition, enemyPosition, &enemyCount);
            board[enemy->x][enemy->y] = defaultCell;
        }
        else if (enemy->gene.attackPower > attacker->gene.defensePower)
        {
            enemy->energyPoint += attacker->energyPoint;
            delete_animal(attackerposition, attackerPosition, &attacherCount);
            board[attacker->x][attacker->y] = defaultCell;
        }
    }
}