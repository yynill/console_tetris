// gameFunctions.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "gameVariables.h"
#include "tile.h"
#include "shape.h"

int generateRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

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

int generateShape(struct Tile board[HEIGHT][WIDTH], int shapeIndex, int row, int col)
{
    const char *shape = tetromino[shapeIndex];

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

int handleKeyInputs()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Get the terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set the terminal to non-blocking mode
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Read input
    ch = getchar();

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch == 'q')
        return 0;
    else if (ch == 'w')
        printf("print: w\n");
    else if (ch == 's')
        printf("print: s\n");
    else if (ch == 'a')
        printf("print: a\n");
    else if (ch == 'd')
        printf("print: d\n");

    return 1;
}
