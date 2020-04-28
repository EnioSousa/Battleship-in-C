#include "game.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "insertDelete.h"
#include "input.h"
#include "ship.h"
#include "map.h"

/*-----------------------Game--------------------------------*/

void game(Player* p1, Player* p2,int size){ 
  
  int f=0,cycleFirst=1,cycleSecond;
  Point* p =newPoint();
  Player* turn=p1;;
  Player* opp=p2;  
  while(cycleFirst){
  cycleSecond=1;
  printShipEnemy (turn->map->ship,turn);
  printPlayer(turn);
	   
	   while(cycleSecond){
	   if(f==1){
	   printShipEnemy (turn->map->ship,turn);
	   printPlayer(turn);
	   }
	   f=0;
	   p=askPoint(p,size);
	   cycleFirst=checkShoot(p,turn,opp);
	   if(cycleFirst!=99)
	   cycleSecond=0;  
	   else{
	   waitS(1);
	   clearTerminal();
	   f=1;
	   }
	 }
  clearTerminal();
  if(cycleFirst==0)
  break;
  if(turn==p2){
  turn=p1;
  opp=p2;
  }
  else{ 
  turn=p2;
  opp=p1;
   }
    }
    }


/*-------------------------check ------------------------------*/
int checkWin(Player* p1){
	
	if(p1->nhit==TOTALPOINTS){
	clearTerminal();
	winMeme();
	inicGame(p1->name,1);
    return 1;
    }
    else 
    return 0;
	}

int checkShoot(Point* p, Player* p1,Player* p2){
	 
	 if(search(p2->map,p)=='#'||search(p2->map,p)=='H' ){
     printf(ANSI_COLOR_RED"Didn't hit the ship\n"ANSI_COLOR_RESET);
     waitS(1);
	 insertPoint(p1->his,p,'0');  	 
     return 1;
     }
	 else{
	 int v =  search(p2->map,p) - '0';
	 printShootShip(v,p1->map->ship,p1); 
	 insertPoint(p1->his,p,'H');
	 insertPoint(p2->map,p,'H');                   	
	 p1->nhit++;
	 if(checkWin(p1)==1)
	 return 0;
	 else
	 return 99;
     }
  } 
  
 

int checkPoint(Point* p,int size){
	
	if(p->x>size || p->y>size ||p->x<=0 || p->y<=0 ){ 
	printf(ANSI_COLOR_RED"Coordinates goes beyond the battlefield\n\n"ANSI_COLOR_RESET);
	return 0;
	}
	return 1;
	} 


/*-------------------------Clear board the game ------------------------------*/

void clearGame(Player* p1,Player* p2){
	
	deleteAll(p1->map);
	deleteAll(p2->map);
	deleteAll(p1->his);
	deleteAll(p2->his);
  }

/*-------------------Define Board--------------------------------------------*/


int defineBattlefieldSize() {
   
   int size,i=1;
   while (i){
   size = defineSize();
   clearTerminal();
   if(minBattlefieldSize(size)==1)
   i=0;
   }
  
  return size;
}

int minBattlefieldSize(int size){
	
	if(size>=8)
	return 1;
	return 0;
	}


int defineSize()
{ 
  int n;
  printf(ANSI_COLOR_RED"Please define de size of the board\n"ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN"Must be greater than 7\n"ANSI_COLOR_RESET);
  scanf("%d", &n);
  getchar(); 
  return n;
}

/*----------------------Ask----------------------------------------*/


Point* askPoint(Point* p,int size){
	int i=1;
	while(i){
	printf(ANSI_COLOR_GRAY"Coordinates of your shoot:\n\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GRAY"x:"ANSI_COLOR_RESET);
	p->x=inputCheck();
	printf(ANSI_COLOR_GRAY"\ny:"ANSI_COLOR_RESET);
	p->y=inputCheck();
	printf("\n");
    if(checkPoint(p,size)!=0)
    i=0;
    }
	return p;
	}


void askForMap(Map* map)
{ 
     printf(ANSI_COLOR_GREEN"If you want to insert Manual press y, if you want Random press any key\n"ANSI_COLOR_RESET);
     char ch = getchar();
     flush_in();
     //getchar();
     
  
     if( ch=='y' ){
	  insertManual(map);
      }
     else{
	  insertRandom(map);
      }

}

/*-------------------------Restart game------------------------------*/
void restartGame(Player* p1,Player* p2){
    
    printf(ANSI_COLOR_GREEN "Player: %s\n"ANSI_COLOR_RESET,p1->name);
    p1->map->ship = initiateShip();
    for(int i=0;i<5;i++)
    p1->countPoints[i] =0;
    askForMap(p1->map);
    printInfo(p1->map);
    printPlayer(p1);
    p1->nhit=0;
    waitS(2);
    
    printf(ANSI_COLOR_GREEN"Player: %s\n"ANSI_COLOR_RESET,p2->name);
    p2->map->ship = initiateShip();
    for(int i=0;i<5;i++)
    p2->countPoints[i] =0;
    askForMap(p2->map);
    printInfo(p2->map);
    printPlayer(p2);
    p2->nhit=0;
    waitS(2);
   }
 
