#ifndef SIMPLE_QUEUE
#define SIMPLE_QUEUE
#include "QuadTree.h"

typedef struct QNode
{
  struct QNode *next;
  Quad *cur;
  
}QNode;

typedef struct Queue
{
  QNode *first,*last;
  int size;
  
}Queue;


Queue *newQueue();

QNode *newQNode(Quad *level);

void enqueue(Queue *q, Quad *tree);

Quad *dequeue(Queue *q);

int isEmpty(Queue* q);

#endif
