#include "interface.h"

void printAll(Map *m)
{
  printInfo(m);
  printMap(m);
}

void printInfo(Map *m)
{
  printf("Map Size = %d, Num of Points = %d\n", m->mapSize, m->nPoint);

  putchar('\n');
}

void printMap(Map *m)
{
  for( int i=m->mapSize-1; i>=0; putchar('\n'), i-- )
    for( int j=0; j<m->mapSize; printf("%c ", m->map[i][j]), j++ );

  putchar('\n');
}

void printPoint(Point *p)
{
  printf("(%d,%d)\n", p->x, p->y);
}


