#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Food.h"
#include "Models/Cell.h"
#include "Models/World.h"

int main(){
    int worldSize;
    World world;
    scanf("%d\n",&worldSize);
    world.size = worldSize;

    Cell board[world.size][world.size];

    initWorld(world,world.size,board);
    char *tok;
    char line[100];
    while (fgets(line, 100, stdin) != NULL && line[0] != '\n') {
        char lineCopy[100];
        strcpy(lineCopy, line);
        tok = strtok(line," \n");
        
        if (*tok == '#'){
            Cell deadEndCell = {
                .typePlace = "dead_end",
                .identifierPlace = "#"
            };
            int nu_deadend;
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &nu_deadend);
            tok = strtok(NULL," \n");
    
            for (int i = 0; i < nu_deadend; i++) {
                int x, y;
    
                sscanf(tok, "(%d,%d)", &x, &y);
                board[x][y] = deadEndCell;
    
                tok = strchr(tok,')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }else if(*tok == 'H'){
            Cell heavenCell = {
                .typePlace = "heaven",
                .identifierPlace = "H"
            };
            int nu_heaven;
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &nu_heaven);
            tok = strtok(NULL," \n");
    
            for (int i = 0; i < nu_heaven; i++) {
                int x, y;
    
                sscanf(tok, "(%d,%d)", &x, &y);
                board[x][y] = heavenCell;
    
                tok = strchr(tok,')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }
        else if(*tok == 'F'){
            tok = strtok(NULL," ");
            int energy;
            sscanf(tok,"%d",&energy);
            Food energyCell = {
                .energy = energy
            };

            Cell foodCell = {
                .typePlace = "food",
                .identifierPlace = "F",
                .foodPlace = energyCell
            };

            tok = strtok(NULL," ");

            int x, y;
            sscanf(tok,"(%d,%d)", &x, &y);
            board[x][y] = foodCell;
            
        }else if (isalpha(*tok) && strlen(lineCopy) > 3) {
            Cell typeanimal = {
                .typePlace = "animal",
                .identifierPlace = *tok,
            };
            int nu_typeanimal;
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &nu_typeanimal);
            tok = strtok(NULL," \n");
    
            for (int i = 0; i < nu_typeanimal; i++) {
                int x, y;
    
                sscanf(tok, "(%d,%d)", &x, &y);
                board[x][y] = typeanimal;
    
                tok = strchr(tok,')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }else if(isalpha(*tok) && strlen(lineCopy) < 3){
            snprintf(world.animalToControl,2,tok);
        }
    }

    printWorld(world.size,board);
    printf("\n");
    printFoodsDetails(world.size,board);
    printf("\n");
    printf("%s",world.animalToControl);
    
    return 0;

}