#include "object.h"

Object *newObject(Map *map, int level, int quadrant)
{
  Object *obj = (Object *)malloc(sizeof(Object));

  if ( obj==NULL )
    errorMessageMem("newObject");

  obj->map = map;

  obj->quadrant = quadrant;

  obj->level = level;

  return obj;
}

void printObject(Object *obj)
{
  printf("Level %d, Quadrant %s", obj->level,
	 obj->quadrant==1 ? "nw\n": obj->quadrant==2 ? "ne\n":
	 obj->quadrant==3 ? "sw\n": "se\n");

  printf("level Limits\n");
  printPoint(obj->map->tl);
  printPoint(obj->map->br);

  printf("Number of Points = %d\n", obj->map->nP);

  if ( obj->map->nw==NULL )
    {
      for( int i=0; i<obj->map->nP; i++ )
	{
	  printPoint(obj->map->vec[i].pos);
	  printf("ID = %c\n", obj->map->vec[i].id);
	}
    }
  
  putchar('\n');
}
