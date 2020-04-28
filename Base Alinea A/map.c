#include "map.h"

Map* newMap(int size, Ship *ship)
{  
  Map *m = (Map*)malloc(sizeof(Map));

  m->nPoint = 0;
  m->mapSize = size;
  
  m->map = newBiArray(size);

  initiateBiArray(m->map, size, WATER);

  m->ship = ship;
  
  return m;
}

char** newBiArray(int size)
{
  char **map = (char**)malloc(size*sizeof(char*));

  if ( map == NULL )
    errorMessageMem("newMap");
  
  for( int i=0; i<size; i++ )
    {
      map[i] = (char*)malloc(size*sizeof(char));

      if ( map[i] == NULL )
	errorMessageMem("newMap");
    }

  return map;
}

void initiateBiArray(char **map, int size, char ch)
{
  for( int i=0; i<size; i++ )
    for( int j=0; j<size; j++)
      map[i][j]=ch;
}

char search(Map *m, Point *p)
{
  if ( !inBound(m, p) )
    errorMessageOut("search", p);

  return m->map[p->y-1][p->x-1];
}

int inBound(Map *m, Point *p)
{
  int lim = m->mapSize;

  return p->x <= lim && p->x > 0 && p->y <= lim && p->y > 0 ? 1: 0;
}

