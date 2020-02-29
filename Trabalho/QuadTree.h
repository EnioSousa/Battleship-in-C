#ifndef QUADTREE_h
#define QUADTREE_h


typedef enum { false, true } bool;

typedef struct Point 
{ 
  int x; 
  int y; 
} 
  Point;


typedef struct Node 
{ 
  Point pos; 
  char c; 
}
  Node;


typedef struct Quad 
{ 
  //limits 
  Point topLeft; 
  Point botRight; 
  
  // Contains details of node 
  Node *n;

  int nP;


  union {
  // Children of this tree 
  struct Quad* topLeftTree; 
  struct Quad* topRightTree; 
  struct Quad* botLeftTree; 
  struct Quad* botRightTree;
  }
    sons;
  
  struct Quad* pai;
}
  Quad;


Point* newPoint(int x,int y);
Node* newNode(Point pos, char v);
Quad* newQuad(Point a,Point b);
bool checker(Point p, Quad* ab ); 

#endif
