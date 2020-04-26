#ifndef GAME
#define GAME
#define TOTALPOINTS 27
#include "player.h"
#include "point.h"



/*-------------------Game----------------------------------------*/
 void game(Player *p1, Player *p2,int size);
/*-------------------Define Board---------------------------------------*/
int defineBattlefieldSize();
int defineSize();
int minBattlefieldSize(int size);
/*-------------------Check----------------------------------------*/
int checkShoot(Point* p, Player* p1,Player* p2);
int checkWin(Player* p1);
int checkPoint(Point* p,int size);
/*--------------------Ask-------------------------------------------*/
Point* askPoint(Point* p,int size);
void askForMap(Map* map);
/*-------------------Clear board game -----------------------*/
void clearGame(Player* p1,Player* p2);
/*-------------------------Restart game------------------------------*/
void restartGame(Player* p1,Player* p2);
#endif 
