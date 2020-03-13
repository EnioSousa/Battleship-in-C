#include "insert.h"


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

      if ( possible(root, &ship[id], p, dir) )
	{
	  insertShip(root, &ship[id], p, dir);
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


void insertRandom(Quad *root, Ship* ship)
{
  Point p;
  char dir;
  
  srand(time(NULL));

  for( int i=nextShip(ship); i!=-1; i=nextShip(ship) )
    {
      randomDir(&dir);
      
      for( randomPoint(&p); !checkPossible(root, &ship[i], &p, &dir); translatePoint(&p) );

      insertShip(root, &ship[i], p, dir);  
      ship[i].left--;      
    }
}

int checkPossible(Quad *tree, Ship *ship, Point *p, char *dir)
{
  int i;

  for( i=1; i<4 && !possible(tree, ship, *p, *dir); rotateDir(dir), i++ );

  return i<4 ? 1: 0;
}

int nextShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( ship[i].left )
      return i;

  return -1;
}

void randomPoint(Point *p)
{
  int n = rand() % ( mapSize * mapSize );

  p->x = n / mapSize + 1;
  p->y = n % mapSize + 1;
}

void randomDir(char *dir)
{
  switch( rand() % 4 )
    {
    case 0:
      *dir = 'e';
      break;
      
    case 1:
      *dir = 'n';
      break;
      
    case 2:
      *dir = 'w';
      break;
      
    default:
      *dir = 's';
      break;     
    }
}

void translatePoint(Point *p)
{
  p->x++;

  if ( p->x>mapSize )
    {
      p->x = 1;
      p->y++;
    }

  if ( p->y > mapSize )
    p->y = 1;
}

void rotateDir(char *dir)
{
  switch(*dir)
    {
    case 'e':
      *dir = 'n';
      break;
    case 'n':
      *dir = 'w';
      break;
    case 'w':
      *dir = 's';
      break;

    default:
      *dir = 'e';
      break;
    }
}

//
void insertShip(Quad *root, Ship *ship, Point ref, char dir)
{
  Point p;
  
  for( int i=0; i<ship->size; i++ )
    {
      movePoint(&ref, &ship->vec[i], &p, dir);
      
      insertPoint(root, p, ship->id);
    }
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
      fprintf(stderr,"Error Point already Exist\n");
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
void movePoint(Point *ref, Point *vec, Point *p, char dir)
{
  switch(dir)
    {
    case 'e':
      p->x = ref->x + vec->x;
      p->y = ref->y + vec->y;
      break;

    case 'w':
      p->x = ref->x - vec->x;
      p->y = ref->y - vec->y;
      break;

    case 'n':
      p->x = ref->x + vec->y;
      p->y = ref->y + vec->x;
      break;

    case 's':
      p->x = ref->x - vec->y;
      p->y = ref->y - vec->x;
      break;
      
    default:
      fprintf(stderr,"Point already Exist\n");
      exit(EXIT_FAILURE);  
    }
}

//
int possible(Quad *root, Ship *ship, Point p, char dir)
{
  return shipAvaliable(ship) && confAvaliable(root, ship, p, dir) ? 1: 0; 
}

//
int confAvaliable(Quad *root, Ship *ship, Point ref, char dir)
{
  Point p;
  
  for( int i=0; i<ship->size;  i++ )
    {
      movePoint(&ref, &ship->vec[i], &p, dir);
	
      if ( simpleSearch(root, p)!=NULL || !insideOfMap(p) )
	return 0;

      else if (  !voidAround(root, p) )
	return 0;
    }
  
  return 1;
}

int voidAround(Quad *root, Point p)
{
  Point temp;
  temp.x = p.x;
  temp.y = p.y;

  for( int i=-1; i<2; i++ )
    {
      if ( i!=0 )
	{
	  temp.x = p.x + i;
	  temp.y = p.y;

	  if ( insideOfMap(temp) )
	    if ( simpleSearch(root, temp)!=NULL )
	      return 0;
	  
	  temp.x = p.x;
	  temp.y = p.y + i;
	  
	  if ( insideOfMap(temp) )
	    if ( simpleSearch(root, temp)!=NULL )
	      return 0;	  
	}
    }
  
  return 1;
}

//
int insideOfMap(Point p)
{
  return p.x>0 && p.x<=mapSize && p.y>0 && p.y<=mapSize ? 1: 0;
}

//
int shipAvaliable(Ship *ship) { return ship->left!=0 ? 1: 0; }

