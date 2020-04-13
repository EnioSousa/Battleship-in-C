#include "interface.h"
#include "map.h"

void printAll(Map *m){
  
  printInfo(m);
  printMap(m);
  }

void printInfo(Map *m){
  
  printf(ANSI_COLOR_RED"Map Size = %d,Num of Points = %d\n"ANSI_COLOR_RESET, m->mapSize,m->nPoint);
  putchar('\n');
}

void printMap(Map *m){ 
  
  for(int i=m->mapSize-1; i>=0; putchar('\n'), i--)
   for(int j=0; j<m->mapSize;j++ ){
    if(m->map[i][j]=='#')
    printf(ANSI_COLOR_BLUE "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else
    if(m->map[i][j]=='H')
    printf(ANSI_COLOR_YELLOW "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else 
    printf(ANSI_COLOR_GREEN"%c "ANSI_COLOR_RESET,m->map[i][j]);
    }
    
  putchar('\n');
}

void printMaphis(Map *m){
	    
  for( int i=m->mapSize-1; i>=0; putchar('\n'), i-- )
   for( int j=0; j<m->mapSize;j++ ){ 
    if(m->map[i][j]=='1')
    printf(ANSI_COLOR_GREEN "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else 
    if(m->map[i][j]=='0')
    printf(ANSI_COLOR_RED "%c "ANSI_COLOR_RESET,m->map[i][j]);
    else
    printf(ANSI_COLOR_BLUE"%c "ANSI_COLOR_RESET,m->map[i][j]);
    }
  
  putchar('\n');
}

void printPoint(Point *p){
	  
 printf("(%d,%d)\n", p->x, p->y);
}


void clearTerminal(){
  
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
      system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
      system("cls");
  #endif
}


void printMap2(Map* map){
  
  printf(ANSI_COLOR_GREEN"Your Ships\n"ANSI_COLOR_RESET);
  printMap(map);
}

void printRepeat(int n, char ch){
  
  for( int i=0; i<n; putchar(ch), i++ );
}


void flush_in(){
   
   int ch;
   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
} 

void winMeme(){
	
	printf(ANSI_COLOR_BLUE"░░░░░░▄██████████████▄░░░░░░░\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE"░░░░▄██████████████████▄░░░░░\n"ANSI_COLOR_RESET); 
	printf(ANSI_COLOR_BLUE"░░░█▀░░░░░░░░░░░▀▀███████░░░░\n"ANSI_COLOR_RESET) ;
	printf(ANSI_COLOR_BLUE"░░█▌░░░░░░░░░░░░░░░▀██████░░░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"░█▌░░░░░░░░░░░░░░░░███████▌░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"░█░░░░░░░░░░░░░░░░░████████░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"▐▌░░░░░░░░░░░░░░░░░▀██████▌░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"░▌▄███▌░░░░▀████▄░░░░▀████▌░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"▐▀▀▄█▄░▌░░░▄██▄▄▄▀░░░░████▄▄░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"▐░▀░░═▐░░░░░░══░░▀░░░░▐▀░▄▀▌▌ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"▐░░░░░▌░░░░░░░░░░░░░░░▀░▀░░▌▌ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ░░░▄▀░░░▀░▌░░░░░░░░░░░░▌█░▌▌ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE" ░▌░░▀▀▄▄▀▀▄▌▌░░░░░░░░░░▐░▀▐▐░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE" ░▌░░▌░▄▄▄▄░░░▌░░░░░░░░▐░░▀▐░░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE" ░█░▐▄██████▄░▐░░░░░░░░█▀▄▄▀░░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE" ░▐░▌▌░░░░░░▀▀▄▐░░░░░░█▌░░░░░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE" ░░█░░▄▀▀▀▀▄░▄═╝▄░░░▄▀░▌░░░░░░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ░░░▌▐░░░░░░▌░▀▀░░▄▀░░▐░░░░░░░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ░░░▀▄░░░░░░░░░▄▀▀░░░░█░░░░░░░ \n"ANSI_COLOR_RESET) ,
    printf(ANSI_COLOR_BLUE"  ░░░▄█▄▄▄▄▄▄▄▀▀░░░░░░░▌▌░░░░░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ░░▄▀▌▀▌░░░░░░░░░░░░░▄▀▀▄░░░░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ▄▀░░▌░▀▄░░░░░░░░░░▄▀░░▌░▀▄░░░ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_BLUE"  ░░░░▌█▄▄▀▄░░░░░░▄▀░░░░▌░░░▌▄▄ \n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_YELLOW"  ░╔╗║░╔═╗░═╦═░░░░░╔╗░░╔═╗░╦═╗░\n"ANSI_COLOR_RESET) ;
    printf(ANSI_COLOR_YELLOW"  ░║║║░║░║░░║░░░░░░╠╩╗░╠═╣░║░║░ \n"ANSI_COLOR_RESET); 
    printf(ANSI_COLOR_YELLOW"  ░║╚╝░╚═╝░░║░░░░░░╚═╝░║░║░╩═╝░\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW"  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"ANSI_COLOR_RESET); 

   wait();
   clearTerminal();
}



void finalGame(char *str){
	                                                                       
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
  printf("	   Congratulations you are the winner: %s     \n",str);
  waitLong();
	
}

void information(){
   
   clearTerminal();
   printf(ANSI_COLOR_GREEN"\nThe game pieces: \n"ANSI_COLOR_RESET);
   printf(ANSI_COLOR_RED"\nid: 0------> Carrier\n\n"ANSI_COLOR_RESET);
   printf("Size the ship occupies: 5 Points\n");
   printf("Graphic piece:\n\n");
   printCarrier();
   printf("\nNumber of ships: 1\n");
   printf(ANSI_COLOR_RED"\nid: 1------> Battleship\n\n"ANSI_COLOR_RESET);
   printf("Size the ship occupies: 4 Points\n");
   printf("Graphic piece:\n");
   printBattleship();
   printf("Number of ships: 2\n");
   printf(ANSI_COLOR_RED"\nid: 2------> Cruiser\n\n"ANSI_COLOR_RESET);
   printf("Size the ship occupies: 3 Points\n");
   printf("Graphic piece:\n");
   printCruiser();
   printf("Number of ships: 2\n\n");
   waitLong();
   printf(ANSI_COLOR_RED"\nid: 3------> Submarine\n\n"ANSI_COLOR_RESET);
   printf("Size the ship occupies: 3 Points\n");
   printf("Graphic piece:\n");
   printSubmarine();
   printf("Number of ships: 1\n");
   printf(ANSI_COLOR_RED"\nid: 4------> Destroyer\n\n"ANSI_COLOR_RESET);
   printf("Size the ship occupies: 2 Points\n");
   printf("Graphic piece:\n");
   printDestroyer();
   printf("Number of ships: 4\n\n");
  
  waitLong();
}
	
void waitLong(){
	
	printf(ANSI_COLOR_RED "wait a few seconds\n"ANSI_COLOR_RESET);
    sleep(4); 
    clearTerminal();
}


void temporyPrint(){
	
	printf("Use lowercase in the direction:\n");
	printf(ANSI_COLOR_YELLOW"North ------> n\n");
	printf("South ------> s\n");
	printf("West -------> w\n");
    printf("East--------> e\n\n"ANSI_COLOR_RESET);
}

void wait(){
	
	printf(ANSI_COLOR_RED "wait a few seconds\n"ANSI_COLOR_RESET);
    sleep(1); 
    clearTerminal();
}

int checkDir(char dir){
	
 switch (dir){
   case 'w':
   return 1;
   break;
   case 'e':
   return 1;
   break;
   case 'n':
   return 1;
   break;
   case 's':
   return 1;
   break;
   default:
   printf("Invalid direction\n");
   return 0; 
   }
}

void printCarrier(){
   
   printf(ANSI_COLOR_YELLOW"0    \n");  
   printf("0 0 0\n");     
   printf("0    \n"ANSI_COLOR_RESET);   
}



void printBattleship(){
	
	printf(ANSI_COLOR_YELLOW"     \n");  
    printf("1 1 1 1\n");     
    printf("     \n"ANSI_COLOR_RESET);
}


void printCruiser(){
    
    printf(ANSI_COLOR_YELLOW"     \n");  
    printf("2 2 2\n");     
    printf("     \n"ANSI_COLOR_RESET);

}

void printSubmarine(){
	
	printf(ANSI_COLOR_YELLOW"     \n");  
    printf("3 3 3\n");     
    printf("     \n"ANSI_COLOR_RESET);
}


void printDestroyer(){
	
	printf(ANSI_COLOR_YELLOW"     \n");  
    printf("4 4\n");     
    printf("     \n"ANSI_COLOR_RESET);
}



void printfActive(Map* map){	
	
	int count=0,count1=0,count2=0,count3=0,count4=0;
	printf(ANSI_COLOR_GREEN"Enemy actives: "ANSI_COLOR_RESET);
	
	for(int i=0;i<map->mapSize;i++){
	 for(int j=0;j<map->mapSize;j++){
	  if(map->map[i][j]=='0')
	  count++;
	  else
	  if(map->map[i][j]=='1')
	  count1++;
	  else
	  if(map->map[i][j]=='2')
	  count2++;
	  else
	  if(map->map[i][j]=='3')
	  count3++;
	  else
	  if(map->map[i][j]=='4')
	  count4++;
  }
  }
 
 if(count>0)
 printf(ANSI_COLOR_RED"Carrier "ANSI_COLOR_RESET);
 if(count1>0)
 printf(ANSI_COLOR_RED"Battleship "ANSI_COLOR_RESET);
 if(count2>0)
 printf(ANSI_COLOR_RED"Cruiser "ANSI_COLOR_RESET);
 if(count3>0)
 printf(ANSI_COLOR_RED"Submarine "ANSI_COLOR_RESET);
 if(count4>0)
 printf(ANSI_COLOR_RED"Destroyer "ANSI_COLOR_RESET);
 
 printf("\n");

}
	
void informationShip(Ship* s){
	
	printf("Number of ships remaining:\n");
	if(s[0].left!=0)
	printf(ANSI_COLOR_YELLOW"Id:0 -->Carrier: %d \n",s[0].left);
	if(s[1].left!=0)
	printf("Id:1 -->Battleship: %d \n",s[1].left);
	if(s[2].left!=0)
	printf("Id:2 -->Cruiser: %d \n",s[2].left);
	if(s[3].left!=0)
	printf("Id:3 -->Submarine: %d \n",s[3].left);
	if(s[4].left!=0)
	printf("Id:4 -->Destroyer: %d \n\n"ANSI_COLOR_RESET,s[4].left);

}















