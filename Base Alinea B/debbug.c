#include "debbug.h"

void printMapDebbug(Map *root)
{
  int iLim = root->mapSize * root->mapSize;

  Point p;
  p.x = root->tl->x;
  p.y = root->tl->y;

  Node *node;
  
  for( int i=1; i<=iLim; i++ )
    {
      node = searchNode(root, &p);

      if ( node!=NULL)
	printf("%c ", node->id);

      else
	printf("%c ", WATER);
      
      if ( i%root->mapSize==0 )
	putchar('\n');

      movePointLeft(root, &p);
    }

  printf("\n\n");
}

void printAllDepthDebbug(Map *root)
{
  List *l = newObjectList();
  enqueueObject(l,newObject(root, 0, 0));

  do
    {
      Object *cur = dequeueObject(l);
      
      printObject(cur);

      if ( cur->map->nw!=NULL )
	{
	  enqueueObject(l, newObject(cur->map->nw, cur->level+1, 1));
	  enqueueObject(l, newObject(cur->map->ne, cur->level+1, 2));
	  enqueueObject(l, newObject(cur->map->sw, cur->level+1, 3));
	  enqueueObject(l, newObject(cur->map->se, cur->level+1, 4));
	}	  
      
    }while ( objectListSize(l)>0 );
}
