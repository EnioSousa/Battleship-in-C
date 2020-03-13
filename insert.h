#ifndef INSERT
#define INSERT
#include "QuadTree.h"
#include "ship.h"
#include "search.h"
#include "interface.h"
#include <time.h>

void insertManual(Quad *root, Ship *ship);
int noMoreShip(Ship *ship);
void insertRandom(Quad *root, Ship *ship);
int checkPossible(Quad *tree, Ship *ship, Point *p, char *dir);
int nextShip(Ship *ship);
void randomPoint(Point *p);
void randomDir(char *dir);
void translatePoint(Point *p);
void rotateDir(char *dir);
void insertShip(Quad *root, Ship *ship, Point ref, char dir);
void insertPoint(Quad *root, Point p, int id);
void movePoint(Point *ref, Point *vec, Point *p, char dir);
void incUp(Quad *level);
int possible(Quad *root, Ship *ship, Point p, char dir);
int shipAvaliable(Ship *ship);
int insideOfMap(Point p);
int confAvaliable(Quad *root, Ship *ship, Point ref, char dir);
int voidAround(Quad *tree, Point p);
#endif
