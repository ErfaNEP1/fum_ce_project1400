#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include "GameFunctions.h"

int main()
{
    // ======================= Getting World Size ======================= //
    int worldSize;
    World world;
    FILE *input;
    input = fopen("map_phase1.txt", "r");
    fscanf(input, "%d", &worldSize);
    fclose(input);
    world.size = worldSize;
    // ======================= End Of Getting World Size ======================= //

    // ======================= Creating Game's Board ======================= //
    Cell board[world.size][world.size];
    initWorld(world, world.size, board);
    // ======================= End Of Creating Game's Board ======================= //

    // ======================= Input Map Details ======================= //
    char *tok;
    char line[256];

    world.foodCount = 0;
    world.animalCount = 0;
    FILE *input2;
    input2 = fopen("map_phase1.txt", "r");
    // Read input file line by line
    while (fgets(line, 256, input2))
    {
        // Copy the line string into another string (because strtok changes the input string)
        char lineCopy[100];
        strcpy(lineCopy, trim(line));
        // Getting first character of each line
        tok = strtok(line, " \n");
        // Getting DeadEnds
        if (*tok == '#')
        {
            inputDeadEnds(worldSize, tok, &world, board);
        }
        // Getting Heavens
        else if (*tok == 'H')
        {
            inputHeavens(worldSize, tok, &world, board);
        }
        // Getting foods
        else if (*tok == 'F')
        {
            inputFood(worldSize, tok, &world, board);
        }
        // Getting animals' info
        else if (isalpha(*tok) && strlen(lineCopy) > 3 && strchr(lineCopy, '$') == NULL)
        {
            inputAnimals(worldSize, tok, &world, board);
        }
        // Animals' Genome
        else if (isalpha(*tok) && strlen(lineCopy) > 3 && strchr(lineCopy, '$') != NULL)
        {
            inputGenome(worldSize, tok, &world, board);
        }
        // Get controlled animal
        else if (isalpha(*tok) && strlen(lineCopy) < 3)
        {
            snprintf(world.animalToControl, 2, tok);
        }
    }
    // ======================= End Of Input Map Details ======================= //

    // ======================= Preprations For Start ======================= //
    // printFoodsDetails(world.size, board);
    // printf("\n");
    // printWorldDetails(world);
    // printf("\n");
    // printWorld(world.size, board, 0, world);
    // printf("\n");
    // printf("%s", world.animalToControl);

    // Allied Animals Count + Storing each animal in World structure
    int nPlayer = saveAnimalinfo(&world, world.animalToControl, world.size, board, world.alliedanimalposition, world.enemyanimalposition);
    int nEnemy = world.animalCount - nPlayer;

    // textcolor(6);
    // printWorld(world.size, board, 0, world);
    // textcolor(13);
    // clearScreen();

    printf("\nSTART !!! ( Move With Arrow Keys. ) ( PRESS \"ESC\" TO EXIT )\n");
    printWorld(world.size, board, 0, world);

    int ch;
    int winSwitch = 0;
    // ======================= End of Preprations For Start ======================= //

    // ======================= Start Game ======================= //

    // ch == 27 => ESC
    int num,numofplayer = -1;
    while ((ch = get_code()) != 27 && winSwitch == 0)
    {
        // Start Player Moves
        num = initPlayerMove(&world, ch, nPlayer, worldSize, &winSwitch, board);
        // Check if game's finished or not
        if (winSwitch == 1)
        {
            numofplayer = num;
            snprintf(world.winner, 2, "%s", world.animalToControl);
            break;
        }
        textcolor(5);
        printf("PLAYER TURN DONE, AI TURN.\n");
        clearScreen();
        // Player Moves End

        // Start AI Moves
        initAImovie(&world, nEnemy, worldSize, &winSwitch, board);
        // End of AI Moves

        // Check if game's finished
        if (winSwitch == 1)
        {
            break;
        }
        else
        {
            // preprations for the next round
            printWorld(world.size, board, 0, world);
            textcolor(5);
            printf("ROUND FINISHED, WAIT FOR 3 SECONDS\n");
            for (int i = 0; i < 3; i++)
            {
                sleep(1000);
                printf("%d ", i + 1);
            }
            clearScreen();
            printf("NEXT ROUND STARTED, MOVE !\n");
            printWorld(world.size, board, 0, world);
            if (world.alliedCount == 0 && world.enemyCount == 0) {
                textcolor(14);
                printf("THE GAME WAS TIED\n");
                break;
            }
        }
        // clearScreen();
        // printWorld(world.size, board, 0, world);
    }
    // ======================= End of Game ======================= //

    // ======================= Printing the Winner ======================= //
    if (winSwitch == 1){
        clearScreen();
        printWorld(world.size, board, numofplayer, world);
        textcolor(2);
        printf("PLAYER %s WON THE GAME !", world.winner);
    }
    // ======================= End of Printing the Winner ======================= //
    return 0;
}