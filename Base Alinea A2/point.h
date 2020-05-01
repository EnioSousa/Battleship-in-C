#ifndef POINT
#define POINT

#include "errorMessage.h"

typedef struct Point
{ 
  int x; 
  int y;
  
} Point;

/*-----------------------Initiate--------------------------------*/
Point* newPoint();

/*-----------------------Print-----------------------------------*/
void printPoint(Point* p);

#endif
