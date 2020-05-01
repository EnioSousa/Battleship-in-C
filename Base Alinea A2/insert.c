#include "insert.h"
#include "search.h"
#include "interface.h"
#include "errorMessage.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

/*----------------------Insert Manual-------------------------*/

void insertManual(Map *m)
{
  int id, x, y;
  int checkId;
  int checkDir;
  char dir;
  Point p;

  if (m->ship == NULL)
    errorMessageMap("insertManual");

  while (someShipLeft(m->ship))
  {
    checkId = 1, checkDir = 1;
    clearTerminal();
    printf(ANSI_COLOR_YELLOW "Manual\n\n" ANSI_COLOR_RESET);
    informationShipRemaining(m->ship);
    printMapShip(m);
    printf(ANSI_COLOR_GREEN "Ship identification\n");
    while (checkId)
    {
      id = inputCheck();
      if (id >= 0 && id < 5)
      {
        if (m->ship[id].left != 0)
          checkId = 0;
        else
          printf("There are no more ships \n");
      }
      else
        printf("invalid id\n");
    }
    printf("X coordinate\n");
    x = inputCheck();
    printf("Y coordinate\n");
    y = inputCheck();
    if (id == 4)
      dir = 'n';
    else
    {
      printf("The direction of the ship\n");
      directionHelpPrint();
      while (checkDir)
      {
        dir = inputCheckChar();
        if (dir == 'n' || dir == 'e' || dir == 'w' || dir == 's')
          checkDir = 0;
        else
          printf("invalid direction\n" ANSI_COLOR_RESET);
      }
    }
    p.x = x;
    p.y = y;
    if (placeIsPossible(m, &m->ship[id], &p, dir))
    {
      insertShip(m, &m->ship[id], &p, dir);
    }
    else
    {
      printf("\nCannot place the ship\n");
      waitS(0);
    }
  }
}

/*----------------------Insert Random-----------------------*/
void insertRandom(Map *m)
{
  Point p;
  char dir;

  if (m->ship == NULL)
    errorMessageMap("insertRandom");

  for (int id = nextShip(m->ship); id != -1; id = nextShip(m->ship))
  {
    randomDir(&dir);

    findSomePlace(m, &m->ship[id], &p, &dir);

    insertShip(m, &m->ship[id], &p, dir);
  }
}

void findSomePlace(Map *m, Ship *ship, Point *p, char *dir)
{
  for (randomPoint(m, p); !findSomeDir(m, ship, p, dir); movePointLeft(m, p))
    ;
}

int findSomeDir(Map *m, Ship *ship, Point *p, char *dir)
{
  int i;

  for (i = 0; i < 4 && !placeIsPossible(m, ship, p, *dir); rotateDir(dir), i++)
    ;

  return i < 4 ? 1 : 0;
}

/*----------------------Insert Ship/Point-----------------------*/
void insertShip(Map *m, Ship *ship, Point *ref, char dir)
{
  Point p;

  for (int i = 0; i < ship->size; i++)
  {
    movePointInDir(ref, &ship->vec[i], &p, dir);

    insertPoint(m, &p, ship);
  }

  ship->active++;
  ship->left--;
}

void insertPoint(Map *map, Point *p, Ship *ship)
{
  if (!inBound(map, p))
    errorMessageOut("insertPoint", p);

  map->board[p->y - 1][p->x - 1].ship = ship;
  map->board[p->y - 1][p->x - 1].bit = '1';
  map->nPoint++;
}

int shoot(Map *map1, Map *map2, Point *p)
{
  int x = p->x - 1, y = p->y - 1;

  if (map2->board[y][x].bit != '1')
  {
    map1->board[y][x].shot = '1';

    if (map2->board[y][x].bit != '2')
      map2->board[y][x].bit = '3';

    return 0;
  }

  else
  {
    Ship *ship = search(map2, p);

    map1->board[y][x].shot = '2';
    map2->board[y][x].bit = '2';

    if (sunk(map2, p))
      ship->active--;

    return 1;
  }
}

int sunk(Map *map, Point *p)
{
  Point vec, p1;
  vec.x = 1;
  vec.y = 0;

  int cond;

  char saveBit = map->board[p->y - 1][p->x - 1].bit;
  map->board[p->y - 1][p->x - 1].bit = '4';

  movePointInDir(p, &vec, &p1, 'e');
  cond = testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 'n');
  cond = cond && testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 'w');
  cond = cond && testCondition(map, &p1);

  movePointInDir(p, &vec, &p1, 's');
  cond = cond && testCondition(map, &p1);

  map->board[p->y - 1][p->x - 1].bit = saveBit;

  return cond;
}

int testCondition(Map *map, Point *p)
{
  if (!inBound(map, p))
    return 1;

  int testBit = map->board[p->y - 1][p->x - 1].bit;

  return testBit == '0' || testBit == '3' || testBit == '4' ? 1 : (testBit == '1' ? 0 : sunk(map, p));
}

/*----------------------------Check-------------------------------*/
int placeIsPossible(Map *m, Ship *ship, Point *p, char dir)
{
  return inBound(m, p) &&
                 shipAvaliable(ship) &&
                 confAvaliable(m, ship, p, dir)
             ? 1
             : 0;
}

int confAvaliable(Map *m, Ship *ship, Point *ref, char dir)
{
  Point p;

  if (!inBound(m, ref))
    errorMessageOut("conAvaliable", ref);

  for (int i = 0; i < ship->size; i++)
  {
    movePointInDir(ref, &ship->vec[i], &p, dir);

    if (!inBound(m, &p))
      return 0;

    else if (search(m, &p) != NULL)
      return 0;

    else if (!voidAroundPoint(m, &p))
      return 0;
  }

  return 1;
}

int voidAroundPoint(Map *m, Point *p)
{
  Point temp;
  temp.x = p->x;
  temp.y = p->y;

  if (!inBound(m, p))
    errorMessageOut("voidAroundPoint", p);

  for (int i = -1; i <= 1; i++)
    if (i)
    {
      temp.x = p->x + i;
      temp.y = p->y;

      if (inBound(m, &temp) && search(m, &temp) != NULL)
        return 0;

      temp.x = p->x;
      temp.y = p->y + i;

      if (inBound(m, &temp) && search(m, &temp) != NULL)
        return 0;
    }

  return 1;
}
/*---------------------Generate next/random-------------------------*/
void randomDir(char *dir)
{
  switch (rand() % 4)
  {
  case 0:
    *dir = 'e';
    break;

  case 1:
    *dir = 'n';
    break;

  case 2:
    *dir = 'w';
    break;

  default:
    *dir = 's';
    break;
  }
}

void rotateDir(char *dir)
{
  switch (*dir)
  {
  case 'e':
    *dir = 'n';
    break;
  case 'n':
    *dir = 'w';
    break;
  case 'w':
    *dir = 's';
    break;

  default:
    *dir = 'e';
    break;
  }
}

void randomPoint(Map *m, Point *p)
{
  int n = rand() % (m->mapSize * m->mapSize);

  p->x = n / m->mapSize + 1;
  p->y = n % m->mapSize + 1;
}

/*--------------------------Move Point------------------------------*/
void movePointLeft(Map *m, Point *p)
{
  if (!inBound(m, p))
    errorMessageOut("movePointLeft", p);

  p->x++;

  if (p->x > m->mapSize)
  {
    p->y++;
    p->x = 1;
  }

  if (p->y > m->mapSize)
    p->y = 1;
}

void movePointInDir(Point *ref, Point *vec, Point *p, char dir)
{
  switch (dir)
  {
  case 'e':
    p->x = ref->x + vec->x;
    p->y = ref->y + vec->y;
    break;

  case 'w':
    p->x = ref->x - vec->x;
    p->y = ref->y - vec->y;
    break;

  case 'n':
    p->x = ref->x + vec->y;
    p->y = ref->y + vec->x;
    break;

  case 's':
    p->x = ref->x - vec->y;
    p->y = ref->y - vec->x;
    break;

  default:
    fprintf(stderr, "Error on movePointInDir %c unknown direction\n", dir);
    exit(EXIT_FAILURE);
  }
}
