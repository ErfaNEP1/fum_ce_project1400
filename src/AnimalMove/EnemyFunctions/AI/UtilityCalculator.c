/**
 * Calculates the MoveToHeaven Action Score
 * 
 * @param {int-distance} current animal distance to closest heaven cell
 * @param {int-energy} current animal energy
 * @param {int-maxEnergy} energy that this animal was born with
 * @param {int-EnergyForMove} energy needed for each step
 * @param {int-worldSize} size of the map
 * 
 * @return {double-score}
 */
double MoveToHeavenScore(int distance, int energy, int maxEnergy, int EnergyForMove, int worldSize)
{
    int weight = 5;
    double distanceScore = distanceModifier(distance, worldSize);
    int energyPower = (distance * EnergyForMove > energy) ? -1 : 2;
    return weight * distanceScore * energyPower;
}
/**
 * Calculates the MoveToFood Action Score
 * 
 * @param {int-distance} current animal distance to closest food
 * @param {int-energy} current animal energy
 * @param {int-maxEnergy} energy that this animal was born with
 * @param {int-worldSize} size of the map
 * 
 * @return {double-score}
 */
double MoveToFoodScore(int distance, int energy, int maxEnergy, int worldSize)
{
    int weight = 4;
    double distanceScore = distanceModifier(distance, worldSize);
    double energyScore = energyModifierFood(energy, maxEnergy);
    return weight * distanceScore * energyScore;
}
/**
 * Calculates the Reproduction Action Score
 * 
 * @param {int-distance} current animal distance to closest ally
 * @param {int-motherEnergy} mother's energy
 * @param {int-fatherEnergy} father's energy
 * @param {int-energyForReproduce} energy needed to reproduce according to genome
 * 
 * @return {double-score}
 */
double ReproductScore(int distance, int motherEnergy, int fatherEnergy, int energyForReproduceMother, int energyForReproduceFather)
{
    int weight = 2;
    int energy_distance = (motherEnergy >= (energyForReproduceMother / 2) && fatherEnergy >= (energyForReproduceFather / 2) && distance < 2) ? 1 : -3;
    return weight * energy_distance;
}

/**
 * Calculates the Attack Action Score
 * 
 * @param {int-distance} current attacker distance to closest enemy
 * @param {int-attackerEnergy} attacker's energy
 * @param {int-enemyEnergy} enemy's energy
 * @param {int-AttackerEnergyToAttack} energy needed to attack
 * @param {int-AttackerPower} Attack power of Attacker
 * @param {int-DefenderPower} Defense power of Defender
 * 
 * @return {double-score}
 */
double AttackScore(int distance, int attackerEnergy, int enemyEnergy, int AttackerEnergyToAttack, int AttackerPower, int DefenderPower)
{
    int weight = 4;
    int energy_distance = (attackerEnergy >= AttackerEnergyToAttack && AttackerPower > DefenderPower) ? 1 : -3;
    int enemy_energy = energyModifier(enemyEnergy,600);
    if(distance >= 2){
        return -999;
    }
    return weight * energy_distance * enemy_energy;
}
/**
 * Calculates the Co-op Action Score
 * 
 * @param {int-distance} distance of closest teammate to heaven from heaven
 * @param {int-EnergyNeededToMove} Energy Needed to get to heaven
 * @param {int-teammateEnergy} teammate energy
 * @param {int-helperEnergy} helper energy
 * 
 * @return {double-score}
 */
double CoopScore(int distance, int EnergyNeededToMove, int teammateEnergy, int helperEnergy,int worldSize)
{
    int weight = 4;
    
    int energy_distance = (teammateEnergy < EnergyNeededToMove * distance && teammateEnergy > EnergyNeededToMove && distance < 6) ? 1 : -3;
    double distanceScore = distanceModifier(distance,worldSize);
    
    return weight * energy_distance * distanceScore;
}