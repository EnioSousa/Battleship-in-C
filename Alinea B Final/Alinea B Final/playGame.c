#include "playGame.h"

int main()
{

  srand(time(NULL));
  int size, endGame = 1, i = 0;
  menuStar();
  size = defineBattlefieldSize();

  while (endGame)
  {
    printf(ANSI_COLOR_GREEN "Player 1\n" ANSI_COLOR_RESET);
    Player *p1 = initiatePlayer(size, i);
    waitS(0);
    printf(ANSI_COLOR_GREEN "Player 2\n" ANSI_COLOR_RESET);
    Player *p2 = initiatePlayer(size, i);
    waitS(0);
    clearTerminal();
    game(p1, p2, size);
    endGame = askContinue();
    i = 1;
  }
  printf(ANSI_COLOR_GREEN "\nGoodbyen\n" ANSI_COLOR_RESET);

  return 0;
}
