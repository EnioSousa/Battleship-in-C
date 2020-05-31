#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#define PORT 6969

int sock;

char **fArg;

void reportAndExit(char *str);
void sockManagement(char *ip);

void argumentManagement(int argc, char **argv);
char *newCharArray(int n);

int main(int argc, char **argv)
{
  if ( argc != 2 )
    reportAndExit("argv errado. main\n");

  sockManagement(argv[1]);

  argumentManagement(argc, argv);

  pid_t pid = fork();

  if ( pid < 0 )
    reportAndExit("Failed to fork. main\n");

  else if ( pid > 0 )
    {
      if ( waitpid(pid, NULL, 0) < 0 )
	reportAndExit("Failed to catch son exit. main\n");
    }

  else
    {
      if ( execv("./main", fArg) < 0 )
	reportAndExit("Error on execv. main\n");
    }

  return 0;
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s", str);
  exit(EXIT_FAILURE);
}

void sockManagement(char *ip)
{
  /**/
  sock = socket(AF_INET, SOCK_STREAM, 0);

  if ( sock < 0 )
    reportAndExit("socket failed. main\n");

  /**/
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  /* Converter o ip, de texto para binario e meter
     na estrutura serv_addr, para posteriormente podermos
     formar uma ligação*/
  if ( inet_pton(AF_INET, ip, &serv_addr.sin_addr) < 0 )
    reportAndExit("inet_pton failed. main\n");

  /* Fazer conecção com o server */
  if ( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
    reportAndExit("connect failed. main\n");
}

void argumentManagement(int argc, char **argv)
{
  fArg = (char **)calloc(4, sizeof(char *));

  if ( fArg == NULL )
    reportAndExit("Memory alocation failed. argumentManagement\n");

  for( int i=0; i<4; i++ )
    fArg[i] = newCharArray(128);

  strcpy(fArg[0], "main");
  snprintf(fArg[1], 127, "%d", sock);
  strcpy(fArg[2], "2");
  fArg[3] = NULL;
}

char *newCharArray(int n)
{
  char *temp = (char *)calloc(n, sizeof(char));

  if ( temp == NULL )
    reportAndExit("Memory alocation failed. newCharArray\n");

  return temp;
}
