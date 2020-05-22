#include "point.h"

Point *newPoint(int x, int y)
{
  Point *p = (Point *)calloc(1, sizeof(Point));

  if ( p==NULL )
    errorMessageMem("newPoint");

  p->x = x;
  p->y = y;

  return p;
}

int equalPoint(Point *p1, Point *p2)
{
  if ( p1==NULL || p2==NULL )
    errorMessagePointer("equalPoint");
  
  return p1->x==p2->x && p1->y==p2->y ? 1: 0;
}

void printPoint(Point *p)
{
  if ( p==NULL )
    errorMessagePointer("printPoint");
  
  printf("(%3d,%3d)\n", p->x, p->y);
}

