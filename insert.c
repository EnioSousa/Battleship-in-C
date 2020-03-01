#include "QuadTree.h"
#include "QuadTree.c"
#include "ship.c"
#include "search.c"
#include "interface.c"

// falta fazer
void insertManual(Quad *root, Ship *ship);
//
int noMoreShip(Ship *ship);
// falta fazer
void insertRandom();
//
void insertShip(Quad *root, Ship ship, Point p, char dir);
//
void insertPoint(Quad *root, Point p, int id);
//
void movePoint(Point *p, char dir);
//
void incUp(Quad *level);
//
int possible(Quad *root, Ship ship, Point p, char dir);
//
int shipAvaliable(Ship ship);
//
int insideOfMap(Point p);
//
int confAvaliable(Quad *root, Ship ship, Point p, char dir);


//falta fazer
void insertManual(Quad *root, Ship *ship)
{
  int id, x, y;
  char dir;

  int n;
  scanf("%d", &n);
  
  while ( !noMoreShip(ship) && n>0 )
    {
      scanf("%d %d %d", &id, &x, &y);
      getchar();
      dir = getchar();

      Point p; p.x=x; p.y=y;

      if ( possible(root, ship[id], p, dir) )
	{
	  insertShip(root, ship[id], p, dir);
	  ship[id].left--;
	}

      else
	printf("Cannot place the ship\n");
      
      n--;
    }
}

//
int noMoreShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( ship[i].left )
      return 0;

  return 1;
}

//falta fazer
void insertRandom()
{

}



//
void insertShip(Quad *root, Ship ship, Point p, char dir)
{  
  for( int i=0; i<ship.size; movePoint(&p, dir), i++ )
    insertPoint(root, p, ship.id);
}


//
void insertPoint(Quad *root, Point p, int id)
{
  Quad *level = searchDepth(root, p);
  
  Node *no = searchLevel(level, p);

  if( no==NULL )
    {
      newNode(level, p, id);

      incUp(level->father);
      
      if ( level->nP>Lim )
	newPartition(level);
    }
  else
    {
      fprintf(stderr,"Point already Exist\n");
      exit(EXIT_FAILURE);
    }
}

//
void incUp(Quad *level)
{
  if ( level==NULL )
    return ;

  level->nP++;

  incUp(level->father);
}

//
void movePoint(Point *p, char dir)
{
  switch(dir)
    {
    case 'n':
      p->y++;
      break;

    case 's':
      p->y--;
      break;

    case 'e':
      p->x++;
      break;

    case 'w':
      p->x--;
      break;

    default:
      fprintf(stderr,"Error in movePoint dir not known\n");
      exit(EXIT_FAILURE);
    }
}

//
int possible(Quad *root, Ship ship, Point p, char dir)
{
  return shipAvaliable(ship) && confAvaliable(root, ship, p, dir) ? 1: 0; 
}

//
int confAvaliable(Quad *root, Ship ship, Point p, char dir)
{  
  for( int i=0; i<ship.size; movePoint(&p, dir), i++ )
    if ( simpleSearch(root, p)!=NULL || !insideOfMap(p) )
      return 0;
  
  return 1;
}

//
int insideOfMap(Point p)
{
  return p.x>0 && p.x<=mapSize && p.y>0 && p.y<=mapSize ? 1: 0;
}

//
int shipAvaliable(Ship ship) { return ship.left!=0 ? 1: 0; }

