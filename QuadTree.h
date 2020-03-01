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
  
}Point;

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

  struct Quad *nw; // north west son
  struct Quad *ne; // north east son
  struct Quad *sw; // south west son
  struct Quad *se; // south east son

  struct Quad *father; // pai 
  
} Quad;


#endif
