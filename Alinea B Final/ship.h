#ifndef SHIP
#define SHIP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
typedef struct Ship
{
  char name[20];
  
  int size, num, left, id, active;
  
  Point *vec;
  
}Ship;

/*-----------------------Initiate--------------------------*/

/* Aloca espaço e retorna o apontador para o array de tipo Ship*/
Ship* initiateShip(int nShips);

/* Define a forma de cada tipo de barco usando um vector de deslocação.
   Caso haja a necessidade de  mudar a forma do barco basta adicionar os pontos que o barco
   tem que passar. Atenção que por definição os barcos apontam todos para East. 
   Exemplo: Um barco com forma T e tamanho 5 seria definido da seguinte forma:
   vec[i].p->x = i e vec[i].p->y = 0, para i={0..2}
   vec[3].p->x = 0 e vec[3].p->y = -1
   vec[4].p->x = 0 e vec[4].p->y = 1*/
void defineForm(Ship *ship);


/*-------------------------Check--------------------------*/
/* Retorna 1 caso falte por algum navio, caso contrario 0. O argumento ship
   é suposto ser o array ship definido em initiateShip/1*/
int someShipLeft(Ship *ship);

/* Retorna 1 caso o tipo de navio dado como argumento, ship, esteje disponivel
   para colocação, i.e ainda falte por algum navio desse tipo*/
int shipAvaliable(Ship *ship);

/* Retorna o indice do proximo navio a colocar. Caso não exista nenhum
   returna -1*/
int nextShip(Ship *ship);

/* Retorna 1 caso exista algum tipo de navio activo, caso contrario 0*/
int someActiveShip(Ship *arrShip);

/*-------------------------Free---------------------------*/

/* Liberta a memoria alocada dinamicamente pela função initiateShip/1*/
void freeShip(Ship *ship);

#endif
