#include <stdio.h>
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Food.h"
#include "Models/Cell.h"
#include "Models/World.h"

int main(){

    World game;
    scanf("%d",game.x);
    game.y = game.x;
    Cell board[game.x][game.y];
    for (int i = 0;i < game.x;i ++) {
        for (int j = 0;j < game.y;j ++) {
            board[i][j] = '.';
        }
    }
    return 0;
}