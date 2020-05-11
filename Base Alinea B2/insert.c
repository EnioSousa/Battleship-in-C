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

      else if ( searchShip(m, &p)!=NULL )
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

	if ( !outOfBounds(root, p) && searchShip(root, &temp)!=NULL )
	  return 0;

	temp.x = p->x;
	temp.y = p->y + i;
	
	if ( !outOfBounds(root, p) && searchShip(root, &temp)!=NULL )
	  return 0;	
      }

  return 1;
}
  
/*----------------------Insert Ship-----------------------*/
void insertShip(Map *root, Ship *ship, Point *ref, char dir)
{
  Point p;
  for( int i=0; i<ship->size; i++ )
    {
      movePointInDir(ref, &ship->vec[i], &p, dir);
  
      insertPointer(root, &p, ship);
    }

  ship->left--;

  ship->active++;
}

void insertPointer(Map *root, Point *p, Ship *ship)
{
  if ( outOfBounds(root, p) )
    {
      printPoint(p);
      errorMessageOut("insertPoint");
    }

  Map *level = searchDepth(root, p);

  if ( level==NULL )
    errorMessagePointer("insertPoint");

  Node *temp = searchLevel(level, p);

  if ( temp==NULL )
    newNode(level, ship, p, '1', '0');
  
  else
    {
      if ( temp->cell==NULL )
	errorMessagePointer("insertCellInLevel");
      
      temp->cell->ship = ship;
      temp->cell->bit = '1';
    }
}

/*----------------------Insert shoot-----------------------*/
void insertShoot(Map *root, Point *p, char shoot)
{
  Map *level = searchDepth(root, p);

  if ( level==NULL )
    errorMessagePointer("insertPoint");
  
  Node *temp = searchLevel(level, p);

  if ( temp==NULL )
    newNode(level, NULL, p, '0', shoot);

  else
    {
      if ( temp->cell==NULL )
	errorMessagePointer("insertShoot");

      temp->cell->shoot = shoot;
    }
}

/*----------------------Insert bit-----------------------*/
void insertBit(Map *root, Point *p, char bit)
{
  Map *level = searchDepth(root, p);

  if ( level==NULL )
    errorMessagePointer("insertPoint");
  
  Node *temp = searchLevel(level, p);

  if ( temp==NULL )
    newNode(level, NULL, p, bit, '0');

  else
    {
      if ( temp->cell==NULL )
	errorMessagePointer("insertShoot");

      temp->cell->bit = bit;
    }
}

/*-----------------------Dispara-------------------------*/
int shootOponent(Map *map1, Map *map2, Point *p)
{
  char *temp = searchBit(map2, p);

  if ( temp==NULL || *temp == '0' )
    {
      insertBit(map2, p, '3');
      insertShoot(map1, p, '1');
      return 0;
    }

  else if ( *temp == '2' )
    return 0;

  else if ( *temp == '1' )
    {
      insertBit(map2, p, '2');
      insertShoot(map1, p, '2');

      if ( sunk(map2, p) )
	{
	  Ship *ship = searchShip(map2, p);

	  if ( ship==NULL )
	    errorMessagePointer("shootOponent");

	  ship->active--;
	}

      return 1;
    }

  else
    {
      fprintf(stderr, "Construiste mal alguma celula ou não estas a verificar tudo\n");
      exit(EXIT_FAILURE);
    }
}

int sunk(Map *map, Point *p)
{
  Point vec, p1;
  vec.x = 1;
  vec.y = 0;

  char *temp = searchBit(map, p);

  if ( temp==NULL )
    {
      fprintf(stderr, "Error on sunk\n");
      printPoint(p);
      exit(EXIT_FAILURE);
    }

  char saveBit = *temp;
  
  insertBit(map, p, '4');

  int cond;
  
  movePointInDir(p, &vec, &p1, 'e');
  cond = testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 'n');
  cond = cond && testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 'w');
  cond = cond && testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 's');
  cond = cond && testCondition(map, &p1);

  insertBit(map, p, saveBit);

  return cond;
}

int testCondition(Map *map, Point *p)
{
  if ( outOfBounds(map, p) )
    return 1;

  char *testBit = searchBit(map, p);

  return testBit==NULL || *testBit=='0' || *testBit=='3' || *testBit=='4' ? 1 :
    ( *testBit=='1' ? 0: sunk(map, p) );
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
