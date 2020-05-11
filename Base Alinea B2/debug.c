#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ship.h"
#include "map.h"
#include "insert.h"
#include "delete.h"
#include "interface.h"

int main()
{
  srand(time(NULL));
  
  Map *map1 = newMap(8, initiateShip(10));
  Map *map2 = newMap(8, initiateShip(10));
  
  insertRandom(map1);
  insertRandom(map2);

  Point p;
  randomPoint(map2, &p);
  
  printMap(map1);
  printMap(map2);
  
  while( someActiveShip(map2->ship) )
    {
      movePointLeft(map2, &p);

      shootOponent(map1, map2, &p);
    }

  for( int i=0; i<64; i++ )
    {
      deletePoint(map1, &p);
      deletePoint(map2, &p);

      movePointLeft(map1, &p);
      
      printMap(map1);
      printHistory(map1);
      printf(">>>>>>>>>>>>><<<<<<<<<<<<<<<\n");
      printMap(map2);
      printHistory(map2);      
    }

  printMapByLevel(map1);
  printMapByLevel(map2);
  
  return 0;
}
