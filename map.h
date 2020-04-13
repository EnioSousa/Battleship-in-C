#ifndef MAP_WORLD
#define MAP_WORLD
#include <stdio.h>
#include <stdlib.h>
#define WATER '#' 

typedef struct Point 
{ 
  int x; 
  int y;
} Point;

typedef struct 
{
  char **map;
  int nPoint, mapSize;
  
}Map;


Map* newMap(int);
char** newBiArray(int);
void initiateBiArray(char **, int, char);
void errorMessageMem(char*);
int search(Map *, Point *);
void deleteAll(Map *);
void deletePoint(Map *, Point *);
void printPoint(Point *);
Point *newPoint();
#endif
