#include "ship.h"

/*-----------------------Initiate--------------------------*/
Ship* initiateShip(int nShips)
{
  Ship *arr= (Ship*)malloc(5*sizeof(Ship));

  arr[0].num=nShips/10;
  arr[1].num=nShips/10;
  arr[2].num=nShips/5;
  arr[3].num=nShips/5;
  arr[4].num=2*nShips/5;;
  
  for(int i=0; i<NumDifShip; i++)
    {
      arr[i].id = i;
      arr[i].size = 5 - i;
      arr[i].left = arr[i].num;
      arr[i].active = 0;
      arr[i].vec = (Point*)malloc(arr[i].size*sizeof(Point)); 
    }
  
  strcpy(arr[0].name, "Carrier");
  strcpy(arr[1].name, "Battleship");
  strcpy(arr[2].name, "Cruiser");
  strcpy(arr[3].name, "Submarine");
  strcpy(arr[4].name, "Destroyer");

  defineForm(arr);
  
  return arr;
}

void defineForm(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    for( int j=0;j<ship[i].size; j++ )
      {
	ship[i].vec[j].x = j;
	ship[i].vec[j].y = 0;
      }

  // carrier                                   
  ship[0].vec[3].x = 0;                       
  ship[0].vec[3].y = -1;                       

  ship[0].vec[4].x = 0;
  ship[0].vec[4].y = 1;
}


int someShipLeft(Ship *ship)
{
  if ( ship==NULL )
    errorMessageMap("someShipLeft");
  
  for( int i=0; i<NumDifShip; i++ )
    if ( shipAvaliable(&ship[i]) )
      return 1;

  return 0;  
}

int shipAvaliable(Ship *ship) { return ship->left!=0 ? 1: 0; }

int nextShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( ship[i].left )
      return i;

  return -1;
}

int someActiveShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    if ( ship[i].active )
      return 1;

  return 0;
}

/*-------------------------Print--------------------------*/
void printAllShip(Ship *arr)
{  
  for( int i=0; i<NumDifShip; i++ )
    printShip(&arr[i]);
}

void printShip(Ship *ship)
{
  printShipInfo(ship);

  printShipForm(ship);

  putchar('\n');  
}

void printAllShipInfo(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    printShipInfo(&ship[i]);
}

void printShipInfo(Ship* ship)
{
  printf("name=%s, id=%d\n", ship->name, ship->id);
  printf("size=%d, ", ship->size);
  printf("Num=%d active=%d\n", ship->num, ship->active);
}

void printShipForm(Ship *ship)
{
  int n = 5;
  
  char temp[n][n];
  
  for( int i=0; i<n; i++ )
    for( int j=0; j<n; j++ )
      temp[i][j] = '#';

  for( int i=0; i<ship->size; i++ )
    temp[(n/2)+ship->vec[i].y][ship->vec[i].x] = '0' + ship->id;
    
  for( int i=n-1; i>=0; putchar('\n'), i-- )
    for( int j=0; j<n; j++ )
      printf("%c ", temp[i][j]);
}

