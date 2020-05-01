#ifndef MAP_WORLD
#define MAP_WORLD

#include <stdio.h>
#include <stdlib.h>

#include "ship.h"
#include "errorMessage.h"
#include "point.h"

typedef struct Cell
{
  Ship *ship;

  char shot;

  char bit;
  
}Cell;

typedef struct 
{
  Cell **board;

  Ship *ship;
  
  int nPoint, mapSize;
  
}Map;

Map *newMap(int size);
Cell *newCell(int size);
Cell **newBiCell(int size);

int lost(Map *map);

#endif
