// gameFunctions.c

#include <stdio.h>
#include <stdlib.h>
#include "gameVariables.h"
#include "tile.h"

const char tetromino[7][17] = {
    "..X...X...X...X.", // I-shape - 0
    "..X..XX...X.....", // J-shape - 1
    ".....XX..XX.....", // O-shape - 2
    "..X..XX..X......", // L-shape - 3
    ".X...XX...X.....", // S-shape - 4
    ".X...X...XX.....", // T-shape - 5
    "..X...X..XX....."  // Z-shape - 6
};

void renderGame(struct Tile board[HEIGHT][WIDTH])
{
    // Clear the screen to redraw the game state
    printf("\033[H\033[J");

    // Draw the top border
    printf("┌");
    for (int i = 0; i < WIDTH; i++)
    {
        printf("─");
    }
    printf("┐\n");

    // Draw the game field
    for (int j = 0; j < HEIGHT; j++)
    {
        printf("│");
        for (int i = 0; i < WIDTH; i++)
        {
            if (board[j][i].entry == 0)
            {
                printf(" ");
            }
            else
            {
                printf("▓");
            }
        }
        printf("│\n");
    }

    // Draw the bottom border
    printf("└");
    for (int i = 0; i < WIDTH; i++)
    {
        printf("─");
    }
    printf("┘\n");
}

int drawShape(struct Tile board[HEIGHT][WIDTH], int shapeIndex, int row, int col)
{
    const char *shape = tetromino[shapeIndex];
    // . . X .
    // . . X .
    // . . X .
    // . . X .

    // check if row and col are valid
    if (row >= HEIGHT - 4 || col >= WIDTH - 4)
    {
        return 0;
    }

    // Draw the shape onto the board
    int shapeRow = 0;
    for (int j = row; j < row + 4; j++)
    {
        int shapeCol = 0;
        for (int i = col; i < col + 4; i++)
        {
            if (shape[shapeRow * 4 + shapeCol] == 'X')
            {
                // Set the corresponding cell in the board to indicate the shape
                board[j][i].entry = 1;
            }
            shapeCol++;
        }
        shapeRow++;
    }
    return 1;
}