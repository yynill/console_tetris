// main.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "gameVariables.h"
#include "tile.h"

void renderGame(struct Tile board[HEIGHT][WIDTH]);
int drawShape(struct Tile board[HEIGHT][WIDTH], int shapeIndex, int row, int col);
void initTile(struct Tile *tile, int row, int col, int entry);

int main()
{
    struct Tile board[HEIGHT][WIDTH];

    // Fill in the board with initial tiles
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            initTile(&board[j][i], j, i, 0);
        }
    }

    int x = drawShape(board, 2, 3, 4); // Example: Drawing I-shape at row 0, column 3

    int running = 1;
    while (running)
    {
        renderGame(board);
        // Limit frame rate
        usleep(5 * 1000000 / 60);
    }

    return 0;
}
