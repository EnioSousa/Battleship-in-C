#ifndef SEARCH
#define SEARCH

#include "map.h"
#include "ship.h"
#include "point.h"
#include "errorMessage.h"


Ship *search(Map *map, Point *p);
int inBound(Map *map, Point *p);

#endif
