#include "QuadTree.h"

void printNode(Node no)
{
  printf("Id=%d (%d,%d)\n", no.id, no.pos.x, no.pos.y);
}

void printLevel(Quad *level)
{
  printf("no=%d\n", level->nP);
  
  if ( level->nw==NULL )
    for( int i=0; i<level->nP; i++ )
      printNode(level->vec[i]);

  else
    printf("No nodes in this level\n");
}

void printAllLevel(Quad *level, int n)
{
  if ( level==NULL )
    return;
  
  printf("Level=%d\n", n);

  printLevel(level);

  printAllLevel(level->nw, n+1);
  printAllLevel(level->ne, n+1);
  printAllLevel(level->sw, n+1);
  printAllLevel(level->se, n+1);
}


void initiateBiArr(char map[][mapSize+1])
{
  for( int i=0; i<=mapSize; i++ )
    for( int j=0; j<=mapSize; map[i][j]='#', j++ );
}

void transToMap(char map[][mapSize+1], Quad *level)
{
  if ( level==NULL || level->nw!=NULL )
    return;

  for( int i=0; i<level->nP; i++ )
    {
      Node temp = level->vec[i];

      map[temp.pos.y][temp.pos.x] = temp.id + '0';
    }
}

void printBiArray(char map[][mapSize+1])
{
  for( int i=mapSize; i>0; putchar('\n'), i-- )
    for( int j=1; j<=mapSize; printf("%c ", map[i][j]), j++);
}

void printMap(Quad *root)
{
  char map[mapSize+1][mapSize+1];
  initiateBiArr(map);

  Queue *q = newQueue();
  enqueue(q, root);

  while ( !isEmpty(q) )
    { 
      Quad *temp = dequeue(q);

      transToMap(map, temp);

      if ( temp->nw!=NULL )
	{
	  enqueue(q, temp->nw);
	  enqueue(q, temp->ne);
	  enqueue(q, temp->sw);
	  enqueue(q, temp->se);      
	}
    }

  printBiArray(map);
}
