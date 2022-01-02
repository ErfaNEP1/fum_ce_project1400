#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include "inc/helpers.h"
#include "Models/Point.h"
#include "Models/Genome.h"
#include "Models/Animal.h"
#include "Models/Food.h"
#include "Models/Cell.h"
#include "Models/World.h"
#include "enemymove/enemymove.h"
#include "enemymove/move.h"
#include "playermove/typeanimalcount.h"
#include "playermove/animalTocontrol.h"

int main()
{
    int worldSize;
    World world;
    FILE * input;
    input = fopen("input.txt", "r");
    fscanf(input,"%d",&worldSize);
    fclose(input);

    world.size = worldSize;
    
    Cell board[world.size][world.size];
    
    initWorld(world, world.size, board);
    char *tok;
    char line[256];

    world.foodCount = 0;
    world.animalCount = 0;
    FILE * input2;
    input2 = fopen("input.txt", "r");
    while (fgets(line, 256, input2))
    {
        char lineCopy[100];
        strcpy(lineCopy, trim(line));
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
        else if (isalpha(*tok) && strlen(lineCopy) > 3 && strchr(lineCopy, '$') == NULL)
        {
            Cell typeanimal = {
                .typePlace = "animal",
                .identifierPlace = *tok,
                .animalPlace.pointindex = -1
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
        else if (isalpha(*tok) && strlen(lineCopy) > 3 && strchr(lineCopy, '$') != NULL)
        {
            int energy;
            Genome gene = {
                .character = *tok
            };

            tok = strtok(NULL, " \n");
            sscanf(tok, "%d", &energy);
            
            tok = strtok(NULL, " \n");

            for (int i = 0; i < 5; i++)
            {
                int gen;

                sscanf(tok, "%d", &gen);

                tok = strchr(tok, '$');

                ++tok;

                if(i == 0){
                    gene.energyForMoving = gen;
                }else if(i == 1){
                    gene.cellsToMove = gen;
                }else if(i == 2){
                    gene.energyForReproduction = gen;
                }else if(i == 3){
                    gene.attackPower = gen;
                }else if(i == 4){
                    gene.defensePower = gen;
                }
            }
            giveCharactersGenome(gene,gene.character, world.size, board, energy);
            
            
        }
        else if (isalpha(*tok) && strlen(lineCopy) < 3)
        {
            snprintf(world.animalToControl, 2, tok);
        }else{

        }
    }

    
    printFoodsDetails(world.size,board);
    printf("\n");
    printWorldDetails(world);
    printf("\n");
    printWorld(world.size,board,0,world);
    printf("\n");
    printf("%s",world.animalToControl);
    int nPlayer = searchTypeanimalposition(world, world.animalToControl, world.size, board, world.alliedanimalposition, world.enemyanimalposition);
    int nEnemy = world.animalCount - nPlayer;

    textcolor(6);
    printWorld(world.size, board, 0, world);
    textcolor(6);
    clearScreen();

    printf("\nSTART !!! ( Move With Arrow Keys. ) ( PRESS \"ESC\" TO EXIT )\n");
    printWorld(world.size, board, 0, world);

    textcolor(7);
    int ch;
    textcolor(2);
    int winSwitch = 0;

    while ((ch = get_code()) != 27 && winSwitch == 0)
    {
            for (int i = 0; i < nPlayer; i++)
            {
                int clickedKey = ch;
                if (clickedKey != 0)
                {
                    i = animalTocontrol(&winSwitch, world.animalToControl, nPlayer, world.size, board, world.alliedanimalposition[i].x, world.alliedanimalposition[i].y, i, world.alliedanimalposition, clickedKey, world.alliedanimalposition[i].gene.cellsToMove);
                    printWorld(world.size, board, i, world);
                }
                if (i != nPlayer - 1)
                    ch = get_code();
            }

            if (winSwitch == 1)
            {
                snprintf(world.winner, 2, "%s", world.animalToControl);
                break;
            }

            printf("PLAYER TURN DONE, AI TURN.\n");
            clearScreen();

            // implement AI
            for (int i = 0; i < nEnemy; i++)
            {
                // printf("WAIT FOR ENEMY TO MOVE");
                int mindist = FindtheClosestWaytoH(world.enemyanimalposition[i].x, world.enemyanimalposition[i].y, world.heavenCell, world.heavenCount);
                struct QueueNode items[world.size * world.size];
                int front = -1, rear = -1;
                int *frontPtr = &front, *rearPtr = &rear;
                struct Point start = {
                    .x = world.enemyanimalposition[i].x,
                    .y = world.enemyanimalposition[i].y};
                struct Point end = {
                    .x = world.heavenCell[mindist].x,
                    .y = world.heavenCell[mindist].y};
                int n;
                if (world.enemyanimalposition[i].pointindex == -1)
                {
                    n = printPath(world.size, board, start, end, world.enemyanimalposition[i].pointTomove, items, frontPtr, rearPtr);
                    if (n != -1)
                    {
                        reverse(world.enemyanimalposition[i].pointTomove, n);
                        n--;
                        world.enemyanimalposition[i].pointindex++;

                        move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].x, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].y, world.enemyanimalposition, i);
                        if (winSwitch == 1)
                        {
                            snprintf(world.winner, 2, "%s", board[world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].x][world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].y].identifierPlace);
                            break;
                        }
                    }
                    else
                    {
                        //Random Move
                        if ((*board[start.x + 1][start.y].identifierPlace == '.' || *board[start.x + 1][start.y].identifierPlace == 'F') && isValid(start.x + 1, start.y, world.size))
                        {
                            move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x + 1, start.y, world.enemyanimalposition, i);
                        }
                        else if ((*board[start.x - 1][start.y].identifierPlace == '.' || *board[start.x - 1][start.y].identifierPlace == 'F') && isValid(start.x - 1, start.y, world.size))
                        {
                            move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x - 1, start.y, world.enemyanimalposition, i);
                        }
                        else if ((*board[start.x][start.y + 1].identifierPlace == '.' || *board[start.x][start.y + 1].identifierPlace == 'F') && isValid(start.x, start.y + 1, world.size))
                        {
                            move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y + 1, world.enemyanimalposition, i);
                        }
                        else if ((*board[start.x][start.y - 1].identifierPlace == '.' || *board[start.x][start.y - 1].identifierPlace == 'F') && isValid(start.x, start.y - 1, world.size))
                        {
                            move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, start.x, start.y - 1, world.enemyanimalposition, i);
                        }
                    }
                }
                else
                {
                    world.enemyanimalposition[i].pointindex++;
                    if (check(worldSize, board, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].x, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].y))
                    {
                        move(world, &winSwitch, worldSize, board, board[start.x][start.y].identifierPlace, start.x, start.y, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].x, world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].y, world.enemyanimalposition, i);
                        if (winSwitch == 1)
                        {
                            snprintf(world.winner, 2, "%s", board[world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].x][world.enemyanimalposition[i].pointTomove[world.enemyanimalposition[i].pointindex].y].identifierPlace);
                            break;
                        }
                    }
                    else
                    {
                        world.enemyanimalposition[i].pointindex = -1;
                        i--;
                    }
                }
                printf("\n");
                clearScreen();
            }
            if (winSwitch == 1)
            {
                break;
            }
            else
            {
                printWorld(world.size, board, 0, world);
                printf("ROUND FINISHED, WAIT FOR 3 SECONDS\n");
                for (int i = 0; i < 3; i++)
                {
                    sleep(1000);
                    printf("%d ", i + 1);
                }
                clearScreen();
                printf("NEXT ROUND STARTED, MOVE !\n");
                printWorld(world.size, board, 0, world);
            }
    clearScreen();
    printWorld(world.size, board, 0, world);
    textcolor(6);
    }
    if (winSwitch == 1)
        printf("PLAYER %s WON THE GAME !", world.winner);

    return 0;
}