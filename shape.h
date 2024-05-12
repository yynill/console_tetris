// shape.h

#include "gameVariables.h"

#ifndef SHAPE_H
#define SHAPE_H

struct Shape
{
    int index; // Index of the shape in tetromino array
    int row;   // Row position of the top-left corner of the shape
    int col;   // Column position of the top-left corner of the shape
    int rotation;
    void (*moveDown)(struct Shape *shape);
    void (*moveLeft)(struct Shape *shape);
    void (*moveRight)(struct Shape *shape);
    void (*rotateShape)(struct Shape *shape);
};

void moveShapeDown(struct Shape *shape);
void moveShapeLeft(struct Shape *shape);
void moveShapeRight(struct Shape *shape);
void rotateShape(struct Shape *shape);

#endif

// if trasnoosed switch x and y in board / render