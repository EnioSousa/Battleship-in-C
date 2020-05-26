#include "player.h"
#include "errorMessage.h"
#include <stdlib.h>
#include <stdio.h>

/*-----------------------Initiate--------------------------------*/

Player *initiatePlayer(char *name, Map *map)
{
  Player *p = (Player *)malloc(sizeof(Player));
  if (p == NULL)
    errorMessageMem("player");

  p->map = map;
  p->name = name;
  return p;
}
