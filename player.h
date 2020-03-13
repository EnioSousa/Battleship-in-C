#ifndef PLAYER
#define PLAYER
#include <stdio.h>
#include <stdlib.h>

typedef struct player{
	char* name;
	int id;
	}
player;

player* newplayer(char* name,int id);

#endif
