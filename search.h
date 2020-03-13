#ifndef SEARCH
#define SEARCH
#include "QuadTree.h"


//
Quad *searchDepth(Quad *tree, Point p);
//
Node *searchLevel(Quad *level, Point p);
//
Node *simpleSearch(Quad *root, Point p);

Node *search_A(Quad *root,Point p);




#endif
