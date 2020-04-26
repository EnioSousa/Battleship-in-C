#include "clearMemory.h"
#include <stdlib.h> 
#include "ship.h"



void clearMemory(Player* p1, int size){
	
	free(p1->countPoints);
	free(p1->map->ship);
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
