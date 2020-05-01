#ifndef MAP_WORLD
#define MAP_WORLD

#include "ship.h"

typedef struct Cell
{
  Ship *ship;

  char shot;

  char bit;

} Cell;

typedef struct
{
  Cell **board;

  Ship *ship;

  int nPoint, mapSize;

} Map;

/*-----------------------Initiate--------------------------*/

Map *newMap(int size);
Cell *newCell(int size);
Cell **newBiCell(int size);
/*----------------------Check------------------------------*/
int lost(Map *map);
/*----------------------Free---------------------------------*/
void freeMap(Map *map);

#endif
