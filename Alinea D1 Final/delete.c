#include "delete.h"

/*----------------------------delete----------------------------------*/
void deletePoint(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("deletePoint");

  if ( outOfBounds(root, p) )
    return;
  
  deletePointOnDepth(searchDepth(root, p), p);
}

void deletePointOnDepth(Map *level, Point *p)
{
  int i;

  if ( level==NULL || p==NULL )
    errorMessagePointer("deletePointOnDepth\n");

  if ( level->nw!=NULL )
    {
      fprintf(stderr, "WrongLevel in deletePointOnDepth\n");
      exit(EXIT_FAILURE);
    }
  
  for( i=0; i<level->nP && !equalPoint(p, level->vec[i].pos); i++ );

  if ( i<level->nP )
    {
      for( ; i < level->nP - 1; i++ )
	swap(&level->vec[i], &level->vec[i+1]);

      level->nP--;
      
      compact(level);

      downUp(level->father, 1);
      
      if ( possibleToFree(level) )
	freeSons(level->father);
    }
}

void swap(Node *a, Node *b)
{
  Cell *cell = a->cell;
  Point *p =  a->pos;

  a->cell = b->cell;
  a->pos = b->pos;

  b->cell = cell;
  b->pos = p;
}

void compact(Map *level)
{
  level->vec = (Node*)realloc(level->vec, level->nP*sizeof(Node));
}

void downUp(Map *level, int n)
{
  if ( level==NULL )
    return;

  level->nP -= n;

  downUp(level->father, n);
}

int possibleToFree(Map *level)
{
  return level->father!=NULL && level->father->nP<=LIM ? 1: 0;
}

void freeSons(Map *father)
{
  father->nP -= father->nw->nP + father->ne->nP + father->sw->nP + father->se->nP;
  
  copyBack(father, father->nw);
  copyBack(father, father->ne);
  copyBack(father, father->sw);
  copyBack(father, father->se);

  freeMapLevel(father->nw); 
  freeMapLevel(father->ne); 
  freeMapLevel(father->sw); 
  freeMapLevel(father->se);
  
  father->nw = NULL;
  father->ne = NULL;
  father->sw = NULL;
  father->se = NULL;
}

void copyBack(Map *father, Map *son)
{
  for( int i=0; i<son->nP; addNode(father, &son->vec[i]), i++ );
}
