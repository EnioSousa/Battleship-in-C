#ifndef SHIP
#define SHIP
#include <string.h>
#include "QuadTree.h"
/* Numero de navios diferentes */
#define NumDifShip 5

/* Name -> nome do navio
   Size -> tamanho que o navio ocupa
   Num -> numero de navios a serem colocados
   Left -> numero de navios que falta ser posto
   vec -> vetor de deslocação*/

typedef struct ship
{
  char name[20];
  int size, num, left, id;
  Point *vec;
  
}Ship;


Ship* initiateShip();
void defineForm(Ship *ship);
void printShip(Ship* arr);


#endif
