#include "listObj.h"

List *newObjectList()
{
  List *l = (List*)malloc(sizeof(List));

  if ( l==NULL )
    errorMessageMem("initiateList");

  l->size = 0;
  
  l->first = newObjectNode(NULL);
  l->last = newObjectNode(NULL);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

Lnode *newObjectNode(Object *obj)
{
  Lnode *n = (Lnode*)malloc(sizeof(Lnode));

  if ( n==NULL )
    errorMessageMem("newObjectNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->obj =  obj;

  return n;
}

void insertObjectFirst(List *l, Object *obj)
{
  Lnode *temp = newObjectNode(obj);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void pushObject(List *l, Object *obj) { insertObjectFirst(l, obj); }


void insertObjectLast(List *l, Object *obj)
{
  Lnode *temp = newObjectNode(obj);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueueObject(List *l, Object *obj) { insertObjectLast(l, obj); }


Object *removeFirstObject(List *l)
{
  if ( !l->size )
    return NULL;

  Lnode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageMem("removeFirst");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  Object *obj = temp->obj;
  
  free(temp);

  return obj;
}

Object *popObject(List *l) { return removeFirstObject(l); }

Object *dequeueObject(List *l) { return removeFirstObject(l); }

int objectListSize(List *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("objectListSize");
  
  return l->size;
};

void printObjectList(List *l)
{
  int i=0;
  
  for( Lnode *cur = l->first->next; cur!=l->last; cur=cur->next, i++ )
    {
      printf("Index = %d\n", i);
      
      printObject(cur->obj);
    }
  
  putchar('\n');
}
