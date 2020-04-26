#include "ship.h"
#include "error.h"
#include "interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*-----------------------Initiate--------------------------*/
Ship* initiateShip()
{
  Ship *arr= (Ship*)malloc(5*sizeof(Ship));
  if(arr==NULL)
  errorMessageMem("Ship");
  
  arr[0].num=1;
  arr[1].num=2;
  arr[2].num=2;
  arr[3].num=2;
  arr[4].num=4;
  
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

/*-------------------------Print--------------------------*/
void printAllShip(Ship *arr)
{
  printf(ANSI_COLOR_RED "Information\n"ANSI_COLOR_RESET);
  
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
  printf(ANSI_COLOR_RED "Name %s, id %d "ANSI_COLOR_RESET, ship->name, ship->id);
  printf(ANSI_COLOR_GREEN"Size %d ", ship->size);
  printf("Number %d \n"ANSI_COLOR_RESET , ship->num);
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
    for( int j=0; j<n; j++ ){
      if(temp[i][j]=='#')
      printf(ANSI_COLOR_BLUE"%c "ANSI_COLOR_BLUE, temp[i][j]);
      else
      printf(ANSI_COLOR_YELLOW"%c "ANSI_COLOR_BLUE, temp[i][j]);
}
}

void informationShipRemaining(Ship* s){
	
	printf("Number of ships remaining:\n");
	if(s[0].left!=0)
	printf(ANSI_COLOR_YELLOW"Id:0 -->Carrier: %d \n",s[0].left);
	if(s[1].left!=0)
	printf("Id:1 -->Battleship: %d \n",s[1].left);
	if(s[2].left!=0)
	printf("Id:2 -->Cruiser: %d \n",s[2].left);
	if(s[3].left!=0)
	printf("Id:3 -->Submarine: %d \n",s[3].left);
	if(s[4].left!=0)
	printf("Id:4 -->Destroyer: %d \n"ANSI_COLOR_RESET,s[4].left);
    printf("\n");
}


void PrintShipName(Ship* s,int i){
  printf(ANSI_COLOR_GREEN "Id:%d "ANSI_COLOR_RESET,s[i].id);
  printf(ANSI_COLOR_RED "%s  "ANSI_COLOR_RESET, s[i].name);
}


