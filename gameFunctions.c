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

void renderGame(struct Tile board[HEIGHT][WIDTH], struct Shape activeShape)
{
    // Set the whole board to 0
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            if (board[j][i].entry != 2)
            {
                board[j][i].entry = 0;
            }
        }
    }
    // update board
    const char *shape = tetromino[activeShape.index];

    int shapeRow = 0;
    for (int j = activeShape.row; j < activeShape.row + 4; j++)
    {
        int shapeCol = 0;
        for (int i = activeShape.col; i < activeShape.col + 4; i++)
        {
            if (shape[shapeRow * 4 + shapeCol] == 'X')
            {
                board[j][i].entry = 1;
            }
            shapeCol++;
        }
        shapeRow++;
    }

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
            else if (board[j][i].entry == 1)
            {
                printf("▓");
            }
            else if (board[j][i].entry == 2)
            {
                printf("▒");
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

struct Shape generateShape(struct Tile board[HEIGHT][WIDTH], int shapeIndex, int row, int col)
{
    struct Shape newShape;

    // check if row and col are valid
    if (row >= HEIGHT - 4 || col >= WIDTH - 4)
    {
        // Return an empty shape indicating failure
        newShape.index = -1;
        return newShape;
    }

    newShape.moveDown = &moveShapeDown;
    newShape.moveLeft = &moveShapeLeft;
    newShape.moveRight = &moveShapeRight;

    newShape.index = shapeIndex;
    newShape.row = row;
    newShape.col = col;

    return newShape;
}

int handleKeyInputs(struct Tile board[HEIGHT][WIDTH], struct Shape *activeShape)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    // store (i, j) to check if it has collision later
    struct Point
    {
        int x;
        int y;
    };

    struct Point points[4];
    int pointCount = 0;

    const char *shape = tetromino[activeShape->index];
    int shapeRow = 0;
    for (int j = activeShape->row; j < activeShape->row + 4; j++)
    {
        int shapeCol = 0;
        for (int i = activeShape->col; i < activeShape->col + 4; i++)
        {
            if (shape[shapeRow * 4 + shapeCol] == 'X')
            {
                points[pointCount].x = i;
                points[pointCount].y = j;
                pointCount++;
            }
            shapeCol++;
        }
        shapeRow++;
    }

    printf("Points list:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Point %d: (%d, %d)\n", i + 1, points[i].x, points[i].y);
    }

    // check for X collisions
    int moveRightBlockage = 0;
    int moveLeftBlockage = 0;

    int tetrisCollision = 0;

    for (int i = 0; i < 4; i++)
    {
        if (points[i].x == WIDTH - 1)
        {
            moveRightBlockage = 1;
        }
        if (points[i].x == 0)
        {
            moveLeftBlockage = 1;
        }
        if (points[i].y == HEIGHT - 1)
        {
            tetrisCollision = 1;
        }
    }

    if (tetrisCollision)
    {
        for (int i = 0; i < 4; i++)
        {
            board[points[i].y][points[i].x].entry = 2;
        }
    }

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
        activeShape->moveDown(activeShape);
    else if (ch == 'a' && !moveLeftBlockage)
        activeShape->moveLeft(activeShape);
    else if (ch == 'd' && !moveRightBlockage)
        activeShape->moveRight(activeShape);

    printf("active shape row: %d, col: %d\n", activeShape->row, activeShape->col);

    return 1;
}
