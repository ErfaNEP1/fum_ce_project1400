/**
 * calculates the energy score
 * 
 * @param {int-CurrentEnergy} current animal energy
 * @param {int-MaximumEnergy} energy that this animal was born with
 * 
 * @return {double-score}
 */
double energyModifier(int CurrentEnergy, int MaximumEnergy)
{
    double x = (double)CurrentEnergy / (double)MaximumEnergy;
    return -1 * (pow((x - 1), 4)) + 1;
}
/**
 * calculates the energy score for food
 * 
 * @param {int-CurrentEnergy} current animal energy
 * @param {int-MaximumEnergy} energy that this animal was born with
 * 
 * @return {double-score}
 */
double energyModifierFood(int CurrentEnergy, int MaximumEnergy)
{
    double x = (double)CurrentEnergy / (double)MaximumEnergy;
    return -1 * (pow((x), 4)) + 1;
}
/**
 * calculates the distance score
 * 
 * @param {int-distance} distance to object
 * @param {int-worldSize} size of the map
 * 
 * @return {double-score}
 */
double distanceModifier(int distance, int worldSize)
{
    // printf("DISTANCE : %d\n",distance);
    double x = (double)distance / (worldSize * worldSize);
    return (-1 * pow(x, 4)) + 1;
}