#ifndef POINT
#define POINT

#include <stdio.h>
#include <stdlib.h>
#include "errorMessage.h"

typedef struct Point
{
  int x, y;
  
}Point;

Point *newPoint(int x, int y);
int equalPoint(Point *p1, Point *p2);
void printPoint(Point *p);

#endif
