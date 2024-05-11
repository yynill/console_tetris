// main.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include "gameVariables.h"
#include "tile.h"
#include "shape.h"

int generateRandomNumber(int min, int max);
void renderGame(struct Tile board[HEIGHT][WIDTH], struct Shape activeShape);
struct Shape generateShape(struct Tile board[HEIGHT][WIDTH], int shapeIndex, int row, int col);
void initTile(struct Tile *tile, int row, int col, int entry);
int handleKeyInputs(struct Tile board[HEIGHT][WIDTH], struct Shape *activeShape);

int main()
{
    struct Tile board[HEIGHT][WIDTH];
    struct Shape activeShape;

    int nextShape = 1;
    int NextRandomShape;
    int ThisRandomShape;

    srand(time(NULL));

    // Fill in the board with initial tiles
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            initTile(&board[j][i], j, i, 0);
        }
    }

    // Draw initial active shape
    ThisRandomShape = generateRandomNumber(0, 6);
    NextRandomShape = generateRandomNumber(0, 6);

    int running = 1;
    while (running)
    {
        if (nextShape)
        {
            ThisRandomShape = NextRandomShape;
            NextRandomShape = generateRandomNumber(0, 6);
            nextShape = 0;

            activeShape = generateShape(board, ThisRandomShape, 3, 4);
        }

        running = handleKeyInputs(board, &activeShape);

        // Limit frame rate
        usleep(5 * 1000000 / 60);

        renderGame(board, activeShape);
    }

    return 0;
}

// to do
// if on floor, turn positions into solids (2) on board, and romeve from acrive shape and make new active shape
// also then detect with collisions with solid (2) blocks