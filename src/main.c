#include <stdio.h>
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Food.h"
#include "Models/Cell.h"
#include "Models/World.h"

#define boardsize 20

int main(){

    World game;
    scanf("%d",game.x);
    game.y = game.x;
    char board[boardsize][boardsize];
    for (int i = 0;i < game.x;i ++) {
        for (int j = 0;j < game.y;j ++) {
            board[i][j] = '.';
        }
    }
    return 0;
}