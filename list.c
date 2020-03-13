#include "list.h"


list *initiateList()
{
  list *l = (list*)malloc(sizeof(list));

  if ( l==NULL )
    {
      printf("Error on initiateList\n");
      exit(EXIT_FAILURE);
    }

  l->first = (node*)malloc(sizeof(node));
  l->last = (node*)malloc(sizeof(node));

  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

node *newNode_(obj *a)
{
  node *n = (node*)malloc(sizeof(node));

  if ( n==NULL )
    {
      printf("Error on newNode\n");
      exit(EXIT_FAILURE);
    }
  
  n->prev = NULL;
  n->next = NULL;

  n->objeto =  a; 

  return n;
}

void insertFirst(list *l, node *n)
{
  n->prev = l->first;
  n->next = l->first->next;

  l->first->next->prev = n;
  l->first->next = n;

  l->size++;
}

void push(list *l, node *n) { insertFirst(l, n); }


void insertLast(list *l, node *n)
{
  n->next = l->last;
  n->prev = l->last->prev;

  l->last->prev->next = n;
  l->last->prev = n;

  l->size++;  
}

void enqueue(list *l, node *n) { insertLast(l, n); }


node *removeFirst(list *l)
{
  if ( !l->size )
    return NULL;

  node *temp = l->first->next;

  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  return temp;  
}

node *pop(list *l) { return removeFirst(l); }

node *dequeue(list *l) { return removeFirst(l); }


node *removeLast(list *l)
{
  if ( !l->size )
    return NULL;

  node *temp = l->last->prev;

  temp->prev->next = l->last;
  l->last->prev = temp->prev;

  l->size--;

  return temp;
}


int listSize(list *l) { return l->size; };


node *getFirst(list *l)
{
  if ( !l->size )
    return NULL;

  return l->first->next;
}

node *top(list *l) { return getFirst(l); }


node *getLast(list *l)
{
  if ( !l->size )
    return NULL;

  return l->last->prev;
}
