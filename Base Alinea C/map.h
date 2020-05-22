#ifndef MAP_WORLD
#define MAP_WORLD

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "point.h"
#include "errorMessage.h"

#define LIM 4 // Dont' change it to a value lower than 4


/* ship  -> Apontador para o tipo de barco que ocupa a cell
   bit   -> Identificador do estado da celula.
            1) possição tem um ponto do barco não atingida
	    2) possição tem um ponto do barco atingida.
	    3) Não tem barco, mas o adversario atirou na celula
   shoot -> Representa a historia de ataques do jogador
            1) O jogador atirou no mapa adversario mas não acertou
	    2) O jogador atirou no mapa adversario e acertou*/
typedef struct Cell
{
  Ship *ship;

  char shoot, bit;
}Cell;

/* pos  -> É um ponto com coordenadas x e y.
   cell -> representa o estado da possição pos.*/
typedef struct Node
{
  Point *pos;

  Cell *cell;

}Node;

/* mapSize -> Tamanho da camada
   tl -> Coordenadas do ponto Top Left
   br -> Coordenadas do ponto Botom Rigth
   vec -> Array de nós i.e os nós presentes neste nivel do mapa
   nP -> Numero de nós que existem na presente e "abaixo" deste nivel
   father -> Endereço da camanha pai
   nw -> Endereço do filho North West
   ne -> Endereço do filho North East
   sw -> Endereço do filho South West
   se -> Endereço do filho South East
   won -> Indica se o jogador ganhou
   lost -> Indica se o jogador perdeu*/
typedef struct Map
{
  int mapSize;

  Point *tl, *br;

  Node *vec;
  int nP;

  Ship *ship;

  struct Map *father;

  struct Map *nw;
  struct Map *ne;
  struct Map *sw;
  struct Map *se;

} Map;

/*----------------------------New struct--------------------------*/

/* Esta função inicializa e retorna um apontador do tipo Map.
   ship -> Array de ship. Ver API ship.h para mais informação
   mapSize -> Devera ser o tamanho maximo que o mapa podera ter*/
Map *newMap(int mapSize, Ship *ship);

/* Esta função ira criar e retornar um apontador de um novo filho,
   do pai father, com limites a e b*/
Map *newSon(Map *father, Point *a, Point *b);

/* Esta função ira criar um novo nó com a informação passada e ira
   adiciona-lo ao nivel currente. Atenção que esta função não verifica
   se o nó já existe, esse trabalho tem que ser feito anteriormente*/
void newNode(Map *level, Ship *ship, Point *p, char bit, char shoot);

/* Função incrementa o numero de pontos existentes na camada currente e nas
   de "cima" por n.*/
void incUp(Map *level, int n);

/* Função adiciona um no ao nivel currente.*/
void addNode(Map *level, Node *no);

/* Função inicializa e retorna um apontador do tipo Cell*/
Cell *newCell(Ship *ship, char bit, char shoot);

/*----------------------------Free struct--------------------------*/

/* Função liberta toda a memoria alocada dinamicamente pelas funções
   newMap/2 e newSon/2. Literalmente ira libertar todos os niveis*/
void freeMap(Map *root);

/* Função liberta toda a memoria alocada dinamicamente para um certo nivel
   do mapa, passado como argumento, level.*/
void freeMapLevel(Map *level);

/* Ira libertar toda a memoria alocada dinamicamente que esta "contida" no
   array de nós.*/
void freeVectorNode(Node *vecNode, int size);

/*----------------------------Division----------------------------------*/

/* Esta função ira ver se é possivel dividir o nivel currente em 4 partes.
   Casso seja possivel então ira ser dividido e a informação contida no
   nivel currente será passada para os seus filhos.*/
void newPartition(Map *level);

/* Função retorna 1 caso seja possivel dividir o nivel currente, caso contrario
   retorna 0*/
int possibleToDivide(Map *level);

/* Função que realmente divide o mapa e passa a informação de um nivel
   para outro, chamando a função copyForward/1*/
void divideInFour(Map *level);

/* Esta função move a informação contida em father para os seu filhos*/
void copyForward(Map *father);

/* Função que nos diz que filho devera reter a informação contida no ponto p.
   0 -> O nivel currente i.e level, devera reter a  informação
   1 -> O filho South West i.e level->sw devera reter a informação
   2 -> O filho South East i.e level->se devera reter a informação
   3 -> O filho North West i.e level->nw devera reter a informação
   4 -> O filho North East i.e level->ne devera reter a informação*/
int whichQuadrant(Map *level, Point *p);

#endif
