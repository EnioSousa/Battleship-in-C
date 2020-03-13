#ifndef INSERFACE
#define INTERFACE
#include "QuadTree.h"

void printNode(Node no);

void printLevel(Quad *level);

void printAllLevel(Quad *level, int n);

void initiateBiArr(char map[][mapSize+1]);

void transToMap(char map[][mapSize+1],Quad *level);

void printBiArray(char map[][mapSize+1]);

void printMap(Quad *root);

#endif
