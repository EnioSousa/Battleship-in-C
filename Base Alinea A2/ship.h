#ifndef SHIP
#define SHIP

#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "errorMessage.h"

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

/*-------------------------Free---------------------------*/
void freeShip(Ship *ship);

/*-------------------------Check--------------------------*/
int someShipLeft(Ship *ship);
int shipAvaliable(Ship *ship);
int nextShip(Ship *ship);
int someActiveShip(Ship *ship);

/*-------------------------Print--------------------------*/
void printAllShip(Ship *);
void printShip(Ship *);
void printShipForm(Ship *);
void printAllShipInfo(Ship *ship);
void printShipInfo(Ship *);

#endif
