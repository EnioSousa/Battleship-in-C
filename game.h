#ifndef GAME
#define GAME
#include "interface.h"
#include "insert.h"
#include "ship.h"
#include "map.h"
#include <time.h>
#define maxNameSize 60
#define Npoints  30


typedef struct 
{
  char *name;
  Map *map, *his;
  int nhit;
  Ship *ship;
  
}Player;


Player *initiatePlayer(int);
int defineSize();
char *getName();
int minBattlefieldSize(int size);
void askForMap(char *, Map *, Ship *,int i);
void game(Player *p1, Player *p2,int size);
Point* askPoint(Point* p,int size);
int checkWin(Player* p1);
void clearGame(Player* p1,Player* p2);
int checkShoot(Point* p, Player* p1,Player* p2);
int checkPoint(Point* p, int size);
int defineBattlefieldSize();
int askContinue();
void restartGame(Player* p1,Player* p2);
void clearMemory(Player* p1,int size);
void clearMemoryMap(Map* p1,int size);
void eat_Extra(void);
void menuStar();
void printPlayerInfo(Player* p,Player* p1);
void printPlayer(Player* p);

#endif
