#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "inc/helpers.h"
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

    world.foodCount = 0;
    world.animalCount = 0;

    while (fgets(line, 100, stdin) != NULL && line[0] != '\n') {
        char lineCopy[100];
        strcpy(lineCopy, line);
        tok = strtok(line," \n");
        
        if (*tok == '#'){
            Cell deadEndCell = {
                .typePlace = "dead_end",
                .identifierPlace = "#"
            };
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &world.deadEndCount);
            tok = strtok(NULL," \n");
    
            for (int i = 0; i < world.deadEndCount; i++) {
                int x, y;
                
                sscanf(tok, "(%d,%d)", &x, &y);

                deadEndCell.x = x; 
                deadEndCell.y = y;

                board[x][y] = deadEndCell;
                world.deadEnds[i] = deadEndCell;
    
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
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &world.heavenCount);
            tok = strtok(NULL," \n");
    
            for (int i = 0; i < world.heavenCount; i++) {
                int x, y;
                
                sscanf(tok, "(%d,%d)", &x, &y);

                heavenCell.x = x;
                heavenCell.y = y;

                board[x][y] = heavenCell;
                world.heavenCell[i] = heavenCell;
    
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

            foodCell.x = x;
            foodCell.y = y;

            board[x][y] = foodCell;
            world.foodCell[world.foodCount] = foodCell;

            world.foodCount++;
            
        }else if (isalpha(*tok) && strlen(lineCopy) > 3) {
            Cell typeanimal = {
                .typePlace = "animal",
                .identifierPlace = *tok,
            };
            int nu_typeanimal;
            
            tok = strtok(NULL," \n");
            sscanf(tok, "%d", &nu_typeanimal);
            world.animalCount += nu_typeanimal;

            tok = strtok(NULL," \n");
    
            for (int i = 0; i < nu_typeanimal; i++) {
                int x, y;
    
                sscanf(tok, "(%d,%d)", &x, &y);

                typeanimal.x = x; 
                typeanimal.y = y;

                board[x][y] = typeanimal;
    
                tok = strchr(tok,')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }else if(isalpha(*tok) && strlen(lineCopy) < 3){
            snprintf(world.animalToControl,2,tok);
            break;
        }
    }




    

    printf("\n");
    printWorld(world.size,board);
    textcolor(7);
    printf("\n");
    printWorldDetails(world);
    printf("\n");
    printf("%s",world.animalToControl);
    printf("\n");

    textcolor(6);
    printf("THE GAME HAS STARTED, TO CANCEL THE GAME CLICK ON \"ESC\" \n");

    int ch;

    while ((ch = _getch()) != 27)
    {
        if (ch == 0 || ch == 224){
            switch (_getch ())
            {
                case 72:
                    printf("UP ARROW");
                    printf("\n");
                    break;

                case 80:
                    printf("DOWN ARROW");
                    printf("\n");
                    break;
                case 77:
                    printf("RIGHT ARROW");
                    printf("\n");
                    break;
                case 75:
                    printf("LEFT ARROW");
                    printf("\n");
                    break;
                default:
                    break;
            }

        }
    }
    
    return 0;

}