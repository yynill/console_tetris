// tile.c

#include "tile.h"
#include <stdio.h>

void initTile(struct Tile *tile, int row, int col, int entry)
{
    tile->row = row;
    tile->col = col;
    tile->entry = entry;
}

void printTile(struct Tile *tile)
{
    printf("Row: %d, Col: %d, Entry: %d\n", tile->row, tile->col, tile->entry);
}

int getEntry(struct Tile *tile)
{
    return tile->entry;
}

void setEntry(struct Tile *tile, int entry)
{
    tile->entry = entry;
}
