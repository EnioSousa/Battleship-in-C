#include "search.h"
#include "list.h"

Quad *searchDepth(Quad *tree, Point p)
{
  switch( whereToPut(*tree, p))
    {
    case 0:
      return tree;

    case 1:
      return searchDepth(tree->sw, p);

    case 2:
      return searchDepth(tree->se, p);

    case 3:
      return searchDepth(tree->nw, p);

    default:
      return searchDepth(tree->ne, p);
    }
  
}

//
Node *searchLevel(Quad *level, Point p)
{
  for( int i=0; i<level->nP; i++ )
    if ( level->vec[i].pos.x == p.x && level->vec[i].pos.y == p.y )
      return &level->vec[i];

  return NULL;
}

//
Node *simpleSearch(Quad *root, Point p)
{
  Quad *level = searchDepth(root,p);

  return searchLevel(level, p);
}



Node *search_A(Quad *root, Point p){
	
        
        list* open = initiateList();
        list* close = initiateList();
        list* path = initiateList();
        
 
 
}






