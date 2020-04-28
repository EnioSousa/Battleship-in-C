#ifndef SHIP
#define SHIP

#include "point.h"
#include "error.h"

/* Numero de navios diferentes */
#define NumDifShip 5

/* name -> nome do navio
   id -> identificação numerica do navio
   size -> tamanho que o navio ocupa
   num -> numero de navios
   left -> numero de navios que falta ser posto
   active -> numero de navios ativos
   vec -> vetor de deslocação*/
typedef struct ship
{
  char name[20];
  
  int size, num, left, id, active;
  
  Point *vec;
  
}Ship;

/*-----------------------Initiate--------------------------*/
Ship* initiateShip();
void defineForm(Ship *);

/*-------------------------Print--------------------------*/
void printAllShip(Ship *);
void printShip(Ship *);
void printShipForm(Ship *);
void printShipInfo(Ship *);

#endif
