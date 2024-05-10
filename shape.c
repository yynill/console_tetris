// shape.c

#include "shape.h"
#include "gameVariables.h"
#include <stdio.h>

void moveShapeDown(struct Shape *shape)
{
    shape->row++;
}

void moveShapeLeft(struct Shape *shape)
{
    shape->col--;
}

void moveShapeRight(struct Shape *shape)
{
    shape->col++;
}

int isShapeOnGround(struct Tile board[HEIGHT][WIDTH], struct Shape shape) {}

int shapeCollisio() {}
