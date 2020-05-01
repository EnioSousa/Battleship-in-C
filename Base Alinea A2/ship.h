#ifndef SHIP
#define SHIP

#include "point.h"


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
Ship* initiateShip(int nShips);
void defineForm(Ship *ship);

/*-------------------------Check--------------------------*/
int someShipLeft(Ship *ship);
int shipAvaliable(Ship *ship);
int nextShip(Ship *ship);
int someActiveShip(Ship *ship);
void printAllShipInfo(Ship *ship);
void informationShipRemaining(Ship* s);

/*-------------------------Print--------------------------*/
void printAllShip(Ship *);
void printShip(Ship *);
void printShipForm(Ship *);
void printShipInfo(Ship *);

/*-------------------------Free---------------------------*/
void freeShip(Ship *ship);

#endif
