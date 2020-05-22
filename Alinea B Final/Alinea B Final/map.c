#include "map.h"

/*----------------------------New/free struct--------------------------*/
Map *newMap(int size, Ship *ship)
{
  Map *root = (Map*)calloc(1, sizeof(Map));

  if ( root==NULL )
    errorMessageMem("newMap");

  root->mapSize = size;
  root->ship = ship;
  
  root->tl = newPoint(1, root->mapSize);
  root->br = newPoint(root->mapSize, 1);

  root->vec = NULL;
  root->nP = 0;
  
  root->nw=NULL;
  root->ne=NULL;
  root->sw=NULL;
  root->se=NULL;

  root->father = NULL;

  return root;
}

Map *newSon(Map *father, Point *tl, Point *br)
{
  int size = (br->x-tl->x+1) * (tl->y-br->y+1);
  Map *son = newMap(size, father->ship);

  free(son->tl); son->tl = newPoint(tl->x, tl->y);
  free(son->br); son->br = newPoint(br->x, br->y);

  son->father = father;

  return son;
}

void newNode(Map *level, Ship *ship, Point *p, char bit, char shoot)
{
  int index = level->nP;
  level->nP++;
  
  level->vec = (Node *)realloc(level->vec, level->nP*sizeof(Node));

   if ( level->vec==NULL )
    errorMessageMem("newNode");

  level->vec[index].pos = newPoint(p->x, p->y);

  level->vec[index].cell = newCell(ship, bit, shoot);

  incUp(level->father, 1);
  
  if ( level->nP>LIM && ( level->father==NULL || level->father->vec==NULL ) )
    newPartition(level);  
}

void incUp(Map *level, int n)
{
  if ( level==NULL )
    return;

  level->nP += n;

  incUp(level->father, n);
}

void addNode(Map *level, Node *no)
{
  if ( no==NULL || no->cell==NULL )
    errorMessagePointer("addNode");
  
  newNode(level, no->cell->ship, no->pos, no->cell->bit, no->cell->shoot);

  incUp(level->father, -1);
}

Cell *newCell(Ship *ship, char bit, char shoot)
{
  Cell *temp = (Cell *)calloc(1, sizeof(Cell));

  if ( temp==NULL )
    errorMessageMem("newCell");

  temp->ship = ship;
  temp->bit = bit;
  temp->shoot = shoot;

  return temp;
}

/*----------------------------Free struct--------------------------*/

void freeMap(Map *root)
{
  freeShip(root->ship);
  freeMapLevel(root);
}

void freeMapLevel(Map *level)
{
  if ( level==NULL )
    return;
  
  free(level->tl);
  free(level->br);
  
  freeVectorNode(level->vec, level->nP);

  freeMapLevel(level->nw);
  freeMapLevel(level->ne);
  freeMapLevel(level->sw);
  freeMapLevel(level->se);

  level=NULL;
}

void freeVectorNode(Node *vecNode, int size)
{
  if ( vecNode==NULL )
    return;
  
  for( int i=0; i<size; i++ )
    {
      if ( &vecNode[i]==NULL )
        return;

      else
	{
	  free(vecNode[i].cell);
	  free(vecNode[i].pos);
	}
    }

  free(vecNode);
  vecNode = NULL;
}

/*----------------------------Division----------------------------------*/

void newPartition(Map *level)
{
  if ( possibleToDivide(level) )
    {
      divideInFour(level);
      
      copyForward(level);

      freeVectorNode(level->vec, level->nP);
      level->vec=NULL;
    }
}

int possibleToDivide(Map *level)
{
  int t1 = level->br->x - level->tl->x + 1;
  int t2 = level->tl->y - level->br->y + 1;

  return t1*t2>=LIM ? 1: 0;
}

void divideInFour(Map *level)
{
  int t1,t2;

  t1 = level->tl->x + (level->br->x - level->tl->x) / 2;
  t2 = level->br->y + (level->tl->y - level->br->y) / 2;

  Point p1, p2;

  p1.x = t1; p1.y = t2+1;  
  level->nw = newSon(level, level->tl, &p1);

  p1.x = t1+1; p1.y = level->tl->y;
  p2.x = level->br->x; p2.y = t2+1;
  level->ne = newSon(level, &p1, &p2);

  p1.x = level->tl->x; p1.y = t2;
  p2.x = t1; p2.y = level->br->y;
  level->sw = newSon(level, &p1, &p2);

  p1.x = t1+1; p1.y=t2;
  level->se = newSon(level, &p1, level->br);
}

void copyForward(Map *father)
{  
  Node *temp;
  
  for(int i=0; i<father->nP; i++ )
    {
      temp = &father->vec[i];

      if ( temp==NULL || temp->pos==NULL )
	errorMessagePointer("copyForward");
      
      switch( whichQuadrant(father, temp->pos) )
	{
	case 1:
	  addNode(father->sw, temp);
	  break;
	  
	case 2:
	  addNode(father->se, temp);
	  break;
	  
	case 3:
	  addNode(father->nw, temp);
	  break;
	  
	case 4:
	  addNode(father->ne, temp);
	  break;

	default:
	  fprintf(stderr, "error on copyAll\n");
	  exit(EXIT_FAILURE);
	}
    }
}

int whichQuadrant(Map *level, Point *p)
{ 
  int t1,t2;

  if ( level==NULL || level->tl==NULL || level->br==NULL )
    errorMessagePointer("whichQuadrant");
  
  t1 = level->tl->x + (level->br->x - level->tl->x) / 2;
  t2 = level->br->y + (level->tl->y - level->br->y) / 2;

  if ( level->nw==NULL )
    return 0;
  
  else if ( p->x<=t1 && p->y<=t2 )
    return 1;

  else if ( p->x<=t1 )
    return 3;

  else if ( p->y<=t2 )
    return 2;

  else
    return 4;
}
