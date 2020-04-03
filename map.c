#include "map.h"
#include "insert.h"

Map* newMap(int size)
{  
  Map *m = (Map*)malloc(sizeof(Map));

  m->nPoint = 0;
  m->mapSize = size;
  
  m->map = newBiArray(size);

  initiateBiArray(m->map,size, WATER);
  
  return m;
}

char** newBiArray(int size)
{
  char **map = (char**)malloc(size*sizeof(char*));

  if( map == NULL )
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
    for( int j=0; j<size; map[i][j]=ch,j++);
}

void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s\n", str);
  exit(EXIT_FAILURE);
}


int search(Map *m,Point *p)
{
  if(insideOfMap(m,p) && m->map[p->y-1][p->x-1] == 'H')
  return 0;
  else
  return insideOfMap(m,p) && m->map[p->y-1][p->x-1] == WATER ? 0: 1;
}

void deleteAll(Map *m)
{
  for(int i=0;i<m->mapSize; i++)
    for(int j=0;j<m->mapSize; m->map[i][j]=WATER, j++ );

  m->nPoint = 0;
}

void deletePoint(Map *m, Point *p)
{
  if ( !insideOfMap(m,p) )
    return;

  if ( m->map[p->y-1][p->x-1] != WATER )
    m->nPoint--;
  
  m->map[p->y-1][p->x-1] = WATER;
}

Point *newPoint()
{
  Point *p = (Point*)malloc(sizeof(Point));

  if ( p==NULL )
     {
      errorMessageMem("Point");
     }

  p->x = 0;
  p->y = 0;

  return p;
}

