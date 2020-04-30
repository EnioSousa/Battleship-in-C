#include "interface.h"

void printAll(Map *m)
{
  printInfo(m);
  printMapShip(m);
  printMapHistory(m);
}

void printInfo(Map *m)
{
  printf("Map Size = %d, Num of Points = %d\n", m->mapSize, m->nPoint);

  putchar('\n');
}

void printMapShip(Map *m)
{
  printf("Your Ships placement\n");
  printf("0->empty, 1->piece not hitted, 2->piece hitted, 3->enemy miss shot\n");
  
  for( int i=m->mapSize-1; i>=0; putchar('\n'), i-- )
    for( int j=0; j<m->mapSize; j++ )
      printf("%c ", m->board[i][j].bit);

  putchar('\n');
}

void printMapHistory(Map *m)
{
  printf("Your History of shots\n");
  printf("0->no shot, 1->failed shot, 2->hit\n");
  
  for( int i=m->mapSize-1; i>=0; putchar('\n'), i-- )
    for( int j=0; j<m->mapSize; j++ )
      printf("%c ", m->board[i][j].shot);

  putchar('\n');
}  

void printPoint(Point *p) { printf("(%d,%d)\n", p->x, p->y); }


  
