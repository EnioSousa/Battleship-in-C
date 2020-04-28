#include "ship.h"

/*-----------------------Initiate--------------------------*/
Ship* initiateShip()
{
  Ship *arr= (Ship*)malloc(5*sizeof(Ship));

  if ( arr==NULL )
    errorMessageMem("initiateShip");
  
  arr[0].num=1;
  arr[1].num=2;
  arr[2].num=2;
  arr[3].num=2;
  arr[4].num=4;
  
  for(int i=0; i<NumDifShip; i++)
    {
      arr[i].id = '0' + i;
      arr[i].size = 5 - i;
      arr[i].left = arr[i].num;
      arr[i].active = 0;
      arr[i].vec = (Point*)malloc(arr[i].size*sizeof(Point));

      if ( arr[i].vec==NULL )
	errorMessageMem("initiateShip");
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

void freeShip(Ship *ship)
{
  for( int i=0; i<NumDifShip; i++ )
    {
      free(ship[i].name);
      free(ship[i].vec);
    }

  free(ship);
  ship = NULL;
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

