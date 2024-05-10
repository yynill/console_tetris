// shape.h

#ifndef SHAPE_H
#define SHAPE_H

struct Shape
{
    int index; // Index of the shape in tetromino array
    int row;   // Row position of the top-left corner of the shape
    int col;   // Column position of the top-left corner of the shape
};

#endif