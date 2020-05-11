#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "ship.h"
#include "map.h"
#include "search.h"
#include "insert.h"
#include "mapLinkedList.h"

//used ANSI colors

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GRAY "\e[0;37m"
#define ANSI_COLOR_DARK_GRAY "\e[1;30m"
#define ANSI_COLOR_GREEN "\e[0;32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\e[0;33m"
#define ANSI_COLOR_BLUE "\e[0;34m"

/* Imprime o mapa*/
void printMap(Map *root);

/* Imprime a historia de ataques*/
void printHistory(Map *root);

/* Imprime o mapa todo, nivel por nivel. Esta função so serve para fazer debug*/
void printMapByLevel(Map *root);

/* Imprime a informação relevante a celula.Função so serve para fazer debug*/
void printCell(Cell *cell);

/* Imprime a informação de quantos navios estão ativos para cada tipo de barco*/
void informationShipRemaining(Ship *arrShip);

/* Imprime a informação realtiva a cada tipo de barco como tamanho, active etc*/
void printAllShipInfo(Ship *arrShip);

/* Imprime a informação realativa a um tipo de navio*/
void printShipInfo(Ship *ship);

/* Imprime toda a informação e a forma de todos os tipos de barco*/
void printAllShip(Ship *arrShip);

/* Imprime A informação e a forma relativamente a um tipo de navio*/
void printShip(Ship *ship);

/* Imprime a forma do barco numa mapa 5x5*/
void printShipForm(Ship * ship);


#endif
