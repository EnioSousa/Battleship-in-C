#ifndef INSERT
#define INSERT

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "ship.h"
#include "point.h"
#include "search.h"
#include "interface.h"
#include "errorMessage.h"

/*----------------------Insert Manual-------------------------*/
void insertManual(Map *m);
  
/*----------------------Insert Random-----------------------*/
void insertRandom(Map *m);
void findSomePlace(Map *m, Ship *ship, Point *p, char *dir);
int findSomeDir(Map *m, Ship *ship, Point *p, char *dir);
  
/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *m, Ship *ship, Point *ref, char dir);
void insertPoint(Map *m, Point *p, Ship *ship);
int shot(Map *map1, Map *map2, Point *p);
int sunk(Map *map, Point *p);
int testCondition(Map *m, Point *p);

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *m, Ship *ship, Point *p, char dir);
int confAvaliable(Map *m, Ship *ship, Point *ref, char dir);
int voidAroundPoint(Map *m, Point *p);

/*---------------------Generate next/random---------------------*/
void randomDir(char *);
void rotateDir(char *);
void randomPoint(Map *, Point *);

/*-------------------------Move Point----------------------------*/
void movePointLeft(Map *, Point *);
void movePointInDir(Point *old, Point *vector, Point *new, char dir);

#endif
