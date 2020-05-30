#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include "interface.h"

/* BUFFERSIZE -> Tamanho maximo do buffer.
   buffer -> Uma string que vai ser usada como "buffer" temporario
   antes de escrevermos nos files*/
#define BUFFERSIZE 1024
char *buffer;


/* Função cria espaço dinamicamente para um buffer intermedio que
   iremos usar antes de escrever em cada ficheiro.*/
void bufferManagement();

/* Função le uma linha do ficheiro file e mete num buffer. Esta
   função não le alem do tamanho maximo do buffer*/
char *myReadLine(int file);

/* As proximas duas funções não devem ser chamadas em
   lado nenhum. São funções auxiliares de myReadLine()*/

/* Condição testa se lemos uma linha ou se chegamos
   ao limite de espaço atribuido para str*/
int readContinue(char *str, int size, int ind);

/* Poe o caracter '\0' na possição ind-1 e faz um teste
   para ver se a string realmente contem uma linha. Se
   não conter uma linha i.e não contem '\n' em str
   então o input lido não cabe em str, podemos estar
   portanto sobre um ataque de buffer overflow.
   Percauções são tomadas para esse caso.*/
char *terminateString(int file, char *str, int ind);

/* Função busca do STDIN um nome e retorna o apontador
   para um array de char que o guarda.*/
char *getName();

/* Função le um inteiro do file e retorna o seu valor.
   São feitas verificações para ataques de buffer
   overflow e de input que não sejam numeros*/
int inputCheckInt(int file, char *str);

/* Função le uma linha de file e verifica se foi
   lido apenas um caracter (sem contar com \n).*/
char inputCheckChar(int file, char *str);

/* Retorna 1 caso a string seja um numero, 0 caso contrario*/
int stringIsNumber(char *str);

/* Busca o tamanho do map para o utilizador.*/
int getMapSize();

/* Este include não é engano. É suposto estar aqui =)*/
#include "engine.h"

#endif
