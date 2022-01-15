void delete_animal(int positionofallied, struct Animal animalposition[],int **animalcount){
    for(int k=positionofallied; k<(**animalcount)-1; k++){
        animalposition[k]=animalposition[k+1];
    }
    (**animalcount)--;
    return;

}

void delete_Food(int x, int y, struct Cell FoodCell[],int **Foodcount){
    int i;
    for (i = 0;i < (**Foodcount);i ++) {
        if (FoodCell[i].x == x && FoodCell[i].y == y) break;
    }
    for(int k=i; k<(**Foodcount)-1; k++){
        FoodCell[k]=FoodCell[k+1];
    }
    (**Foodcount)--;
    return;

}