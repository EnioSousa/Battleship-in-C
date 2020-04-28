#ifndef MAP_WORLD
#define MAP_WORLD

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "ship.h"
#include "error.h"

#define WATER '#' 
#define HIT 'H'

#define LIM 4 // Dont' change it to a value lower than 4

typedef struct
{
  Point *pos;
  char id;
  
}Node;


typedef struct Map
{
  int mapSize;
  
  Point *tl; // top left
  Point *br; // bottom rigth
  
  Node *vec; // array of nodes
  int nP; // number of nodes/Points

  Ship *ship;
  
  struct Map *father; // pai 
  
  struct Map *nw; // north west son
  struct Map *ne; // north east son
  struct Map *sw; // south west son
  struct Map *se; // south east son

} Map;

/*----------------------------New/free struct--------------------------*/
Map *newMap(int mapSize, Ship *ship);
Map *newSon(Map *father, Point *a, Point *b);

void freeMap(Map *root);
void freeMapLevel(Map *level);

void newNode(Map *level, Point *p, char ch);
void addNode(Map *level, Node *node);

void freeVectorNode(Node *vecNode, int size);

/*----------------------------Division----------------------------------*/
void newPartition(Map *level);
int possibleToDivide(Map *level);
void divideInFour(Map *level);
void copyForward(Map *father);
int whichQuadrant(Map *level, Point *p);


#endif
