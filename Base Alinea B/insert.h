#ifndef INSERT
#define INSERT

#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "error.h"
#include "ship.h"
#include "map.h"
#include "search.h"
#include "debbug.h"

/*----------------------Insert Manual-------------------------*/
void insertManual(Map *m);

/*----------------------Insert Random-----------------------*/
void insertRandom(Map *m);
void findSomePlace(Map *m, Ship *ship, Point *p, char *dir);
int findSomeDir(Map *m, Ship *ship, Point *p, char *dir);

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *level, Ship *ship, Point *p, char dir);
int shipAvaliable(Ship *ship);
int someShipLeft(Ship *ship);
int confAvaliable(Map *m, Ship *ship, Point *ref, char dir);
int voidAroundPoint(Map *root, Point *p);

/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *root, Ship *ship, Point *ref, char dir);
void insertPoint(Map *root, Point *p, char id);
void insertPointInLevel(Map *level, Point *p, char id);
void incUp(Map *level);

/*---------------------Generate next/random-------------------------*/
void randomDir(char *dir);
void rotateDir(char *dir);
void randomPoint(Map *m, Point *p);
int nextShip(Ship *ship);
  
/*--------------------------Move Point------------------------------*/
void movePointLeft(Map *level, Point *p);
void movePointInDir(Point *ref, Point *vec, Point *p, char dir);
#endif
