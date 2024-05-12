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

void rotateShape(struct Shape *shape)
{
    shape->rotation = (shape->rotation + 1) % 4;
}
