#ifndef INTERFACE
#define INTERFACE
#include "map.h"
#include "ship.h"
#include "game.h"
#include <unistd.h>
//cores em ANSI utilizadas 
#define ANSI_COLOR_RED     	"\x1b[31m" 
#define ANSI_COLOR_GRAY    	"\e[0;37m"
#define ANSI_COLOR_DARK_GRAY 	"\e[1;30m"
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW "\e[0;33m"
#define ANSI_COLOR_BLUE "\e[0;34m"


void printAll(Map *);
void printInfo(Map *);
void printMap(Map *);
void printPoint(Point *);
void clearTerminal();
void printRepeat(int n, char ch);
void flush_in();
void printMaphis(Map *m);
void winMeme();
void finalGame(char* str);
void information();
void wait();
void waitLong();
void temporyPrint();
int  checkDir(char dir);
void printMap2(Map* map);
void printCarrier();
void printBattleship();
void printCruiser();
void printSubmarine();
void printDestroyer();
void printfActive(Map* map);
void informationShip(Ship* s);
#endif
