#include "interface.h"
#include <unistd.h>

void clearTerminal()
{

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN64) || defined(_WIN32)
  system("cls");
#endif
}

void menuStar()
{
  printf(ANSI_COLOR_RED "                                               	                                     \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "                     $                         	                                      \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "                        $$$      .oo..     'oooo'oooo'ooooooooo....                         \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "                         $       $$$$$$$                                                     \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "                     .ooooooo.   $$!!!!!                                                      \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "                   .'.........'. $$!!!!!      o$$oo.   ...oo,oooo,oooo'ooo''                 \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "      $          .o'  oooooo   '.$$!!!!!      $$!!!!!       'oo''oooo''                      \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "  ..o$ooo...    $                '!!''!.     $$!!!!!                                         \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "   $    ..  '''oo$$$$$$$$$$$$$.    '    'oo.  $$!!!!!       Version 1                            \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "   !.......      '''..$$ $$ $$$   ..        '.$$!!''!                                         \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "   !!$$$!!!!!!!!oooo......   '''  $$ $$ :o           'oo.                                      \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "   !!$$$!!!$$!$$!!!!!!!!!!oo.....     ' ''  o$$o .      ''oo..                              \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "   !!!$$!!!!!!!!!!!!!!!!!!!!!!!!!!!!ooooo..      'o  oo..    $   \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "    '!!$$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!oooooo..  ''   ,$  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "     '!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!oooo..$$  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "      !!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$'  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "      '$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!!!!!!!!!!!!!!!!!!,  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "  .....$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GRAY "                                                                              \n\n\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "      dMMMMb  .aMMMb  dMP dMP .aMMMb  dMP \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "     dMP dMP dMP dMP dMP dMP dMP dMP dMP  \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "    dMP dMP dMMMMMP dMP dMP dMMMMMP dMP   \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "   dMP dMP dMP dMP  YMvAP  dMP dMP dMP    \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "  dMP dMP dMP dMP    VP   dMP dMP dMMMMMP \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "                                          \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "      dMMMMb  .aMMMb dMMMMMMP dMMMMMMP dMP     dMMMMMP \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "     dMP dMP dMP dMP   dMP      dMP   dMP     dMP      \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "    dMMMMK  dMMMMMP   dMP      dMP   dMP     dMMMP     \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "   dMP.aMF dMP dMP   dMP      dMP   dMP     dMP        \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "  dMMMMP  dMP dMP   dMP      dMP   dMMMMMP dMMMMMP     \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "                                                                                \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "                                                                                   \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "                    ~                               \n" ANSI_COLOR_RESET);
  printf("                                                   Console edition  \n");
  printf(ANSI_COLOR_GREEN "\n  PRESS ANY KEY \n" ANSI_COLOR_RESET);

  getchar();
  clearTerminal();
}

void winMeme()
{

  printf(ANSI_COLOR_BLUE "░░░░░░▄██████████████▄░░░░░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░░░░▄██████████████████▄░░░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░░░█▀░░░░░░░░░░░▀▀███████░░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░░█▌░░░░░░░░░░░░░░░▀██████░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░█▌░░░░░░░░░░░░░░░░███████▌░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░█░░░░░░░░░░░░░░░░░████████░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "▐▌░░░░░░░░░░░░░░░░░▀██████▌░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "░▌▄███▌░░░░▀████▄░░░░▀████▌░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "▐▀▀▄█▄░▌░░░▄██▄▄▄▀░░░░████▄▄░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "▐░▀░░═▐░░░░░░══░░▀░░░░▐▀░▄▀▌▌ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "▐░░░░░▌░░░░░░░░░░░░░░░▀░▀░░▌▌ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ░░░▄▀░░░▀░▌░░░░░░░░░░░░▌█░▌▌ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE " ░▌░░▀▀▄▄▀▀▄▌▌░░░░░░░░░░▐░▀▐▐░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE " ░▌░░▌░▄▄▄▄░░░▌░░░░░░░░▐░░▀▐░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE " ░█░▐▄██████▄░▐░░░░░░░░█▀▄▄▀░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE " ░▐░▌▌░░░░░░▀▀▄▐░░░░░░█▌░░░░░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE " ░░█░░▄▀▀▀▀▄░▄═╝▄░░░▄▀░▌░░░░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ░░░▌▐░░░░░░▌░▀▀░░▄▀░░▐░░░░░░░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ░░░▀▄░░░░░░░░░▄▀▀░░░░█░░░░░░░ \n" ANSI_COLOR_RESET),
      printf(ANSI_COLOR_BLUE "  ░░░▄█▄▄▄▄▄▄▄▀▀░░░░░░░▌▌░░░░░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ░░▄▀▌▀▌░░░░░░░░░░░░░▄▀▀▄░░░░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ▄▀░░▌░▀▄░░░░░░░░░░▄▀░░▌░▀▄░░░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "  ░░░░▌█▄▄▀▄░░░░░░▄▀░░░░▌░░░▌▄▄ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "  ░╔╗║░╔═╗░═╦═░░░░░╔╗░░╔═╗░╦═╗░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "  ░║║║░║░║░░║░░░░░░╠╩╗░╠═╣░║░║░ \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "  ░║╚╝░╚═╝░░║░░░░░░╚═╝░║░║░╩═╝░\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_YELLOW "  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n" ANSI_COLOR_RESET);

  waitS(0);
  clearTerminal();
}

void inicGame(char *str, int i)
{

  printf("           ⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠀ \n");
  printf("           ⣰⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣧⢀ \n");
  printf("          ⣿⣿⣿⠋⠀⠀⠀⠀⠀⠙⠀⠙⣿⣿⣿⣷⢳⢀⠀⠀  ,'                                    \n");
  printf("          ⣿⣿⣿⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿                                  \n");
  printf("         ⣸⣿⣿⣿⠸⠀⠀⠀⠒⠒⠒⠐⠀⠀⢿⣿⣿⣿⣿⣿⠀                                   \n");
  printf("         ⣴⣿⣿⣿⡿⠀⠒⣋⣙⡒⢰⠀⠤⣖⠒⢾⣿⣿⣿⣿⣧                                      \n");
  printf("         ⢺⣿⣿⣿⣿⢀⠀⠀⠉⠉⠉⠸⠀⡇⠉⠉⠀⢿⣿⣿⣿⣄                                  \n");
  printf("         ⠙⣿⣿⣧⢻⠀⠀⠀⠀⠀⠠⠀⠰⠀⠀⠀⣸⠸⣿⣿⠿⠰⠀                                  \n");
  printf("         ⠹⣿⣿⣿⣷⠀⡠⠙⣲⣔⣅⢡⣰⣷⣿⣿⣿⣧⠀                                  \n");
  printf("          ⣼⣿⣿⣿⣿⠀⡿⠭⠭⠭⠭⢿⠀⣿⢻⣿⣿⠃                                      \n");
  printf("          ⠙⠛⣿⢻⠹⣿⠐⠙⠛⠟⠉⢀⣴⡟⢿⣿⡏                                     \n");
  printf("             ⡟⠀⠀⠻⣦⣤⣶⠾⠋⠀⠀⠁⡦⢄⢀                                    \n");
  printf("           ⡠⠁⡇⠑⢄⠀⠀⠀⠀⠀⠀⠔⠀⠀⠁⠀⠀⠀⠉⠁                                        \n");
  printf("            ⠔⣇⠀⠀⠀⠑⡤⠤⢎⠁⠀⠀⡘⠀⠀⠀⠀⠀⠀                            \n");
  printf("	          ⠀      ⢢⠠⠀⡠⢆⠀⠀⡠⠙⢄⠀⡸⠀                                                  \n");
  if (i == 0)
    printf("  Hello %s \n Welcome to the game of naval battle.\n We will continue with a brief tutorial on the game pieces.\n Good luck.      \n", str);
  if (i == 1)
  {
    printf("	   You lost the game: %s     \n", str);
    waitS(0);
  }

  if (i > 1)
  {
    printf("	   Congratulations you are the winner: %s     \n", str);
    waitS(0);
  }
}

void waitS(int i)
{

  printf(ANSI_COLOR_RED "\nwait a few seconds\n" ANSI_COLOR_RESET);

  if (i == 0)
    sleep(3);
  else
    sleep(1);

  clearTerminal();
}

void display(Map *root)
{
  printMap(root);
  printHistory(root);
}

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

  printf("%2d| ", root->mapSize);

  for (int i = 1; i <= iLim; i++)
  {
    cur = searchBit(root, &p);

    if (cur == NULL || *cur == '0')
      printf(ANSI_COLOR_BLUE "0 " ANSI_COLOR_RESET);

    else if (*cur == '1')
      printf(ANSI_COLOR_GREEN "1 " ANSI_COLOR_RESET);

    else if (*cur == '2')
      printf(ANSI_COLOR_RED "2 " ANSI_COLOR_RESET);

    else
      printf(ANSI_COLOR_YELLOW "3 " ANSI_COLOR_RESET);

    if (i % root->mapSize == 0)
    {
      if (i / root->mapSize < root->mapSize)
        printf("\n%2d| ", root->mapSize - i / root->mapSize);

      else
        printf("\n");
    }

    movePointLeft(root, &p);
  }

  printf("    ");

  for (int i = 0; i < root->mapSize; i++)
    printf("--");

  printf("\n   ");

  for (int i = 0; i < root->mapSize; i++)
    if (i % 2 == 0)
      printf(ANSI_COLOR_RED "%2d" ANSI_COLOR_RESET, i + 1);
    else
      printf(ANSI_COLOR_YELLOW "%2d" ANSI_COLOR_RESET, i + 1);

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

  printf("%2d| ", root->mapSize);

  for (int i = 1; i <= iLim; i++)
  {
    cur = searchShoot(root, &p);

    if (cur == NULL || *cur == '0')
      printf(ANSI_COLOR_BLUE "0 " ANSI_COLOR_RESET);

    else if (*cur == '1')
      printf(ANSI_COLOR_RED "1 " ANSI_COLOR_RESET);

    else
      printf(ANSI_COLOR_YELLOW "2 " ANSI_COLOR_RESET);

    if (i % root->mapSize == 0)
    {
      if (i / root->mapSize < root->mapSize)
        printf("\n%2d| ", root->mapSize - i / root->mapSize);

      else
        printf("\n");
    }

    movePointLeft(root, &p);
  }

  printf("    ");

  for (int i = 0; i < root->mapSize; i++)
    printf("--");

  printf("\n   ");

  for (int i = 0; i < root->mapSize; i++)
  {
    if (i % 2 == 0)
      printf(ANSI_COLOR_RED "%2d" ANSI_COLOR_RESET, i + 1);
    else
      printf(ANSI_COLOR_YELLOW "%2d" ANSI_COLOR_RESET, i + 1);
  }
  printf("\n\n");
}

void printMapByLevel(Map *root)
{
  MList *stack = newMapList();

  pushMap(stack, root);

  while (stack->size > 0)
  {
    Map *temp = popMap(stack);

    if (temp == NULL)
      continue;

    printf("Limites do mapa\n");
    printPoint(temp->tl);
    printPoint(temp->br);

    printf("Numero de pontos = %d\n\n", temp->nP);

    if (temp->nw == NULL)
      for (int i = 0; i < temp->nP; i++)
      {
        printPoint(temp->vec[i].pos);
        printCell(temp->vec[i].cell);
      }

    else
    {
      if (temp->vec != NULL)
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

  if (cell == NULL)
  {
    printf("There is no cell\n");
    return;
  }

  if (cell->ship == NULL)
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

void directionHelpPrint()
{
  printf("Use lowercase in the direction:\n");
  printf(ANSI_COLOR_YELLOW "North ------> n\n");
  printf("South ------> s\n");
  printf("West -------> w\n");
  printf("East--------> e\n\n" ANSI_COLOR_RESET);
}
