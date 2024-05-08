// tile.h

#ifndef TILE_H
#define TILE_H

struct Tile
{
    int row;
    int col;
    char entry;
};

void initTile(struct Tile *tile, int row, int col, int entry);
void printTile(struct Tile *tile);
int getEntry(struct Tile *tile);
void setEntry(struct Tile *tile, int entry);

#endif
