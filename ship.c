#include "ship.h"

Ship* initiateShip()
{
  Ship* arr= (Ship*)malloc(5*sizeof(Ship));

  for(int i=0; i<NumDifShip; arr[i].id=i, i++);
  
  strcpy(arr[0].name, "Carrier");
  strcpy(arr[1].name, "Battleship");
  strcpy(arr[2].name, "Cruiser");
  strcpy(arr[3].name, "Submarine");
  strcpy(arr[4].name, "Destroyer");

  arr[0].size=5;
  arr[1].size=4;
  arr[2].size=3;
  arr[3].size=3;
  arr[4].size=2;

  arr[0].num=1;
  arr[1].num=2;
  arr[2].num=2;
  arr[3].num=1;
  arr[4].num=4;

  for(int i=0; i<NumDifShip; arr[i].left=arr[i].num, i++);

  for( int i=0; i<NumDifShip; i++ )
    arr[i].vec = (Point*)malloc(arr[i].size*sizeof(Point)); 

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

  ship[0].vec[4].x = 1;
  ship[0].vec[4].y = -1;
}

void printShip(Ship* arr)
{
  for( int i=0; i<NumDifShip; i++ )
    {
      printf("name=%s, id=%d\n", arr[i].name, arr[i].id);
      printf("size=%d, ", arr[i].size);
      printf("num=%d, left=%d\n\n", arr[i].num, arr[i].left);
    }
}
