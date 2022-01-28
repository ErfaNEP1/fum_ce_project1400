double MoveToHeavenScore(int distance, int energy, int maxEnergy, int EnergyForMove)
{
    int weight = 5;
    double distanceScore = distanceModifier(distance);
    // double energyScore = energyModifier(energy, maxEnergy);
    int energyPower = (distance * EnergyForMove > energy) ? -1 : 2;
    return weight * distanceScore * energyPower;
}

double MoveToFoodScore(int distance, int energy, int maxEnergy)
{
    int weight = 4;
    double distanceScore = distanceModifier(distance);
    double energyScore = energyModifierFood(energy, maxEnergy);
    return weight * distanceScore * energyScore;
}