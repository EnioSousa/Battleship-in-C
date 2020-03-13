#ifndef LISTA_H_
#define LISTA_H_
#include <stdio.h>
#include <stdlib.h>
#include "QuadTree.h"

typedef struct aobj
{
   Quad*  current ;
   struct aobj *pai;
  
}obj;


typedef struct anode
{
  struct aobj *objeto;

  struct anode *prev, *next;
  
}node;

typedef struct
{
  int size;

  struct anode *first, *last;
  
}list;

list *initiateList();
node *newNode_(obj *);
void insertFirst(list *, node *);
void push(list *, node *);
void insertLast(list *, node *);
void enqueue(list *, node *);
node *removeLast(list*);
node *removeFirst(list*);
node *pop(list*);
node *dequeue(list*);
int listSize(list*);
node *getFirst(list*);
node *top(list*);
node *getLast(list*);

#endif
