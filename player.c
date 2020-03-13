#include "player.h"


player* newplayer(char* name, int id){
	
	player *p = (player*)malloc(sizeof(player));	
	
	if ( p==NULL )
     {
      fprintf(stderr,"Falta de memória em newPoint\n");
      exit(EXIT_FAILURE);
     }
	
	p->name=name;
	p->id=id;
	
	return p;
	}


