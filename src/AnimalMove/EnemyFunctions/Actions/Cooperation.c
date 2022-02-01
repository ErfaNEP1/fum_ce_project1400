void cooperation(Animal *helperanimal, Animal *animal)
{
    if (helperanimal->energyPoint - helperanimal->gene.energyForMoving >= 0)
    {
        animal->energyPoint += helperanimal->gene.energyForMoving;
        helperanimal->energyPoint -= helperanimal->gene.energyForMoving;
    }
}