#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Numero de navios diferentes */
#define NumDifShip 5

/* Name -> nome do navio
   Size -> tamanho que o navio ocupa
   Num -> numero de navios a serem colocados
   Left -> numero de navios que falta ser posto*/
typedef struct ship
{
  char Name[20];
  int Size, Num, Left, ID;
  
}Ship;


Ship* initiateShip()
{
  Ship* arr = (Ship*)malloc(5*sizeof(Ship));

  for( int i=0; i<NumDifShip; arr[i].ID=i, i++ );
  
  strcpy(arr[0].Name, "Carrier");
  strcpy(arr[1].Name, "Battleship");
  strcpy(arr[2].Name, "Cruiser");
  strcpy(arr[3].Name, "Submarine");
  strcpy(arr[4].Name, "Destroyer");

  arr[0].Size=5;
  arr[1].Size=4;
  arr[2].Size=3;
  arr[3].Size=3;
  arr[4].Size=2;

  arr[0].Num=1;
  arr[1].Num=2;
  arr[2].Num=2;
  arr[3].Num=1;
  arr[4].Num=4;

  for( int i=0; i<NumDifShip; arr[i].Left=arr[i].Num, i++ );

  return arr;
}

void printShip(Ship* arr)
{
  for( int i=0; i<NumDifShip; i++ )
    {
      printf("Name=%s, ID=%d\n", arr[i].Name, arr[i].ID);
      printf("Size=%d, ", arr[i].Size);
      printf("Num=%d, Left=%d\n\n", arr[i].Num, arr[i].Left);
    }
}
