int minenergy(struct Genome gene){
    int MinEnergy=600;
    if(gene.energyForMoving < MinEnergy){
        MinEnergy = gene.energyForMoving;
    }
    else if(gene.energyForReproduction < MinEnergy){
        MinEnergy = gene.energyForReproduction;
    }
    else if(gene.attackPower < MinEnergy){
        MinEnergy = gene.attackPower;
    }
    else if(gene.defensePower < MinEnergy){
        MinEnergy = gene.defensePower;
    }
    return MinEnergy;
}