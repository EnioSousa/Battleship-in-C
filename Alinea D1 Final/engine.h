#ifndef ENGINE
#define ENGINE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <ctype.h>
#include "point.h"
#include "map.h"

#include "ship.h"
#include "interface.h"
#include "insert.h"

#include <time.h>
#include <sys/file.h>
#include <signal.h>

/* BUFFERSIZE -> Tamanho maximo do buffer.
   buffer -> Uma string que vai ser usada como "buffer" temporario
   antes de escrevermos nos files*/
#define BUFFERSIZE 1024
char *buffer;

/* fd -> Descritor do ficheiro aberto pelo programa. */
#define FIFO_FILE "/tmp/myfifo"
int fd;

/* Last point shot*/
Point last;

/* É preciso ter cuidado ao sair do programa. Caso seja passado
   GIGINT, O programa sai, mas não chega a fechar o Pipe. Esta
   função combate esse problema.*/
void handle_sigint(int sig);

/* Função reporta e faz exit caso haja algum erro. Atenção o
   programador é que fica responsavel de chamar esta função,
   ela so serve para o programador saber onde esta a falhar.*/
void reportAndExit(char *str);

/* Retorna 1 caso a string seja um numero, 0 caso contrario*/
int stringIsNumber(char *str);

/* Gere a criação dos named pipes*/
void pipeManagement();

/* Função cria espaço dinamicamente para um buffer intermedio que
   iremos usar antes de escrever em cada ficheiro.*/
void bufferManagement();

/* Função le uma linha do ficheiro file e mete num buffer. Esta
   função não le alem do tamanho maximo do buffer*/
char *myReadLine(int file);

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* Altera esta função joão. Podes tambem alterar o tipo de retorno
   Altera de modo a receberes apenas o nome do jogador e ver se o gajo
   quer manual ou random*/
Map *initiatePlayer();

/* Funções stateX por favor ver o automato em anexo. Basicamente
   eles são o ciclo logico de execução. Ver o automato pois é
   bastante facil de perceber*/
void start(Map *map, int nPlayer);
void state0(Map *map);
void state1(Map *map);
void state2(Map *map);
void state3(Map *map, Point p);
void state4(Map *map);
void state5(Map *map);
void state6(Map *map);
void state7(Map *map);
void state8(Map *map);
void state9(Map *map);
void state10(Map *map, Point p);
void state11(Map *map, int cnd);
void stateWin(Map *map);
void stateLose(Map *map);


#endif
