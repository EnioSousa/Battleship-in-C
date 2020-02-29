#include "QuadTree.h"
#include "ship.c"
#include <stdio.h>
#include <stdlib.h>



Point* newPoint(int a,int b){
  Point* var = (Point*) malloc(sizeof(Point));
	
  if (var == NULL){
    fprintf(stderr,"Falta de memória\n");
    exit(EXIT_FAILURE);
  }
	
  var->x=a;
  var->y=b;
	
  return var;
}
	
	
void newNode(Quad *tree, Point a, char b){

  tree->nP++;
  
  tree->n = (Node*)realloc(tree->n, tree->nP*sizeof(Node));
	
  if (tree->n[tree->nP-1]==NULL){
    fprintf(stderr,"Falta de memória\n");
    exit(EXIT_FAILURE);
  }
	
  tree->n[tree->nP].pos=a;
  var->c=b;
	
  return var;
}
	

Quad* newQuad(Point a, Point b) { 
        
  Quad* var = (Quad*) malloc(sizeof(Quad));
  if (var == NULL){
    fprintf(stderr,"Falta de memória\n");
    exit(EXIT_FAILURE);
  }
        
        
  var->n = NULL;

  var->nP=0;
        
  var->topLeftTree  = NULL; 
  var->topRightTree = NULL; 
  var->botLeftTree  = NULL; 
  var->botRightTree = NULL; 
        
  var->topLeft = a; 
  var->botRight = b; 

  return var;  
}



bool checker(Point p, Quad* ab  ) 
{ 
  if(p.x >= ab->topLeft.x && 
     p.x <= ab->botRight.x && 
     p.y >= ab->topLeft.y && 
     p.y <= ab->botRight.y)
    return true;
} 

int whereToMap(Quad *tree, Point p)
{
  int x = (tree->botRight.x - tree->topleft.x)/2;
  int y = (tree->botRight.y - tree->topLeft.y)/2;


  if ( p.x<x && p.y<y )
    return 1;

  else if ( p.x<x && p.y>y )
    return 3;

  else if ( p.x>x && p.y<y )
    return 2;

  else
    return 4;
}


int whereToGo(Quad *tree, Point p)
{
  if ( tree->nP<Lim )
    return 0;

  else return whereToMap(tree, p);
}


void divide(Quad *tree)
{
  int x = (tree->botRight.x - tree->topleft.x)/2;
  int y = (tree->botRight.y - tree->topLeft.y)/2;

  Point *temp = newPoint(x, y);
  
  tree->topLeftTree = newQuad(tree->topLeft, *temp);
  tree->botRigthTree = newQuad(*temp, tree->botLeft);

  free(temp);
  
  Point *p1 = newPoint(tree->topLeft.x, y);
  Point *p2 = newpoint(x, tree->botRigth.y);

  tree->botLeftTree = newQuad(*p1, *p2);

  p1->x = x
  p1->y = tree->topLeft.y;

  p2->x = tree->botRigth.x;
  p2->y = y;

  tree->topRigthTree = newQuad(*p1, *p2);

  free(p1);
  free(p2);

  tree->topLeftTree->pai = tree;
  tree->botRigthtree->pai = tree;
  tree->topRigthTree->pai = tree;
  tree->botLeftTree->pai = tree;
    
}


void copy(Quad *son, Node *n) { newNode(son, n->pos, n->c); son->nP++; }

void copyAll(Quad *pai)
{
  for( int i=0; i<Lim; i++ )
    {
      Node *temp = &pai->n->[i]);
      switch(whereToMap(pai, temp))
	{
	case 1:
	  copy(pai->topLeftTree, temp);
	  break;
	
	case 2:
	  copy(pai->topRigthTree, temp);
	  break;

	case 3:
	  copy(pai->botLeftTree, temp);
	  break;

	  
	case 4:
	  copy(pai->botRigthTree, temp);
	  break;	  
	}
    }
}

void newPartition(Quad *tree)
{
  divide(tree);

  copyAll(tree);

  free(tree->n);
}

Quad* searchDepth(Quad *tree, Point p)
{
  if ( tree->np<Lim )
    return tree;

  switch(whereToMap(pai, p))
    {
    case 1:
      return searchDepth(pai->topLeftTree, p);
	
    case 2:
      return searchDepth(pai->topRigthTree, p);

    case 3:
      return searchDepth(pai->botLeftTree, p);

    case 4:
      return searchDepth(pai->botRigthTree, p);
    }
  
 
}

int equalPoint(point p1, Point p2) { return p1.x==p2.x && p1.y==p1.y ? 1: 0; }

int equal(Node *no, Point p) { return equalPoint(*no->pos, p); }


Node *searchPoint(Quad *level, Point p)
{
  for( int i=0; i<level->nP; i++ )
    if ( equal(&level->n[i], p) )
      return &level->n[i];

  return NULL;
}

Node *searchBlind(Quad *root, Point p)
{
  return searchPoint(searchDepth(root, p), p);
}

void incUp(Quad* tree)
{
  if ( tree==NULL )
    return;

  else
    {
      tree->nP++;
      incUp(tree->pai);
    }
}

void insertPoint(Quad *root, Point p)
{
  Quad *temp = searchDepth(root, p);

  if ( searchPoint(temp, p)!=NULL )
    {
      
    }

  else
    {
      newNode(temp, p, ch);
      incUp(temp);

      if ( temp->nP>=Lim )
	newPartition(temp);
    }
}
void movePos(Point* p, char dir)
{
  switch(dir)
    {
    case 'n':
      p->x--;
      break;

    case 's':
      p->x++;
      break;

    case 'w':
      p->y--;
      break;

    default:
      p->y++;
      break;
    }
}

int confAvaliable(Quad *root, Ship* ship, int id, Point p, char dir)
{
  for( int i=0; i<ship[id].Size; movePos(&p, dir), i++ )
    if ( searchBlind(root, p)!=NULL )
      return 0;
}

int shipAvaliable(Ship* ship, int id)
{
  return ship[id].Left!=0 ? 1: 0;
}

// precisa de ser modificada
void insertAll(Quad *root, Ship* ship, int id, Point p, char dir)
{
  for( int i=0; i<ship[id].Size; movePos(&p, dir), i++ )
    insertPoint(root, p);
}


void updateMap(Quad *root, Ship* ship, int id, Point p, char dir)
{
  if ( !confAvaliable(root, ship, id, p, dir) )
    return;

  if ( !shipAvaliable(ship, id) )
    return;

  insertAll((root, ship, id, p, dir);
}
