#ifndef LISTOBJ
#define LISTOBJ

#include "object.h"

typedef struct Lnode
{
  Object *obj;
  
  struct Lnode *prev, *next;
  
}Lnode;

typedef struct List
{
  int size;

  struct Lnode *first, *last;
  
}List;

List *newObjectList();
Lnode *newObjectNode(Object *obj);

void insertObjectFirst(List *l, Object *obj);
void pushObject(List *l, Object *obj);

void insertObjectLast(List *l, Object *obj);
void enqueueObject(List *l, Object *obj);

Object *removeFirstObject(List *l);
Object *popObject(List *l);
Object *dequeueObject(List *l);

int objectListSize(List *l);

void prinObjecttList(List *l);

#endif
