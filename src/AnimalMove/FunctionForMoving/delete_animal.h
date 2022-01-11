void delete_allied(int positionofallied, struct Animal alliedposition[],int **alliedcount){
    for(int k=positionofallied; k<(**alliedcount)-1; k++){
        alliedposition[k]=alliedposition[k+1];
    }
    (**alliedcount)--;
    return;

}