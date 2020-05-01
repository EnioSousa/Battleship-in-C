#include "search.h"
#include "errorMessage.h"
#include "ship.h"
#include <stdio.h>

/*-------------------Search----------------------------------------*/
Ship *search(Map *map, Point *p)
{
  if ( !inBound(map, p) )
    return NULL;

  return map->board[p->y-1][p->x-1].ship;
}

/*-------------------Check----------------------------------------*/
int inBound(Map *map, Point *p)
{
  int lim = map->mapSize;

  return p->x <= lim && p->x > 0 && p->y <= lim && p->y > 0 ? 1: 0;
}
