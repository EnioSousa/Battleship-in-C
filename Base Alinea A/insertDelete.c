#include "insertDelete.h"


/*----------------------Insert Manual-------------------------*/
void insertManual(Map *m)
{
  int id;
  char dir;
  Point p;

  if ( m->ship==NULL )
    errorMessageMap("insertManual");
  
  while ( someShipLeft(m) )
    {
      scanf("%d %d %d %c", &id, &p.x, &p.y, &dir);

      if( placeIsPossible(m, &m->ship[id], &p, dir) )
	{
	  insertShip(m, &m->ship[id], &p, dir);
	}

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
  
  for( int id = nextShip(m); id!=-1; id=nextShip(m) )
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

      insertPoint(m, &p, '0' + ship->id);
    }

  ship->active++;
  ship->left--;
}

// mudar esta função se a estrutura map mudar
void insertPoint(Map *m, Point *p, char ch)
{
  if ( !inBound(m, p) )
    errorMessageOut("insertPoint", p);

  m->map[p->y-1][p->x-1] = ch;
  m->nPoint++;  
}

/*---------------------------delete------------------------------*/
void deletePoint(Map *m, Point *p)
{
  if ( !inBound(m, p) )
    errorMessageOut("deletePoint", p);

  char ch = search(m, p);

  m->map[p->y-1][p->x-1] = WATER;

  if ( ch!=WATER && m->ship!=NULL )
    {
      int id = ch - '0';

      if ( voidAroundPoint(m, p) )
	m->ship[id].active--;

      m->nPoint--;
    }  
}

void deleteAll(Map *m)
{
  Point p;
  
  for( int i=1; i<=m->mapSize; i++ )
    for( int j=1; j<=m->mapSize; j++ )
      {
	p.x = i; p.y = j;
	deletePoint(m, &p);
      }

  m->nPoint = 0;
}

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *m, Ship *ship, Point *p, char dir)
{
  return inBound(m, p) &&
    shipAvaliable(ship) &&
    confAvaliable(m, ship, p, dir) ? 1: 0;
}

int someShipLeft(Map *m)
{
  if ( m->ship==NULL )
    errorMessageMap("someShipLeft");
  
  for( int i=0; i<NumDifShip; i++ )
    if ( shipAvaliable(&m->ship[i]) )
      return 1;

  return 0;  
}

int shipAvaliable(Ship *ship) { return ship->left!=0 ? 1: 0; }

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

      else if ( search(m, &p)!=WATER )
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

	if ( inBound(m, &temp) && search(m, &temp)!=WATER )
	  return 0;

	temp.x = p->x;
	temp.y = p->y + i;
	
	if ( inBound(m, &temp) && search(m, &temp)!=WATER )
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

int nextShip(Map *m)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( m->ship[i].left )
      return i;

  return -1;
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
