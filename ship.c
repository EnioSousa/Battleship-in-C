#include <string.h>

/* Numero de navios diferentes */
#define NumDifShip 5


/* Name -> nome do navio
   Size -> tamanho que o navio ocupa
   Num -> numero de navios a serem colocados
   Left -> numero de navios que falta ser posto*/
typedef struct ship
{
  char name[20];
  int size, num, left, id;
  
}Ship;


Ship* initiateShip()
{
  Ship* arr = (Ship*)malloc(5*sizeof(Ship));

  for( int i=0; i<NumDifShip; arr[i].id=i, i++ );
  
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

  for( int i=0; i<NumDifShip; arr[i].left=arr[i].num, i++ );

  return arr;
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
