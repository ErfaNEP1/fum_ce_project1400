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
double ReproductScore(int distance,int motherEnergy,int fatherEnergy,int energyForReproduceMother,int energyForReproduceFather){
    int weight = 3;
    int energy_distance = (motherEnergy >= (energyForReproduceMother / 2) && fatherEnergy >= (energyForReproduceFather / 2) && distance < 2) ? 1 : -3;
    return weight * energy_distance;
}