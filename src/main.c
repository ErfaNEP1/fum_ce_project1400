#include <stdio.h>
#include "Models/Genome.h"
#include "Models/Animal.h"

int main(){
    Animal animal;
    animal.healthPoint = 5;

    printf("%d", animal.healthPoint);
}