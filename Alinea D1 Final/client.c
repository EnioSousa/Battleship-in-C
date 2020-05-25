#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 6969

#define BUFFERSIZE 1024
char *buffer;

int sock;

char **fArg;

void reportAndExit(char *str);
void bufferManagement();
void sockManagement(char *ip);

int main(int argc, char **argv)
{
  bufferManagement();

  if ( argc != 2 )
    reportAndExit("argv errado. main\n");

  sockManagement(argv[1]);

  pid_t pid = forK();

  if ( pid < 0 )
    reportAndExit("Failed to fork. main\n");

  if ( pid > 0 )
    {
      if ( waitpid(pid) < 0 )
	reportAndExit("Failed to catch son exit. main\n");
    }

  else
    {
      argumentManager(argc, argv);
    }

  return 0;
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s", str);
  exit(EXIT_FAILURE);
}

void bufferManagement()
{
  buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  if ( buffer == NULL )
    reportAndExit("Memory alocation failed. bufferManagement\n");
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

  /* Teste de funcionamento*/
  strcpy(buffer, "Hello from client\n\0");
  write(sock, buffer, BUFFERSIZE);
  read(sock, buffer, BUFFERSIZE);
  printf("Client: %s\n", buffer);
}

void argumentManagement(int argc, char **argv)
{
  fArg = (char **)calloc(5, sizeof(char *));

  if ( fArg == NULL )
    reportAndExit("Memory alocation failed. argumentManagement\n");

  for( int i=0; i<5; i++ )
    fArg[i] = newCharArray(128);

  strncpy(argv[1], "main");
  strncpy(argv[1], "main");
  strncpy(argv[1], "main");
  strncpy(argv[1], "main");
}

char *newCharArray(int n)
{
  char *temp = (char *)calloc(n, sizeof(char));

  if ( temp == NULL )
    reportAndExit("Memory alocation failed. newCharArray\n");

  return temp;
}
