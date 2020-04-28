#include "map.h"
#include "interface.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

/*-----------------------Initiate--------------------------------*/
Map* newMap(int size, Ship *ship)
{  
  Map *m = (Map*)malloc(sizeof(Map));
  if(m==NULL)
  errorMessageMem("Map");
  
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

/*-----------------------Search-----------------------------------*/

char search(Map *m, Point *p)
{
  if (!inBound(m,p) )
    errorMessageOut("search", p);

  return m->map[p->y-1][p->x-1];
}

int inBound(Map *m, Point *p)
{
  int lim = m->mapSize;

  return p->x <= lim && p->x > 0 && p->y <= lim && p->y > 0 ? 1: 0;
}


/*-----------------------Print-----------------------------------*/


void printMap(Map *m,int u){ 
  
    for(int i=m->mapSize-1; i>=0; putchar('\n'), i--)
    for(int j=0; j<m->mapSize;j++ ){
    if(m->map[i][j]=='#')
    printf(ANSI_COLOR_BLUE "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else
    if(m->map[i][j]=='H')
    printf(ANSI_COLOR_YELLOW "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else{ 
    if(u==0)
    printf(ANSI_COLOR_GREEN"%c "ANSI_COLOR_RESET,m->map[i][j]);
    else
    printf(ANSI_COLOR_RED"%c "ANSI_COLOR_RESET,m->map[i][j]);
    }
    }
    
  putchar('\n');
}

void printInfo(Map *m)
{
  printf("Map Size = %d, Num of Points = %d\n", m->mapSize, m->nPoint);

  putchar('\n');
}






