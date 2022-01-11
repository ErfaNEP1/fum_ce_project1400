int minenergy(struct Genome gene){
    int MinEnergy=600;
    if(gene.energyForMoving < MinEnergy){
        MinEnergy = gene.energyForMoving;
    }
    if(gene.energyForReproduction < MinEnergy){
        MinEnergy = gene.energyForReproduction;
    }
    if(gene.attackPower < MinEnergy){
        MinEnergy = gene.attackPower;
    }
    if(gene.defensePower < MinEnergy){
        MinEnergy = gene.defensePower;
    }
    return MinEnergy;
}