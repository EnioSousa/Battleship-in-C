#ifndef INTERFACE
#define INTERFACE

#include "map.h"
#include "point.h"

//used ANSI colors

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GRAY "\e[0;37m"
#define ANSI_COLOR_DARK_GRAY "\e[1;30m"
#define ANSI_COLOR_GREEN "\e[0;32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\e[0;33m"
#define ANSI_COLOR_BLUE "\e[0;34m"

/*-----------------------Clear terminal ---------------------------------*/
void clearTerminal();
/*------------------------Images------------------------------------------*/
void menuStar();
void winMeme();
void inicGame(char *str, int i);
/*-------------------------Wait------------------------------------------*/
void waitS(int i);
/*----------------------Information--------------------------------------*/
void directionHelpPrint();
/*---------------------------Ask------------------------------------------*/
int askContinue();
/*---------------------------Map------------------------------------------*/
void printAll(Map *);
void printInfo(Map *);
void printMapShip(Map *m);
void printMapHistory(Map *m);

#endif
