#include "player.h"
#include "input.h"
#include "error.h"
#include <stdlib.h>
#include "interface.h"
#include <stdio.h>
#include "game.h"

/*-----------------------Initiate--------------------------------*/

Player *initiatePlayer(int size)
{
  Player *p = (Player*)malloc(sizeof(Player));
  if(p==NULL)
  errorMessageMem("player");
  
  p->countPoints = (int*)malloc(4*sizeof(int));
  if(p->countPoints ==NULL)
  errorMessageMem("count points");
  
  for(int i=0;i<5;i++)
  p->countPoints[i] =0;
  
  Ship* s = initiateShip();
  p->map= newMap(size,s);
  p->his = newMap(size,s);
  p->name = getName();
  p->nhit=0;
  p->map->ship=s;
  clearTerminal();
  inicGame(p->name,0);
  printAllShip(p->map->ship);
  waitS(4);
  clearTerminal();
  askForMap(p->map);
  printPlayer(p);
  return p;     
}

 /*-----------------------Print-----------------------------------*/ 

void printPlayer(Player *p)
{ 
  printf(ANSI_COLOR_YELLOW"Player: %s\n"ANSI_COLOR_RESET, p->name);
  printf(ANSI_COLOR_GREEN"Your Ships\n"ANSI_COLOR_RESET);
  printMap(p->map,0);
  printf(ANSI_COLOR_GREEN"You history of atacks\n"ANSI_COLOR_RESET);
  printMap(p->his,1);
  
}


 void printShipEnemy (Ship* ship, Player* p){ 
  
  printf(ANSI_COLOR_YELLOW"Enemy:\n\n"ANSI_COLOR_RESET);	
  printf(ANSI_COLOR_GREEN"Active:\n"ANSI_COLOR_RESET);
  
  if(p->countPoints[0]!=5)
  PrintShipName(ship,0);
  if(p->countPoints[1]!=8)
  PrintShipName(ship,1);
  if(p->countPoints[2]!=6)
  PrintShipName(ship,2);
  if(p->countPoints[3]!=4)
  PrintShipName(ship,3);
  if(p->countPoints[4]!=4)
  PrintShipName(ship,4);
  printf("\n\n");
}
 
  void printShootShip(int v,Ship* ship,Player* p){
	printf(ANSI_COLOR_GREEN "Hit the %s \n\n"ANSI_COLOR_RESET, ship[v].name);
	p->countPoints[v]++;
}

