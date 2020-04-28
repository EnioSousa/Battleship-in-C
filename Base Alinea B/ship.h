#ifndef SHIP
#define SHIP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  
  int size, num, left, active;

  char id;
  
  Point *vec;
  
}Ship;

/*-----------------------Initiate--------------------------*/
Ship* initiateShip();
void defineForm(Ship *ship);

void freeShip(Ship *ship);

/*-------------------------Print--------------------------*/
void printAllShip(Ship *ship);
void printShip(Ship *ship);
void printShipForm(Ship *ship);
void printShipInfo(Ship *ship);

#endif
