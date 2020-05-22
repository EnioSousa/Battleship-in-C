#include "search.h"

char *searchShoot(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("searchShip");
  
  if ( outOfBounds(root, p) )
    return NULL;

  Cell *temp = searchCell(root, p);

  if ( temp==NULL )
    return NULL;

  else
    return &temp->shoot;
}

char *searchBit(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("searchShip");
  
  if ( outOfBounds(root, p) )
    return NULL;

  Cell *temp = searchCell(root, p);

  if ( temp==NULL )
    return NULL;

  else
    return &temp->bit;
}

Ship *searchShip(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("searchShip");

  if ( outOfBounds(root, p) )
    return NULL;

  Cell *temp = searchCell(root, p);

  if ( temp==NULL )
    return NULL;

  else
    return temp->ship;
}

Cell *searchCell(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("searchCell");

  if ( outOfBounds(root, p) )
    return NULL;

  Node *temp = searchNode(root, p);

  if ( temp==NULL )
    return NULL;

  else
    return temp->cell;  
}

Node *searchNode(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("searchNode");
  
  if ( outOfBounds(root, p) )
    return NULL;

  return searchLevel(searchDepth(root, p), p);
}  

Map *searchDepth(Map *level, Point *p)
{
  if ( level==NULL || p==NULL )
    errorMessagePointer("searchDepth");

  if ( outOfBounds(level, p) )
    return NULL;
  
  switch( whichQuadrant(level, p) )
    {
    case 0:
      return level;

    case 1:
      return searchDepth(level->sw, p);

    case 2:
      return searchDepth(level->se, p);

    case 3:
      return searchDepth(level->nw, p);

    default:
      return searchDepth(level->ne, p);
    }  
}

Node *searchLevel(Map *level, Point *p)
{
  if ( p==NULL )
    errorMessagePointer("searchLevel");
  
  for( int i=0; i<level->nP; i++ )
    if ( equalPoint(level->vec[i].pos, p) )
      return &level->vec[i];
  
  return NULL;
}

int outOfBounds(Map *map, Point *p)
{
  if ( map==NULL || map->tl==NULL || map->br==NULL || p==NULL )
    errorMessagePointer("outOfBounds");

  return p->x>=map->tl->x && p->x<=map->br->x &&
    p->y>=map->br->y && p->y<=map->tl->y ? 0: 1;
}
