#ifndef SEARCH
#define SEARCH

#include "point.h"
#include "map.h"
#include "ship.h"
#include "error.h"

/* Procura na arvore e retorna o apontador para o shoot que esta no ponto p
   Caso não exista retorna NULL. Complexidade O(ln n)*/
char *searchShoot(Map *root, Point *p);

/* Procura na arvore e retorna o apontador para o bit que esta no ponto p
   Caso não exista retorna NULL. Complexidade O(ln n)*/
char *searchBit(Map *root, Point *p);

/* Procura na arvore e retorna o apontador para um navio que esta no ponto p.
   Caso não exista retorna NULL. Complexidade O(ln n)*/
Ship *searchShip(Map *root, Point *p);

/* Procura na arvore e retorna o apontador para uma celula que esta no ponto p
   Caso não exista retorna NULL. Complexidade O(ln n)*/
Cell *searchCell(Map *root, Point *p);

/* Procura na arvore e retorna o apontador para um Nó que esta no ponto p
   Caso não exista retorna NULL. Complexidade O(ln n)*/
Node *searchNode(Map *root, Point *p);

/* Retorna o apontador para o nivel, que poderá conter o nó com o ponto p
   Se retornar NULL, esta a ser feito um mal uso da função. Ter cuidado.*/
Map *searchDepth(Map *level, Point *p);

/* Procura no nivel currente, pelo ponto p e retorna o nó correspondente*/
Node *searchLevel(Map *level, Point *p);

/* Retorna 1 caso o ponto p esta fora dos limites do nivel, caso contrario
   retorna 0.*/
int outOfBounds(Map *level, Point *p);

#endif
