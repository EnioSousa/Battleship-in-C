#ifndef POINT
#define POINT


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
