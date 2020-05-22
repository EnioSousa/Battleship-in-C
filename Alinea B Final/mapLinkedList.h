#ifndef MAPLINKEDLIST
#define MAPLINKEDLIST

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "errorMessage.h"

typedef struct MNode
{
  Map *map;
  
  struct MNode *prev, *next;
  
}MNode;

typedef struct MList
{
  int size;

  struct MNode *first, *last;
  
}MList;

MList *newMapList();
MNode *newMapNode(Map *map);

void insertMapFirst(MList *l, Map *map);
void pushMap(MList *l, Map *map);

void insertMapLast(MList *l, Map *map);
void enqueueMap(MList *l, Map *map);

Map *removeFirstMap(MList *l);
Map *popMap(MList *l);
Map *dequeueMap(MList *l);

int mapListSize(MList *l);

void freeMapList(MList *l);

#endif
