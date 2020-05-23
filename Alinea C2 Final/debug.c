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

  Map *map1 = newMap(10, initiateShip(10));
  insertRandom(map1);

  Map *map2 = newMap(10, initiateShip(10));
  insertRandom(map2);

  display(map1);
  //display(map2);

  Point p;
  int cnd;

  while ( 1 )
    {
      display(map1);

      scanf("%d %d", &p.x, &p.y);

      cnd = shoot(map2, &p);

      updateHistory(map1, &p, cnd);

      display(map1);

      display(map2);

      scanf("%d %d", &p.x, &p.y);

      cnd = shoot(map1, &p);

      updateHistory(map2, &p, cnd);

      display(map2);
    }

  return 0;
}
