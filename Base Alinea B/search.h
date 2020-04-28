#ifndef SEARCH
#define SEARCH

#include "point.h"
#include "map.h"
#include "error.h"

char searchCharacter(Map *root, Point *p);
Point *searchPoint(Map *root, Point *p);
Node *searchNode(Map *root, Point *p);
Map *searchDepth(Map *level, Point *p);
Node *searchLevel(Map *level, Point *p);
int outOfBounds(Map *level, Point *p);

#endif
