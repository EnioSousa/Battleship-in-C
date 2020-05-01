#include "map.h"

Map *newMap(int size)
{
  Map *map = (Map *)calloc(1, sizeof(Map));

  if ( map==NULL )
    errorMessageMem("newMap");

  map->mapSize = size;

  map->board = newBiCell(size);

  map->ship = initiateShip(size);

  return map;
}

Cell *newCell(int size)
{
  Cell *arr = (Cell *)calloc(size, sizeof(Cell));

  if ( arr==NULL )
    errorMessageMem("newCell");

  for( int i=0; i<size; i++ )
    {
      arr[i].bit = '0';
      arr[i].shot = '0';
    }
  
  return arr;
}

Cell **newBiCell(int size)
{
  Cell **biArr = (Cell **)calloc(size, sizeof(Cell *));

  if ( biArr==NULL )
    errorMessageMem("newBiCell");

  for( int i=0; i<size; i++ )
    biArr[i] = newCell(size);

  return biArr;
}

int lost(Map *map)
{
  return someActiveShip(map->ship) ? 0: 1;
}
