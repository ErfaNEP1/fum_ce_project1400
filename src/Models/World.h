typedef struct World {
    int size;
    int deadEndCount,heavenCount,foodCount,animalCount;
    Animal animalToControl;
} World;


void initWorld(struct World world,int worldSize, struct Cell board[][worldSize]){
    Cell defaultCell = {
        .typePlace = "default",
        .identifierPlace = "."
    };
    
    for(int i=0; i<worldSize; i++){
        for(int j=0; j<worldSize;j++){
            board[i][j] = defaultCell;
        }
    }
}

void printWorld(int worldSize, struct Cell board[][worldSize]){
    for(int i=0; i<worldSize; i++){
        for(int j=0; j<worldSize;j++){
            printf("%s ",board[i][j].identifierPlace);
        }
        printf("\n");
    }
}