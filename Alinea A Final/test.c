#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "insert.h"
#include "point.h"
#include "ship.h"
#include "time.h"
#include "map.h"

#define size 10

int main()
{  
  Map *map1 = newMap(10);
  Map *map2 = newMap(10);

  insertRandom(map1);
  insertRandom(map2);

  freeMap(map1);
  freeMap(map2);

  printShipInfo(map1->ship);

  /* Point p; */

  /* printf("FUCK %d\n",  lost(map2)); */
  /* while ( !lost(map2) ) */
  /*   { */
  /*     printAll(map1); */
  /*     printAllShipInfo(map1->ship); */
  /*     printAll(map2); */
  /*     printAllShipInfo(map2->ship); */

  /*     scanf("%d %d", &p.x, &p.y); */
  /*     shot(map1, map2, &p); */
  /*   } */
  
  return 0;
}
