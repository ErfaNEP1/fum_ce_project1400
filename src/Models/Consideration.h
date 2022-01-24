double energyModifier(int CurrentEnergy, int MaximumEnergy)
{
    double x = (double)CurrentEnergy / (double)MaximumEnergy;
    return -1 * (pow((x - 1), 4)) + 1;
}
double energyModifierFood(int CurrentEnergy, int MaximumEnergy)
{
    double x = (double)CurrentEnergy / (double)MaximumEnergy;
    return -1 * (pow((x), 4)) + 1;
}


double distanceModifier(int distance)
{
    double x = (double)distance / 400;
    return -1 * (pow((x), 4)) + 1;
}