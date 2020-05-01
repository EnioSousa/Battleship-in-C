#include "player.h"
#include "input.h"
#include "errorMessage.h"
#include <stdlib.h>
#include "interface.h"
#include <stdio.h>
#include "game.h"

/*-----------------------Initiate--------------------------------*/

Player *initiatePlayer(int size,int i)
{
  Player *p = (Player*)malloc(sizeof(Player));
  if(p==NULL)
  errorMessageMem("player");
  
  p->map=newMap(size);
  p->name = getName();
  clearTerminal();
  inicGame(p->name,0);
  if(i==0){
  printAllShip(p->map->ship);
  }
  waitS();
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
  printMapShip(p->map);
  waitS();
  clearTerminal();
  printf(ANSI_COLOR_GREEN"You history of atacks\n"ANSI_COLOR_RESET);
  printMapHistory(p->map);
  
 }



