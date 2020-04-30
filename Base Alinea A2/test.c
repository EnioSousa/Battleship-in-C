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
  srand(time(NULL));
  
  Map *map1 = newMap(20);
  Map *map2 = newMap(40);

  insertRandom(map1);
  insertRandom(map2);

  printAll(map1);
  printAll(map2);
  
  return 0;
}
