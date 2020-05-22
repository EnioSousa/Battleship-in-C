#include "ship.h"

/*-----------------------Initiate--------------------------*/

Ship *initiateShip(int nShips)
{
  Ship *arr = (Ship *)malloc(5 * sizeof(Ship));

  arr[0].num = nShips / 10;
  arr[1].num = nShips / 10;
  arr[2].num = nShips / 5;
  arr[3].num = nShips / 5;
  arr[4].num = 2 * nShips / 5;
  ;

  for (int i = 0; i < NumDifShip; i++)
  {
    arr[i].id = i;
    arr[i].size = 5 - i;
    arr[i].left = arr[i].num;
    arr[i].active = 0;
    arr[i].vec = (Point *)malloc(arr[i].size * sizeof(Point));
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

/*-------------------------Check--------------------------*/

int someShipLeft(Ship *ship)
{
  if (ship == NULL)
    errorMessageMap("someShipLeft");

  for (int i = 0; i < NumDifShip; i++)
    if (shipAvaliable(&ship[i]))
      return 1;

  return 0;
}

int shipAvaliable(Ship *ship) { return ship->left != 0 ? 1 : 0; }

int nextShip(Ship *ship)
{
  for (int i = 0; i < NumDifShip; i++)
    if (ship[i].left)
      return i;

  return -1;
}

int someActiveShip(Ship *ship)
{
  for (int i = 0; i < NumDifShip; i++)
    if (ship[i].active)
      return 1;

  return 0;
}

/*-------------------------Free---------------------------*/

void freeShip(Ship *ship)
{
  for (int i = 0; i < NumDifShip; i++)
    free(ship[i].vec);

  free(ship);
}
