#include "simpleQueue.h"

Queue *newQueue()
{
  Queue *temp = (Queue*)malloc(sizeof(Queue));

  temp->first=NULL;
  temp->last=NULL;
  temp->size=0;

  return temp;
}


QNode *newQNode(Quad *level)
{
  QNode *no = (QNode*)malloc(sizeof(QNode));

  if ( no==NULL )
    {
      fprintf(stderr,"Error newQNode (lack of space)\n");
      exit(EXIT_FAILURE);
    }
  
  no->cur = level;
  no->next = NULL;

  return no;
}


void enqueue(Queue *q, Quad *level)
{
  QNode *no = newQNode(level);
  
  if ( q->size==0 )
    {
      q->first = no;
      q->last = no;
    }

  else
    {
      q->last->next = no;
      q->last = no;
    }
  
  q->size++;
}


Quad *dequeue(Queue *q)
{
  if ( q->size==0 )
    return NULL;

  QNode *t1 = q->first;
  Quad *t2 = t1->cur;
  
  q->first = q->first->next;

  q->size--;

  free(t1);
  
  return t2;;
}


int isEmpty(Queue* q) { return q->size==0 ? 1: 0; };
