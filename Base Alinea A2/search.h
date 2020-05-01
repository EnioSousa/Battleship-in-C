#ifndef SEARCH
#define SEARCH

#include "map.h"
#include "point.h"

/*-------------------Search----------------------------------------*/
Ship *search(Map *map, Point *p);
/*-------------------Check----------------------------------------*/
int inBound(Map *map, Point *p);

#endif

