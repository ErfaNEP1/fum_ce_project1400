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
#include "playermove/typeanimalcount.h"
#include "playermove/animalTocontrol.h"

int main()
{
    int worldSize;
    World world;
    scanf("%d\n", &worldSize);
    world.size = worldSize;

    Cell board[world.size][world.size];

    initWorld(world, world.size, board);
    char *tok;
    char line[100];

    world.foodCount = 0;
    world.animalCount = 0;

    while (fgets(line, 100, stdin) != NULL && line[0] != '\n')
    {
        char lineCopy[100];
        strcpy(lineCopy, line);
        tok = strtok(line, " \n");

        if (*tok == '#')
        {
            Cell deadEndCell = {
                .typePlace = "dead_end",
                .identifierPlace = "#"};
            tok = strtok(NULL, " \n");
            sscanf(tok, "%d", &world.deadEndCount);
            tok = strtok(NULL, " \n");

            for (int i = 0; i < world.deadEndCount; i++)
            {
                int x, y;

                sscanf(tok, "(%d,%d)", &x, &y);

                deadEndCell.x = x;
                deadEndCell.y = y;

                board[x][y] = deadEndCell;
                world.deadEnds[i] = deadEndCell;

                tok = strchr(tok, ')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }
        else if (*tok == 'H')
        {
            Cell heavenCell = {
                .typePlace = "heaven",
                .identifierPlace = "H"};
            tok = strtok(NULL, " \n");
            sscanf(tok, "%d", &world.heavenCount);
            tok = strtok(NULL, " \n");

            for (int i = 0; i < world.heavenCount; i++)
            {
                int x, y;

                sscanf(tok, "(%d,%d)", &x, &y);

                heavenCell.x = x;
                heavenCell.y = y;

                board[x][y] = heavenCell;
                world.heavenCell[i] = heavenCell;

                tok = strchr(tok, ')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }
        else if (*tok == 'F')
        {

            tok = strtok(NULL, " ");
            int energy;
            sscanf(tok, "%d", &energy);
            Food energyCell = {
                .energy = energy};

            Cell foodCell = {
                .typePlace = "food",
                .identifierPlace = "F",
                .foodPlace = energyCell};

            tok = strtok(NULL, " ");

            int x, y;
            sscanf(tok, "(%d,%d)", &x, &y);

            foodCell.x = x;
            foodCell.y = y;

            board[x][y] = foodCell;
            world.foodCell[world.foodCount] = foodCell;

            world.foodCount++;
        }
        else if (isalpha(*tok) && strlen(lineCopy) > 3)
        {
            Cell typeanimal = {
                .typePlace = "animal",
                .identifierPlace = *tok,
            };
            int nu_typeanimal;

            tok = strtok(NULL, " \n");
            sscanf(tok, "%d", &nu_typeanimal);
            world.animalCount += nu_typeanimal;

            tok = strtok(NULL, " \n");

            for (int i = 0; i < nu_typeanimal; i++)
            {
                int x, y;

                sscanf(tok, "(%d,%d)", &x, &y);

                typeanimal.x = x;
                typeanimal.y = y;

                board[x][y] = typeanimal;

                tok = strchr(tok, ')');
                if (tok == NULL)
                    break;
                ++tok;
            }
        }
        else if (isalpha(*tok) && strlen(lineCopy) < 3)
        {
            snprintf(world.animalToControl, 2, tok);
            break;
        }
    }

    printf("\n");
    int number = searchTypeanimalposition(world.animalToControl, world.size, board, world.animalposition);

    textcolor(6);
    printf("THE GAME HAS STARTED, TO CANCEL THE GAME CLICK ON \"ESC\" \n");
    printWorld(world.size, board);
    textcolor(7);
    int ch;
    textcolor(2);

    while ((ch = getch()) != 27 && ch != 224)
    {
        if (ch == 224 || ch == 0){
            for (int i = 0; i < number; i++){
                    int clickedKey = getch();
                    if(clickedKey != 0){
                        animalTocontrol(world.animalToControl, number, world.size, board, world.animalposition[i].x, world.animalposition[i].y, i, world.animalposition,clickedKey);
                        // clearScreen();
                        printWorld(world.size, board);
                    }
                    if(i != number-1)
                        getch();
            }

            
            printf("player input is done ! %d\n",ch);

            // implement AI


        }
    }

    return 0;
}