#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "point.h"
#include "error.h"
#include "ship.h"
#include "map.h"
#include "insert.h"
#include "debbug.h"
#include "delete.h"

int main()
{
  srand(time(NULL));
  
  Map *m = newMap(8, initiateShip());

  insertManual(m);
  
  return 0;
}
