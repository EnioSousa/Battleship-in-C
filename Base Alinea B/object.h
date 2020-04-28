#ifndef OBJECT
#define OBJECT

#include "map.h"
#include "error.h"

typedef struct Object
{
  Map *map;

  int quadrant, level;

  struct Object *pai;
  
}Object;

Object *newObject(Map *map, int level, int quadrant);
void printObject(Object *obj);

#endif
