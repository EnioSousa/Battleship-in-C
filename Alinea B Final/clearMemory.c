#include "clearMemory.h"
#include <stdlib.h>
#include "ship.h"

void clearMemory(Player *p)
{
    free(p->name);
    freeMap(p->map);
    free(p);
}
