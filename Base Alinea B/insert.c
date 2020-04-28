#include "insert.h"

/*----------------------Insert Manual-------------------------*/
void insertManual(Map *root)
{
  int id, x, y;
  char dir;
  Point p;
  
  while ( someShipLeft(root->ship) )
    {
      scanf("%d %d %d %c", &id, &x, &y, &dir);

      p.x=x; p.y=y;

      if( placeIsPossible(root, &root->ship[id], &p, dir) )
	{
	  insertShip(root, &root->ship[id], &p, dir);
	  root->ship[id].left--;

	  printMapDebbug(root);
	}

      else
	printf("Cannot place the ship\n");
    }
}

/*----------------------Insert Random-----------------------*/
void insertRandom(Map *root)
{
  Point p;
  char dir;
  
  for( int id = nextShip(root->ship); id!=-1; id=nextShip(root->ship) )
    {
      randomDir(&dir);
      
      findSomePlace(root, &root->ship[id], &p, &dir);
      
      insertShip(root, &root->ship[id], &p, dir);

      root->ship[id].left--;
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

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *level, Ship *ship, Point *p, char dir)
{
  return !outOfBounds(level, p) && shipAvaliable(ship) && confAvaliable(level, ship, p, dir);
}

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

  if ( outOfBounds(m, ref) )
    errorMessageOut("conAvaliable");
  
  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);
      
      if ( outOfBounds(m, &p) )
	return 0;

      else if ( searchNode(m, &p)!=NULL )
	return 0;

      else if ( !voidAroundPoint(m, &p) )
	return 0;
    }
  
  return 1;
}

int voidAroundPoint(Map *root, Point *p)
{
  if ( root==NULL || p==NULL )
    errorMessagePointer("voidAroundPoint");
  
  Point temp;
  temp.x = p->x; temp.y = p->y;

  for( int i=-1; i<=1; i++ )
    if ( i )
      {
	temp.x = p->x + i;
	temp.y = p->y;

	if ( !outOfBounds(root, p) && searchNode(root, &temp)!=NULL )
	  return 0;

	temp.x = p->x;
	temp.y = p->y + i;
	
	if ( !outOfBounds(root, p) && searchNode(root, &temp)!=NULL )
	  return 0;	
      }

  return 1;
}

/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *root, Ship *ship, Point *ref, char dir)
{
  Point p;

  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);
      
      insertPoint(root, &p, ship->id);
    }
}

void insertPoint(Map *root, Point *p, char id)
{
  if ( outOfBounds(root, p) )
    {
      printPoint(p);
      errorMessageOut("insertPoint");
    }
  
  insertPointInLevel(searchDepth(root, p), p, id);
}

void insertPointInLevel(Map *level, Point *p, char id)
{
  if ( level==NULL )
    errorMessagePointer("insertPointInLevel");

  int index = level->nP;
  
  level->nP++;
  
  level->vec = (Node *)realloc(level->vec, level->nP*sizeof(Node));

  if ( level->vec==NULL )
    errorMessageMem("insertPointInLevel");

  level->vec[index].pos = newPoint(p->x, p->y);
  level->vec[index].id = id;

  incUp(level->father);
  
  if ( level->nP>LIM && level->nw==NULL )
    newPartition(level);
}

void incUp(Map *level)
{
  if ( level==NULL )
    return;

  level->nP++;

  incUp(level->father);
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
  if ( outOfBounds(m, p) )
    errorMessageOut("movePointLeft");
  
  p->x++;

  if ( p->x > m->br->x )
    {
      p->y--;
      p->x = m->tl->x;
    }

  if ( p->y < 1 )
    p->y = m->tl->y;
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
      p->y = ref->y + vec->y;
      break;

    case 'n':
      p->x = ref->x - vec->y;
      p->y = ref->y + vec->x;
      break;

    case 's':
      p->x = ref->x + vec->y;
      p->y = ref->y - vec->x;
      break;
      
    default:
      fprintf(stderr,"Error on movePointInDir %c unknown direction\n", dir);
      exit(EXIT_FAILURE);  
    }
}
