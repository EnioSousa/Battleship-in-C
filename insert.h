#ifndef INSERT
#define INSERT
#include "map.h"
#include "ship.h"
#include <time.h>



/*----------------------Insert Manual-------------------------*/
void insertManual(Map *, Ship *);

/*----------------------Insert Randoml-----------------------*/
void insertRandom(Map *, Ship*);
void findSomePlace(Map *, Ship *, Point *, char *);
int findSomeDir(Map *, Ship *, Point *, char *);

/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *, Ship *, Point *, char );
void insertPoint(Map *, Point *, int );
void insertHit (Map *m, Point *p, char id);

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *, Ship *, Point *, char );
int insideOfMap(Map *, Point *);
int shipAvaliable(Ship *);
int someShipLeft(Ship *);
int confAvaliable(Map *, Ship *, Point *, char );
int voidAroundPoint(Map *, Point *);


/*---------------------Generate next/random-------------------------*/
void randomDir(char *);
void rotateDir(char *);
void randomPoint(Map *, Point *);
int nextShip(Ship *);

/*----------------------Move Point-------------------------*/
void movePointLeft(Map *, Point *);
void movePointInDir(Point *, Point *, Point *, char );

/*---------------------------Error message2------------------------*/
void errorMessage2(char *, Point *);
  
#endif


