#include "interface.h"
#include "input.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "insertDelete.h"


/*-----------------------Clear terminal ---------------------------------*/
void clearTerminal(){
  
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
      system("clear");
  #endif

  #if defined(_WIN64) || defined(_WIN32) 
      system("cls");
  #endif
}



/*-----------------------Images--------------------------------------------*/


void menuStar(){
printf(ANSI_COLOR_RED "                                               	                                     \n"ANSI_COLOR_RESET); 
printf(ANSI_COLOR_RED "                     $                         	                                      \n"ANSI_COLOR_RESET); 
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

   waitS(4);
   clearTerminal();
}

void inicGame(char *str,int i){
  
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
  if(i==0)
  printf("  Hello %s \n Welcome to the game of naval battle.\n We will continue with a brief tutorial on the game pieces.\n Good luck.      \n",str);
  else
  printf("	   Congratulations you are the winner: %s     \n",str);
  waitS(5);

}

/*-----------------------wait---------------------------------*/

void waitS(int i){
	
	printf(ANSI_COLOR_RED "\nwait a few seconds\n"ANSI_COLOR_RESET);
    sleep(i); 
    clearTerminal();
}

/*-------------------------------------------Ask-----------------------------------*/



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



/*-------------------------------Information---------------------------------*/

void directionHelpPrint(){
	printf("Use lowercase in the direction:\n");
	printf(ANSI_COLOR_YELLOW"North ------> n\n");
	printf("South ------> s\n");
	printf("West -------> w\n");
    printf("East--------> e\n\n"ANSI_COLOR_RESET);
}



