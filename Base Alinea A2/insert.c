#include "insert.h"


/*----------------------Insert Manual-------------------------*/
void insertManual(Map *m)
{
  int id;
  char dir;
  Point p;

  if ( m->ship==NULL )
    errorMessageMap("insertManual");
  
  while ( someShipLeft(m->ship) )
    {
      scanf("%d %d %d %c", &id, &p.x, &p.y, &dir);

      if( placeIsPossible(m, &m->ship[id], &p, dir) )
	insertShip(m, &m->ship[id], &p, dir);
      
      else
	printf("Cannot place the ship\n");
    }
}

/*----------------------Insert Random-----------------------*/
void insertRandom(Map *m)
{
  Point p;
  char dir;

  if ( m->ship==NULL )
    errorMessageMap("insertRandom");
    
  for( int id = nextShip(m->ship); id!=-1; id=nextShip(m->ship) )
    {
      randomDir(&dir);
      
      findSomePlace(m, &m->ship[id], &p, &dir);
      
      insertShip(m, &m->ship[id], &p, dir);
    }  
}

void findSomePlace(Map *m, Ship *ship, Point *p, char *dir)
{
  for( randomPoint(m, p); !findSomeDir(m, ship, p, dir); movePointLeft(m, p));
}

int findSomeDir(Map *m, Ship *ship, Point *p, char *dir)
{
  int i;
  
  for( i=0; i<4 && !placeIsPossible(m, ship, p, *dir); rotateDir(dir), i++ );

  return i<4 ? 1: 0;
}

/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *m, Ship *ship, Point *ref, char dir)
{
  Point p;

  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);

      insertPoint(m, &p, ship);
    }

  ship->active++;
  ship->left--;
}

void insertPoint(Map *map, Point *p, Ship *ship)
{
  if ( !inBound(map, p) )
    errorMessageOut("insertPoint", p);
    
  map->board[p->y-1][p->x-1].ship = ship;
  map->board[p->y-1][p->x-1].bit = '1';
  map->nPoint++;
}

int shot(Map *map1, Map *map2, Point *p)
{
  int x = p->x-1, y = p->y - 1;
  
  if ( search(map2, p)==NULL )
    {
      map1->board[y][x].shot = '1';
      map2->board[y][x].bit = '3';

      return 0;
    }

  else
    {
      map1->board[y][x].shot = '2';
      map2->board[y][x].bit = '2';

      return 1;
    }
}


/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *m, Ship *ship, Point *p, char dir)
{
  return inBound(m, p) &&
    shipAvaliable(ship) &&
    confAvaliable(m, ship, p, dir) ? 1: 0;  
}

int confAvaliable(Map *m, Ship *ship, Point *ref, char dir)
{
  Point p;

  if ( !inBound(m, ref) )
    errorMessageOut("conAvaliable", ref);
  
  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);

      if ( !inBound(m, &p) )
	return 0;

      else if ( search(m, &p)!=NULL )
	return 0;

      else if ( !voidAroundPoint(m, &p) )
	return 0;
    }

  return 1;
}

int voidAroundPoint(Map *m, Point *p)
{
  Point temp;
  temp.x = p->x; temp.y = p->y;

  if ( !inBound(m, p) )
    errorMessageOut("voidAroundPoint", p);

  for( int i=-1; i<=1; i++ )
    if ( i )
      {
	temp.x = p->x + i;
	temp.y = p->y;

	if ( inBound(m, &temp) && search(m, &temp)!=NULL )
	  return 0;

	temp.x = p->x;
	temp.y = p->y + i;
	
	if ( inBound(m, &temp) && search(m, &temp)!=NULL)
	  return 0;	
      }

  return 1;
}
/*---------------------Generate next/random-------------------------*/
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

void randomPoint(Map *m, Point *p)
{
  int n = rand() % ( m->mapSize * m->mapSize );

  p->x = n / m->mapSize + 1;
  p->y = n % m->mapSize + 1;  
}


/*--------------------------Move Point------------------------------*/
void movePointLeft(Map *m, Point *p)
{
  if ( !inBound(m, p) )
    errorMessageOut("movePointLeft", p);
  
  p->x++;

  if ( p->x > m->mapSize )
    {
      p->y++;
      p->x=1;
    }

  if ( p->y > m->mapSize  )
    p->y = 1;
}

void movePointInDir(Point *ref, Point *vec, Point *p, char dir)
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
      fprintf(stderr,"Error on movePointInDir %c unknown direction\n", dir);
      exit(EXIT_FAILURE);  
    }
}
