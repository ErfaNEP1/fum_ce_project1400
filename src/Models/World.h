typedef struct World {
    int size;
    int deadEndCount,heavenCount,foodCount,animalCount;
    char animalToControl[2];
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

void printFoodsDetails(int worldSize, struct Cell board[][worldSize]){
    for(int i=0; i<worldSize; i++){
        for(int j=0; j<worldSize;j++){
            if(strcmp(board[i][j].typePlace,"food") == 0){
                printf("food(%d,%d) : %d\n",i,j,board[i][j].foodPlace.energy);
            }
        }
    }
}