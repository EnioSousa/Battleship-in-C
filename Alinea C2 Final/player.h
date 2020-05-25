#ifndef PLAYER
#define PLAYER
#include "map.h"

typedef struct
{
  char *name;
  Map *map;
} Player;

/*-----------------------Initiate--------------------------------*/
Player *initiatePlayer(char *, Map *);

#endif
