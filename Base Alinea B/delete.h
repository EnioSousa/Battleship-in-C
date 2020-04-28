#ifndef DELETE
#define DELETE

#include <stdio.h>
#include <stdlib.h>

#include "insert.h"
#include "search.h"
#include "map.h"
#include "point.h"

/*----------------------------delete----------------------------------*/
void deletePoint(Map *root, Point *p);
void deletePointOnDepth(Map *level, Point *p);
void swap(Node *a, Node *b);
void compact(Map *level);
void downUp(Map *level, int n);
int possibleToFree(Map *level);
void freeSons(Map *father);
void copyBack(Map *father, Map *son);
  
/*----------------------------Replace---------------------------------*/
void replacePoint(Map *level, Point *p, char id);
void replacePointOnLevel(Map *level, Point *p, char id);

#endif
