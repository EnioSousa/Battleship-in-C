#include "insert.h"
#include "interface.h"


/*----------------------Insert Manual-------------------------*/
void insertManual(Map *m, Ship *ship)
{
  int id, x, y,c;
  char dir;	
  Point p;
  int tmp=1;
  //srand(time(NULL));
  
  while ( someShipLeft(ship) )
    { 
	  c=1;
	  clearTerminal();
      if(tmp==1)
      temporyPrint();
      if(tmp==0)
      printMap2(m);
      while(c){
      c=0;
      printf(ANSI_COLOR_GREEN "Enter the ship's identification,the x and y coordinates and the direction of the ship\n"ANSI_COLOR_RESET);
      if(tmp==1){
      printf(ANSI_COLOR_GREEN "Example of an entry: 4 4 5 w \n"ANSI_COLOR_RESET);   
      tmp=0;
      }
      scanf("%d %d %d %c", &id, &x, &y, &dir);
      if(checkDir(dir)==0){
      wait();
      clearTerminal();
      c=1;
      }
      }
      p.x=x; p.y=y;

      if( placeIsPossible(m, &ship[id], &p, dir) )
	{
	  insertShip(m,&ship[id],&p, dir);
	  ship[id].left--;

	  printAll(m);
	}

      else
	printf("Cannot place the ship\n");
	wait();
    }
}

/*----------------------Insert Random-----------------------*/
void insertRandom(Map *m, Ship* ship)
{
  Point p;
  char dir;
  
  for( int id = nextShip(ship); id!=-1; id=nextShip(ship) )
    {
      randomDir(&dir);

      findSomePlace(m, &ship[id], &p, &dir);
      
      insertShip(m, &ship[id], &p, dir);

      ship[id].left--;
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

      insertPoint(m, &p, ship->id);
    }
}
void insertHit (Map *m, Point *p, char id)
{
  if ( !insideOfMap(m, p) )
    errorMessage2("insertPoint", p);

  m->map[p->y-1][p->x-1] = id;
  m->nPoint++;  
}



// mudar esta função se a estrutura map mudar
void insertPoint(Map *m, Point *p, int id)
{
  if ( !insideOfMap(m, p) )
    errorMessage2("insertPoint", p);

  m->map[p->y-1][p->x-1] = '0' + id;
  m->nPoint++;  
}

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *m, Ship *ship, Point *p, char dir)
{
  return insideOfMap(m, p) && shipAvaliable(ship) && confAvaliable(m, ship, p, dir) ? 1: 0;
}

int insideOfMap(Map *m,Point *p) { return p->x>0 && p->x<=m->mapSize && p->y>0 && p->y<=m->mapSize ? 1: 0; }

int shipAvaliable(Ship *ship) { return ship->left!=0 ? 1: 0; }

int someShipLeft(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( shipAvaliable(&ship[i]) )
      return 1;

  return 0;  
}

int confAvaliable(Map *m, Ship *ship, Point *ref, char dir)
{
  Point p;

  if ( !insideOfMap(m, ref) )
    errorMessage2("conAvaliable", ref);
  
  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);

      if ( !insideOfMap(m, &p) )
	return 0;

      else if ( search(m, &p) )
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

  if ( !insideOfMap(m, p) )
    errorMessage2("voidAroundPoint", p);

  for( int i=-1; i<=1; i++ )
    if ( i )
      {
	temp.x = p->x + i;
	temp.y = p->y;

	if ( insideOfMap(m, &temp) && search(m, &temp) )
	  return 0;

	temp.x = p->x;
	temp.y = p->y + i;
	
	if ( insideOfMap(m, &temp) && search(m, &temp) )
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

int nextShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( ship[i].left )
      return i;

  return -1;
}


/*--------------------------Move Point------------------------------*/
void movePointLeft(Map *m, Point *p)
{
  if ( !insideOfMap(m, p) )
    errorMessage2("movePointLeft", p);
  
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

/*---------------------------Error message2------------------------*/
void errorMessage2(char *str, Point *p)
{
  fprintf(stderr, "Error on %s, Point (%d,%d) out of bounds\n", str, p->x, p->y);
  exit(EXIT_FAILURE);  
}
