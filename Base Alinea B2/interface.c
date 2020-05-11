#include "interface.h"

void printMap(Map *root)
{
  printf("Your Ships placement\n\n");
  printf(ANSI_COLOR_BLUE "0->empty " ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "1->piece not hitted " ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "2->piece hitted " ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "3->enemy miss shot\n\n" ANSI_COLOR_RESET);

  int iLim = root->mapSize * root->mapSize;
  
  Point p;
  p.x = root->tl->x;
  p.y = root->tl->y;

  char *cur;
  
  for( int i=1; i<=iLim; i++ )
    {
      cur = searchBit(root, &p);

      if ( cur==NULL || *cur == '0')
	printf(ANSI_COLOR_BLUE "0 " ANSI_COLOR_RESET);

      else if ( *cur == '1' )
	printf(ANSI_COLOR_GREEN "1 " ANSI_COLOR_RESET);

      else if ( *cur == '2' )
	printf(ANSI_COLOR_RED "2 " ANSI_COLOR_RESET);

      else
	printf(ANSI_COLOR_YELLOW "3 " ANSI_COLOR_RESET); 

      if ( i%root->mapSize==0 )
	putchar('\n');
      
      movePointLeft(root, &p);
    }

  printf("\n\n");  
}

void printHistory(Map *root)
{
  printf("Your History of shots\n\n");
  printf(ANSI_COLOR_BLUE "0->no shot " ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "1->failed shot " ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "2->hit\n\n" ANSI_COLOR_RESET);
  
  int iLim = root->mapSize * root->mapSize;
  
  Point p;
  p.x = root->tl->x;
  p.y = root->tl->y;

  char *cur;
  
  for( int i=1; i<=iLim; i++ )
    {
      cur = searchShoot(root, &p);

      if ( cur==NULL || *cur == '0' )
	printf(ANSI_COLOR_BLUE "0 " ANSI_COLOR_RESET);

      else if ( *cur=='1' )
	printf(ANSI_COLOR_RED "1 " ANSI_COLOR_RESET);

      else
	printf(ANSI_COLOR_YELLOW "2 " ANSI_COLOR_RESET);

      if ( i%root->mapSize==0 )
	putchar('\n');
      
      movePointLeft(root, &p);
    }

  printf("\n\n");  
}

void printMapByLevel(Map *root)
{
  MList *stack = newMapList();

  pushMap(stack, root);

  while ( stack->size > 0 )
    {
      Map *temp = popMap(stack);

      if ( temp==NULL )
        continue;

      printf("Limites do mapa\n");
      printPoint(temp->tl);
      printPoint(temp->br);

      printf("Numero de pontos = %d\n\n", temp->nP);

      if ( temp->nw==NULL )
	for( int i=0; i<temp->nP; i++ )
	  {
	    printPoint(temp->vec[i].pos);
	    printCell(temp->vec[i].cell);
	  }

      else
	{
	  if ( temp->vec != NULL )
	    {
	      fprintf(stderr, "Livertação de memoria mal feita\n");
	      exit(EXIT_FAILURE);
	    }
	  
	  printf("None in this level\n");
	}

      pushMap(stack, temp->nw);
      pushMap(stack, temp->ne);
      pushMap(stack, temp->sw);
      pushMap(stack, temp->se);

      printf("\n\n");
    }
  
  printf("\n\n");
}

void printCell(Cell *cell)
{
  printf("Cell info\n");
  
  if ( cell==NULL )
    {
      printf("There is no cell\n");
      return;
    }
  
  if ( cell->ship==NULL )
    printf("Contains no ship ");

  else
    printf("Cointans a ship\n");

  printf("bit=%c shoot=%c\n", cell->bit, cell->shoot);

  putchar('\n');
}

void informationShipRemaining(Ship *s)
{
  printf("Number of ships remaining:\n");
  
  if (s[0].left != 0)
    printf(ANSI_COLOR_YELLOW "Id:0 -->Carrier: %d \n", s[0].left);
  
  if (s[1].left != 0)
    printf("Id:1 -->Battleship: %d \n", s[1].left);
  
  if (s[2].left != 0)
    printf("Id:2 -->Cruiser: %d \n", s[2].left);
  
  if (s[3].left != 0)
    printf("Id:3 -->Submarine: %d \n", s[3].left);
  
  if (s[4].left != 0)
    printf("Id:4 -->Destroyer: %d \n" ANSI_COLOR_RESET, s[4].left);
  
  printf("\n");
}

void printAllShip(Ship *arr)
{
  printf(ANSI_COLOR_RED "Information\n\n" ANSI_COLOR_RESET);
  
  for (int i = 0; i < NumDifShip; i++)
    printShip(&arr[i]);
}


void printShip(Ship *ship)
{
  printShipInfo(ship);

  printShipForm(ship);

  putchar('\n');  
}

void printAllShipInfo(Ship *ship)
{
  for (int i = 0; i < NumDifShip; i++)
    printShipInfo(&ship[i]);
}

void printShipInfo(Ship *ship)
{
  printf(ANSI_COLOR_RED "Name: %s id: %d " ANSI_COLOR_RESET, ship->name, ship->id);
  printf(ANSI_COLOR_GREEN "Size: %d ", ship->size);
  printf("Number: %d \n" ANSI_COLOR_RESET, ship->num);
}

void printShipForm(Ship *ship)
{
  int n = 5;

  char temp[n][n];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      temp[i][j] = '#';

  for (int i = 0; i < ship->size; i++)
    temp[(n / 2) + ship->vec[i].y][ship->vec[i].x] = '0' + ship->id;

  for (int i = n - 1; i >= 0; putchar('\n'), i--)
    for (int j = 0; j < n; j++)
      if (temp[i][j] == '#')
        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_BLUE, temp[i][j]);
  
      else
        printf(ANSI_COLOR_YELLOW "1" ANSI_COLOR_BLUE);
}
