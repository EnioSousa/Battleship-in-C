#include "point.h"
#include "errorMessage.h"
#include <stdlib.h>
#include <stdio.h>


/*-----------------------Initiate--------------------------*/

Point *newPoint()
{
  Point *p = (Point*)malloc(sizeof(Point));

  if ( p==NULL ){
      errorMessageMem("Point");
     }
  
  p->x = 0;
  p->y = 0;

  return p;
}

/*-----------------------Print---------------------------------*/

void printPoint(Point *p)
{
  printf("(%d,%d)\n", p->x, p->y);

}



	
