#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "insertDelete.h"
#include "point.h"
#include "ship.h"
#include "map.h"

#define size 10

int main()
{
  Map *m = newMap(size, initiateShip());

  printAll(m);

  insertRandom(m);
  printAll(m);

  printAllShip(m->ship);

  for( int i=0; i<100; i++ )
    {
      Point p; p.x = i/10 + 1; p.y = i%10 + 1;
      deletePoint(m, &p);
    }
  
  printAll(m);

  printAllShip(m->ship);
  return 0;
}
