#include "interface.h"

void printAll(Map *m)
{
  printInfo(m);
  printMap(m);
}

void printInfo(Map *m)
{
  printf("Map Size = %d, Num of Points = %d", m->mapSize, m->nP);

  putchar('\n');
}

