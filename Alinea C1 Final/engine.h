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
#include "player.h"

#include <time.h>
#include <signal.h>

/* Estrutura usada para iniciar o semaforo
   val -> Usado apenas por SETVAL
   buf -> Usado por IPC_STAT e IPC_SET
   array -> Usado por GETALL e SETALL*/
union semun {
  int val;
  struct semid_ds *buf;
  ushort *array;
};

/* SEMKEY -> É usado pelo programa para criar ou buscar o semaforO
             associado ao SEMKEY
   semaid -> Usado para representar o semaforo. Quando um semaforo
             é criado ou "buscado" ele retora um indentificador para
             posteriormente podermos usar
   you -> Representa o semaforo que este processo vai "usar"
   him -> Representa o semaforo que o outro processo vai "usar"*/
#define SEMKEY 69
int semaid, you, him;

/* BUFFERSIZE -> Tamanho maximo do buffer.
   buffer -> Uma string que vai ser usada como "buffer" temporario
   antes de escrevermos nos files*/
#define BUFFERSIZE 1024
char *buffer;

/* fd -> Descritor dos ficheiros aberto pelo programa.
   rd -> Possição em fd[], onde podemos apenas ler
   wr -> Possição em fd[], onde podeos apenas escrever*/
int fd[2];
int rd, wr;

/* Last point shot*/
Point last;

struct sembuf changePlayer[2], youPlay[2];

/* Esta função é reponsavel por gerir o sinal sigint. Isto porque
   os semaphoros são da gestão do kernel e precisamos de avisar que
   queremos remover o semaforo antes de sairmos abrutamente do programa.*/
void handler_sigint(int sig);

/* Função repora e faz exit caso haja algum erro. Atenção o
   programador é que fica responsavel de chamar esta função,
   ela so serve para o programador saber onde esta a falhar.*/
void reportAndExit(char *str);

/* Esta função abre dois ficheiros, um de escrita e um de leitura.
   Os programas sabem se são o jogador 1 ou 2 e iremos abrir os
   ficheiros de maneira a que o jogador 1 apenas escreva em
   player2.txt e apenas leia player1.txt e o jogador 2 apenas escreve
   em player1.txt e leia em player.2txt*/
void fileManagement(int argc, char **argv);

/* Retorna 1 caso a string seja um numero, 0 caso contrario*/
int stringIsNumber(char *str);

/* Nesta função é criada toda a mecada de semaforos*/
void semaphoreManagement(int argc, char **argv);

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
Player *initiate(int size);

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
