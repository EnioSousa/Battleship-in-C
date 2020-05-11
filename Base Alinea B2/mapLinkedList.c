#include "mapLinkedList.h"

MList *newMapList()
{
  MList *l = (MList*)malloc(sizeof(MList));

  if ( l==NULL )
    errorMessageMem("initiateList");

  l->size = 0;
  
  l->first = newMapNode(NULL);
  l->last = newMapNode(NULL);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

MNode *newMapNode(Map *map)
{
  MNode *n = (MNode*)malloc(sizeof(MNode));

  if ( n==NULL )
    errorMessageMem("newMapNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->map =  map;

  return n;
}

void insertMapFirst(MList *l, Map *map)
{
  MNode *temp = newMapNode(map);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void pushMap(MList *l, Map *map) { insertMapFirst(l, map); }


void insertMapLast(MList *l, Map *map)
{
  MNode *temp = newMapNode(map);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueueMap(MList *l, Map *map) { insertMapLast(l, map); }


Map *removeFirstMap(MList *l)
{
  if ( !l->size )
    return NULL;

  MNode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageIllegalSize("removeFirstMap");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  Map *mapTemp = temp->map;

  free(temp);

  return mapTemp;
}

Map *popMap(MList *l) { return removeFirstMap(l); }

Map *dequeueMap(MList *l) { return removeFirstMap(l); }

int mapListSize(MList *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("mapListSize");
  
  return l->size;
};

void freeMapList(MList *l)
{
  while ( l->size>0 )
    freeMap(dequeueMap(l));
}
