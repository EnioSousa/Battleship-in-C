#ifndef QUAD_HEADER
#define QUAD_HEADER
#define Lim 4
#define mapSize 10
#include <stdio.h>
#include <stdlib.h>

typedef struct Point 
{ 
  int x; 
  int y;
  }
 Point;

typedef struct Node 
{ 
  Point pos; 
  int id;
  
}Node;

typedef struct Quad 
{ 
  Point tl; // top left
  Point br; // bottom rigth
  
  Node *vec; // list/array of nodes
  int nP; // number of nodes

  struct Quad *father; // pai 
  
  //union {
  struct Quad *nw; // north west son
  struct Quad *ne; // north east son
  struct Quad *sw; // south west son
  struct Quad *se; // south east son
  //}children; 

} Quad;


Point *newPoint(int x, int y);

void newNode(Quad *tree, Point a, int id);

void addNode(Quad *level, Node *no);

Quad *newQuadZero(Point a, Point b);

Quad *initiateTree();

void newPartition(Quad *tree);

int possibleToDivide(Quad *tree);

void divideInFour(Quad *tree);

void copyAll(Quad *father);

int whereToPut(Quad level, Point p);

#endif
