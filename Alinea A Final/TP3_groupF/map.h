#ifndef MAP
#define MAP

#define WATER '#' 
#define HIT 'H'

#include "ship.h"
#include "point.h"

typedef struct 
{
  char **map;
  Ship *ship;
  int nPoint, mapSize;
  
}Map;

/*-----------------------Initiate--------------------------------*/
Map* newMap(int, Ship *);
char** newBiArray(int);
void initiateBiArray(char **, int, char);
/*-----------------------Search-----------------------------------*/
char search(Map *, Point *);
int inBound(Map *, Point *);
/*-----------------------Print-----------------------------------*/
void printMap(Map *m,int i);
void printInfo(Map *m);
#endif
