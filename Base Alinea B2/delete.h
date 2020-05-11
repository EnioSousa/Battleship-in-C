#ifndef DELETE
#define DELETE

#include <stdio.h>
#include <stdlib.h>

#include "insert.h"
#include "search.h"
#include "map.h"
#include "point.h"

/*----------------------------delete----------------------------------*/

/* Remove um ponto/celula do mapa caso exista.*/
void deletePoint(Map *root, Point *p);

/* Remove um dado ponto do nivel currente se existir*/
void deletePointOnDepth(Map *level, Point *p);

/* Troca dos elementos do array de nós*/
void swap(Node *a, Node *b);

/* Compacta o array de nós presente no currente nivel*/
void compact(Map *level);

/* Decrementa o numero de pontos para os nivel "acima" de level*/
void downUp(Map *level, int n);

/* Retorna 1 se for possivel libertar um nivel da arvore, caso contrario 0*/
int possibleToFree(Map *level);

/* Liberta os filhos de father, copiada de volta toda a informação contida neles*/
void freeSons(Map *father);

/* Copia todos os nós contidos em son para father*/
void copyBack(Map *father, Map *son);

#endif
