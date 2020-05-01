#ifndef PLAYER
#define PLAYER

#include "map.h"
#include "ship.h"

typedef struct
{
  char *name;
  Map *map;
} Player;

/*-----------------------Initiate--------------------------------*/
Player *initiatePlayer(int, int);
/*-----------------------Print-----------------------------------*/
void printPlayer(Player *p);

#endif
