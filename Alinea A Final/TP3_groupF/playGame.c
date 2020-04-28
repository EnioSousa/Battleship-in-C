#include "playGame.h"

 int main(){
  
  srand(time(NULL));
  int size,endGame=1;
  menuStar();
  size=defineBattlefieldSize();
  
  printf(ANSI_COLOR_GREEN"Player 1\n"ANSI_COLOR_RESET);
  Player *p1 = initiatePlayer(size);
  waitS(2);
  printf(ANSI_COLOR_GREEN"Player 2\n"ANSI_COLOR_RESET);
  Player *p2 = initiatePlayer(size);
  waitS(2);
  
    while(endGame){
    game(p1,p2,size);
    endGame=askContinue();
    waitS(2);
    clearGame(p1,p2);
    if(endGame==1){
    restartGame(p1,p2);
    }
  }
    printf(ANSI_COLOR_GREEN"\nGoodbyen\n"ANSI_COLOR_RESET);
    clearMemory(p1,size);
    clearMemory(p2,size);
  
  return 0;
}





