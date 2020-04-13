#include "game.h"
#include <ctype.h>  
//main
 int main(){
  
  srand(time(NULL));
  int size,q=1;
  menuStar();
  size=defineBattlefieldSize();
  
  printf(ANSI_COLOR_GREEN"Player 1\n"ANSI_COLOR_RESET);
  Player *p1 = initiatePlayer(size);
  wait();
  printf(ANSI_COLOR_GREEN"Player 2\n"ANSI_COLOR_RESET);
  Player *p2 = initiatePlayer(size);
  wait();
  
    while(q){
    game(p1,p2,size);
    q=askContinue();
    wait();
    if(q==1){
    restartGame(p1,p2);
    }
  }
    clearMemory(p1,size);
    clearMemory(p2,size);
  
  return 0;
}

//size the board 

int defineBattlefieldSize() {
   
   int size,i=1;
   while (i){
   size = defineSize();
   clearTerminal();
   if(minBattlefieldSize(size)==1)
   i=0;
   }
  
  return size;
}

//define size the board

int defineSize()
{ 
  int n;
  printf(ANSI_COLOR_RED"Please define de size of the board\n"ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN"Must be greater than 8\n"ANSI_COLOR_RESET);
  scanf("%d", &n);
  getchar(); 
  return n;
}

//limit minimum size 

int minBattlefieldSize(int size){
	
	if(size>=9)
	return 1;
	return 0;
	}

//initiate player

Player *initiatePlayer(int size)
{
  Player *p = (Player*)malloc(sizeof(Player));
  if(p==NULL)
  errorMessageMem("player");
  
  p->map = newMap(size);
  p->his = newMap(size);
  p->ship = initiateShip();
  p->name = getName();
  p->nhit=0;
  
  askForMap(p->name,p->map,p->ship,0);
  printPlayer(p);
  
  return p;     
}

//choose random or manual mode

void askForMap(char *str, Map *map, Ship *ship,int i)
{ 
     if(i==0)
     information();
     printf(ANSI_COLOR_GREEN"If you want to insert Manual press y, if you want Random press any key\n"ANSI_COLOR_RESET);
     char ch = getchar();
     getchar();
  
   
     if( ch=='y' ){
	  insertManual(map, ship);
      }
     else{
	  insertRandom(map, ship);
      }

}

// get player name

char *getName()
{ 
  char *str = (char*)malloc(maxNameSize*sizeof(char));
  if(str==NULL)
  errorMessageMem("get name player");
  
  printf(ANSI_COLOR_RED"Your name please \n"ANSI_COLOR_RESET);
  if(fgets(str,maxNameSize, stdin)) { 
    if (NULL == strchr(str, '\n'))
     eat_Extra(); 
     return str; 
     }
}

void eat_Extra(void) {
    
    int ch;
    while ((ch = getchar()) != '\n') {
        if (ch < 0)
        exit(EXIT_FAILURE); 
    }
}

//start game

void game(Player *p1, Player *p2,int size){ 
  
  int f=0,c=1,q;
  Player* turn;
  Player* adv;
  Point* p =newPoint();
  
  turn=p1;
  adv=p2;
  
  while(c){
	   
	   q=1;
	   printPlayerInfo(turn,adv);
	   
	   while(q){
	   if(f==1)
	   printPlayerInfo(turn,adv);
	   f=0;
	   p=askPoint(p,size);
	   c=checkShoot(p,turn,adv);
	   if(c!=99)
	   q=0;  
	   else{
	   printf(ANSI_COLOR_GREEN"Hit the ship\n"ANSI_COLOR_RESET);
	   winMeme();
	   f=1;
	   }
	 }
	   clearTerminal();
	   if(turn==p2){
	   turn=p1;
	   adv=p2;
       }
	   else{ 
	   turn=p2;
	   adv=p1;
       }
    }
    
   clearGame(p1,p2);
   }


// check input
int inputCheck(){
	char x[10];
	int i=1,v;
	
	while(i){
	if(fgets(x,10, stdin)) { 
    if (NULL == strchr(x, '\n'))
    eat_Extra(); 
    }
	for (int j=0;j<strlen(x)-1;j++)
        if (!isdigit(x[j]))
        {   
			printf ("Entered input is not a number\n");
            break;
        }
        else
        i=0;
    }
     v=atoi(x);
    return v;
 } 


char inputCheckChar(){
	int i=1;
	char x[10];
	while(i){
	if(fgets(x,10, stdin)) { 
    if (NULL == strchr(x, '\n'))
    eat_Extra(); 
    }
    if(strlen(x)==2)
    i=0;
    else
    printf("Please see game information\n");
    }
    return x[0];
  
 } 
	

//ask for the point

Point* askPoint(Point* p,int size){
	int i=1;
	
	while(i){
	printf(ANSI_COLOR_GRAY"Coordinates of your shoot:\n\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GRAY"x:"ANSI_COLOR_RESET);
	p->x=inputCheck();
	printf(ANSI_COLOR_GRAY"\ny:"ANSI_COLOR_RESET);
	p->y=inputCheck();
	printf("\n");
    if(checkPoint(p,size)!=0)
    i=0;
    }
	return p;
	}

//check the point

int checkPoint(Point* p,int size){
	
	if(p->x>size || p->y>size ||p->x<=0 || p->y<=0 ){ 
	printf(ANSI_COLOR_RED"Coordinates goes beyond the battlefield\n\n"ANSI_COLOR_RESET);
	return 0;
	}
	return 1;
	}

//check victory

int checkWin(Player* p1){
	
	if(p1->nhit==Npoints){
	clearTerminal();
	finalGame(p1->name );
    return 1;
    }
    else 
    return 0;
	}



//clear the memory

void clearMemory(Player* p1, int size){
	
	free(p1->ship->name);
	free(p1->ship->vec);
	free(p1->name);
	clearMemoryMap(p1->map,size);
	clearMemoryMap(p1->his,size);
	free(p1);
}

void clearMemoryMap(Map* p1,int size){
	
	for(int i=0;i<size;i++)
    {
        free(p1->map[i]);
    }
    free(p1->map);
}
 

//clean the board

void clearGame(Player* p1,Player* p2){
	
	deleteAll(p1->map);
	deleteAll(p2->map);
	deleteAll(p1->his);
	deleteAll(p2->his);
  }

//restart the game
  
void restartGame(Player* p1,Player* p2){
    
    p1->nhit=0;
    p2->nhit=0;
    
    printf(ANSI_COLOR_GREEN "Player: %s\n"ANSI_COLOR_RESET,p1->name);
    p1->ship = initiateShip();
    askForMap(p1->name, p1->map, p1->ship,1);
    printInfo(p1->map);
    wait();
    
    printf(ANSI_COLOR_GREEN"Player: %s\n"ANSI_COLOR_RESET,p2->name);
    p2->ship = initiateShip();
    askForMap(p2->name, p2->map, p2->ship,1);
    printInfo(p2->map);
    wait();
   }

//ask if you want to continue

int askContinue(){
	
	printf(ANSI_COLOR_GREEN"You want to play again?\n\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"Yes --> press y or No--> press any key  \n"ANSI_COLOR_RESET);
	char ch = getchar();
    getchar();
    if ( ch=='y' )
    return 1;
    else
    return 0;
	}


//check the shoot

int checkShoot(Point* p, Player* p1,Player* p2){
	 
	 if(search(p2->map,p)==0){
     printf(ANSI_COLOR_RED"Didn't hit the ship\n"ANSI_COLOR_RESET);
     wait();
	 insertPoint(p1->his,p,0);  //zero falhou --->this	 
     return 1;
     }
	 
	 else{
	 insertPoint(p1->his,p,1);	// 1 acertou---->this
	 insertHit(p2->map,p,'H');
	 p1->nhit++;
	 if(checkWin(p1)==1)
	 return 0;
	 else
	 return 99;
     }
  }


//display menu

void menuStar(){printf(ANSI_COLOR_RED "                                               	                                     \n"ANSI_COLOR_RESET); printf(ANSI_COLOR_RED "                     $                         	                                      \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "                        $$$      .oo..     'oooo'oooo'ooooooooo....                         \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "                         $       $$$$$$$                                                     \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "                     .ooooooo.   $$!!!!!                                                      \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "                   .'.........'. $$!!!!!      o$$oo.   ...oo,oooo,oooo'ooo''                 \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "      $          .o'  oooooo   '.$$!!!!!      $$!!!!!       'oo''oooo''                      \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "  ..o$ooo...    $                '!!''!.     $$!!!!!                                         \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "   $    ..  '''oo$$$$$$$$$$$$$.    '    'oo.  $$!!!!!       Version 1                            \n"ANSI_COLOR_RESET);  
printf(ANSI_COLOR_RED "   !.......      '''..$$ $$ $$$   ..        '.$$!!''!                                         \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "   !!$$$!!!!!!!!oooo......   '''  $$ $$ :o           'oo.                                      \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "   !!$$$!!!$$!$$!!!!!!!!!!oo.....     ' ''  o$$o .      ''oo..                              \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "   !!!$$!!!!!!!!!!!!!!!!!!!!!!!!!!!!ooooo..      'o  oo..    $   \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "    '!!$$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!oooooo..  ''   ,$  \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "     '!!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!oooo..$$  \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "      !!$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$'  \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "      '$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!!!!!!!!!!!!!!!!!!,  \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "  .....$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$...  \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_GRAY "                                                                              \n\n\n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "      dMMMMb  .aMMMb  dMP dMP .aMMMb  dMP \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "     dMP dMP dMP dMP dMP dMP dMP dMP dMP  \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "    dMP dMP dMMMMMP dMP dMP dMMMMMP dMP   \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "   dMP dMP dMP dMP  YMvAP  dMP dMP dMP    \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN"  dMP dMP dMP dMP    VP   dMP dMP dMMMMMP \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN"                                          \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "      dMMMMb  .aMMMb dMMMMMMP dMMMMMMP dMP     dMMMMMP \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "     dMP dMP dMP dMP   dMP      dMP   dMP     dMP      \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "    dMMMMK  dMMMMMP   dMP      dMP   dMP     dMMMP     \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "   dMP.aMF dMP dMP   dMP      dMP   dMP     dMP        \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "  dMMMMP  dMP dMP   dMP      dMP   dMMMMMP dMMMMMP     \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "                                                                                \n"ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "                                                                                   \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_GREEN "                    ~                               \n"ANSI_COLOR_RESET);
printf("                                                   Console edition  \n");  
printf(ANSI_COLOR_GREEN "\n  PRESS ANY KEY \n"ANSI_COLOR_RESET);

getchar();
clearTerminal();
}


//print  information the player 

void printPlayerInfo(Player *p,Player* p1)
{
  printfActive(p1->map);
  printf(ANSI_COLOR_YELLOW"Player :%s\n"ANSI_COLOR_RESET, p->name);
  printf(ANSI_COLOR_GREEN"Your Ships\n"ANSI_COLOR_RESET);
  printMap(p->map);
  printf(ANSI_COLOR_GREEN"You history of atacks\n"ANSI_COLOR_RESET);
  printMaphis(p->his);
}

void printPlayer(Player *p)
{
  printf(ANSI_COLOR_YELLOW"Player :%s\n"ANSI_COLOR_RESET, p->name);
  printf(ANSI_COLOR_GREEN"Your Ships\n"ANSI_COLOR_RESET);
  printMap(p->map);
  printf(ANSI_COLOR_GREEN"You history of atacks\n"ANSI_COLOR_RESET);
  printMaphis(p->his);
}










