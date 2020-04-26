#ifndef PLAYER
#define PLAYER

#include "map.h"
#include "ship.h"

typedef struct 
{
  char *name;
  Map *map, *his;
  int *countPoints;
  int nhit;
 
 }Player;

/*-----------------------Initiate--------------------------------*/
Player *initiatePlayer(int);
/*-----------------------Print-----------------------------------*/
void printPlayer(Player* p);
void printShipEnemy (Ship*,Player* );
void printShootShip(int ,Ship *, Player* );
#endif


