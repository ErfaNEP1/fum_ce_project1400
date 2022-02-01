/**
 * cooperating given two animals
 * 
 * @param {Animal-helperanimal} the animal that gives its energy to another animal
 * @param {Animal-animal} the animal that receives energy from helperanimal
 * 
 * @return {void}
 */
void cooperation(Animal *helperanimal, Animal *animal)
{
    if (helperanimal->energyPoint - helperanimal->gene.energyForMoving >= 0)
    {
        animal->energyPoint += helperanimal->gene.energyForMoving;
        helperanimal->energyPoint -= helperanimal->gene.energyForMoving;
    }
}