#include <stdio.h>
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Cell.cpp"
#include "Models/Food.cpp"


int main(){
    Animal animal;
    animal.healthPoint = 5;

    printf("%d ", animal.healthPoint);
}