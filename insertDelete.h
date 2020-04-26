#ifndef INSERTDELETE
#define INSERTDELETE

#include "map.h"
#include "ship.h"
#include "point.h"

/*-----------------------Insert Manual--------------------------*/
void insertManual(Map *);
/*-----------------------Insert Randoml-------------------------*/
void insertRandom(Map *);
void findSomePlace(Map *, Ship *, Point *, char *);
int findSomeDir(Map *, Ship *, Point *, char *);
/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *, Ship *, Point *, char );
void insertPoint(Map *, Point *, char);
/*---------------------------delete------------------------------*/
void deletePoint(Map *, Point *);
void deleteAll(Map *);
/*----------------------------Check-----------------------------*/
int placeIsPossible(Map *, Ship *, Point *, char );
int insideOfMap(Map *, Point *);
int shipAvaliable(Ship *);
int someShipLeft(Map *);
int confAvaliable(Map *, Ship *, Point *, char );
int voidAroundPoint(Map *, Point *);
/*---------------------Generate next/random---------------------*/
void randomDir(char *);
void rotateDir(char *);
void randomPoint(Map *, Point *);
int nextShip(Map *);
/*-------------------------Move Point----------------------------*/
void movePointLeft(Map *, Point *);
void movePointInDir(Point *old, Point *vector, Point *new, char dir);
#endif


