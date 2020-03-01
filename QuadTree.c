#include "QuadTree.h"
#include "simpleQueue.c"

//A0
Point *newPoint(int x, int y);
//A1
void newNode(Quad *tree, Point a, int id);
//A2
void addNode(Quad *level, Node *no);
//A3
Quad *newQuadZero(Point a, Point b);
//
Quad *initiateTree();
//A4
void newPartition(Quad *tree);
//
int possibleToDivide(Quad *tree);
//A5
void divideInFour(Quad *tree);
//A6
void copyAll(Quad *father);
//A7
int whereToPut(Quad level, Point p);

//A0
Point *newPoint(int x, int y)
{
  Point *p = (Point*)malloc(sizeof(Point));

  if ( p==NULL )
    {
      fprintf(stderr,"Falta de memória em newPoint\n");
      exit(EXIT_FAILURE);
    }

  p->x = x;
  p->y = y;

  return p;
}

//A1
void newNode(Quad *tree, Point a, int id)
{
  tree->nP++;

  tree->vec = (Node*)realloc(tree->vec, tree->nP*sizeof(Node));

  if ( &tree->vec[tree->nP-1]==NULL )
    {
      fprintf(stderr,"Falta de memória em newNode\n");
      exit(EXIT_FAILURE);
    }

  tree->vec[tree->nP-1].pos = a;
  tree->vec[tree->nP-1].id = id;  
}

//A2
void addNode(Quad *level, Node *no) { newNode(level, no->pos, no->id); }

//A3
Quad *newQuadZero(Point a, Point b)
{
  Quad *tree = (Quad*)malloc(sizeof(Quad));

  if ( tree==NULL )
    {
      fprintf(stderr,"Falta de memória em newQuadZero\n");
      exit(EXIT_FAILURE);
    }

  tree->tl = a;
  tree->br = b;

  tree->vec = NULL;
  tree->nP = 0;
  
  tree->nw=NULL;
  tree->ne=NULL;
  tree->sw=NULL;
  tree->se=NULL;

  return tree;
}

//
Quad *initiateTree()
{
  Point p1, p2;

  p1.x=1; p1.y=mapSize;
  p2.x=mapSize; p2.y=1;
  
  return newQuadZero(p1, p2);
}

//A4
void newPartition(Quad *tree)
{
  if ( possibleToDivide(tree) )
    { 
      divideInFour(tree);
      
      copyAll(tree);

      free(tree->vec);
      tree->vec=NULL;
    }
}

//
int possibleToDivide(Quad *tree)
{
  int t1 = tree->br.x - tree->tl.x + 1;
  int t2 = tree->tl.y - tree->br.y + 1;

  return t1*t2>=Lim ? 1: 0;
}

//A5
void divideInFour(Quad *tree)
{
  int t1, t2;
  Point p1, p2;
  
  t1 = (tree->br.x - tree->tl.x)/2;
  t2 = (tree->tl.y - tree->br.y)/2;

  // NorthWest
  p2.x = t1;
  p2.y = t2 + 1;

  tree->nw = newQuadZero(tree->tl, p2);

  // NortEast
  p1.x = t1 + 1;
  p1.y = tree->tl.y;

  p2.x = tree->br.x;
  p2.y = t2 + 1;

  tree->ne = newQuadZero(p1, p2);

  // SoutWest
  p1.x = tree->tl.x;
  p1.y = t2;

  p2.x = t1;
  p2.y = tree->br.y;

  tree->sw = newQuadZero(p1, p2);

  // SouthEast
  p1.x = t1 + 1;
  p2.y = t2;

  tree->se = newQuadZero(p1, tree->br);
  
  //
  tree->nw->father = tree;
  tree->ne->father = tree;
  tree->sw->father = tree;
  tree->se->father = tree;
}

//A6
void copyAll(Quad *father)
{  
  for( int i=0; i<father->nP; i++ )
    {
      Node *temp = &father->vec[i];

      switch( whereToPut(*father, temp->pos) )
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
	  
        default:
	  addNode(father->ne, temp);
	  break;
	}     
    }
}

//A7
int whereToPut(Quad level, Point p)
{
  int t1, t2;
  
  t1 = (level.br.x - level.tl.x)/2;
  t2 = (level.tl.y - level.br.y)/2;

  if ( level.nw==NULL ) // 0=>poem no nivel currente
    return 0;
  
  else if ( p.x<=t1 && p.y<=t2 ) // 1=>poe no filho SW
    return 1;

  else if ( p.x<=t1 ) //3=>poe no filho NW
    return 3;

  else if ( p.y<=t2 ) //2=>pow no filho SE
    return 2;

  else //4=>poe no filho NE
    return 4;
}
