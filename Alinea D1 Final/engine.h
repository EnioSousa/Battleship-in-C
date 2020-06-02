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
#include "player.h"

#include "ship.h"
#include "interface.h"
#include "insert.h"

#include <time.h>
#include <sys/file.h>
#include <signal.h>

#include "input.h"
#include "interface.h"
#include <sys/types.h>

#include <sys/socket.h>


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

/* Nesta funções os jogadores vão decidir o tamanho do mapa.
   Basicamente ambos têm que introduzir um tamanho valido
   e sera escolhido aquele que introduzir primeiro.
   Caso tenham introduzido ao mesmo tempo, desempatamos
   escolhendo o tamanho que o player 1 introduzio*/
int agreedMapSize(int p);

/* Retorna o player*/
Player* initiate(int size);

/* Funções stateX por favor ver o automato em anexo. Basicamente
   eles são o ciclo logico de execução. Ver o automato pois é
   bastante facil de perceber*/
void start(Player *p, int nPlayer);
void state0(Player *p);
void state1(Player *p);
void state2(Player *p);
void state3(Player *p, Point po);
void state4(Player *p);
void state5(Player *p);
void state6(Player *p);
void state7(Player *p);
void state8(Player *p);
void state9(Player *p);
void state10(Player *p, Point po);
void state11(Player *p, int cnd);
void stateWin(Player *p);
void stateLose(Player *p);

#endif
