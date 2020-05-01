#include "input.h"
#include <stdlib.h> 
#include "errorMessage.h"
#include "interface.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>


/*-----------------------Numbers input--------------------------------*/
 
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

/*-----------------------Char input--------------------------------*/

char inputCheckChar(int r){
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
 
/*-----------------------Name user input--------------------------------*/ 
char *getName()
{ 
  char *str = (char*)malloc(maxNameSize*sizeof(char));
  if(str==NULL)
  errorMessageMem("name player");
  
  printf(ANSI_COLOR_RED"Your name please \n"ANSI_COLOR_RESET);
  if(fgets(str,maxNameSize, stdin)) { 
    if (NULL == strchr(str, '\n'))
     eat_Extra(); 
     return strdup(str); 
     }
}

/*-----------------------Auxiliary functions------------------------- */

void eat_Extra(void) {
    
    int c;
    while ((c = getchar()) != '\n') {
        if (c < 0)
        exit(EXIT_FAILURE); 
    }
}

/*-----------------------flush in -----------------------*/

void flush_in(){
   
   int c;
   while( (c = fgetc(stdin)) != EOF && c != '\n' ){}
} 

