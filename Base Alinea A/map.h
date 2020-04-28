#ifndef MAP_WORLD
#define MAP_WORLD

#include <stdio.h>
#include <stdlib.h>

#include "ship.h"
#include "error.h"
#include "point.h"


#define WATER '#' 
#define HIT 'H'

typedef struct 
{
  char **map;

  Ship *ship;
  
  int nPoint, mapSize;
  
}Map;


Map* newMap(int, Ship *);
char** newBiArray(int);
void initiateBiArray(char **, int, char);

char search(Map *, Point *);
int inBound(Map *, Point *);

#endif
