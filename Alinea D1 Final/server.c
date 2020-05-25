#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 6969

#define BUFFERSIZE 1024
char *buffer;

int serverFd, newSocket;

void reportAndExit(char *str);
void bufferManagement();
void sockManagement();

int main(int argc, char **argv)
{
  bufferManagement();

  sockManagement();

  close(sock);
  close(newSock);

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

void sockManagement()
{
  serverFd = socket(AF_INET, SOCK_STREAM, 0);

  if ( serverFd < 0 )
    reportAndExit("socket failed. main\n");

  /* Definir as opções*/
  int true = 1;
  if ( setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &true, sizeof(true)) < 0 )
    reportAndExit("setsockopt failed. main\n");

  struct sockaddr_in address;
  bzero((char *)&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if ( bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0 )
    reportAndExit("bind failed. main\n");

  /* Espera por uma ligação*/
  if ( listen(serverFd, 1) < 0 )
    reportAndExit("listen failed. main\n");

  /* ver api do accept para perceberes o porque de criar addressSize*/
  int addressSize = sizeof(address);

  newSocket = accept(serverFd, (struct sockaddr *)&address,(socklen_t *)&addressSize);

  if ( newSocket < 0 )
    reportAndExit("accept failed. main\n");

  /* Teste*/
  read(newSocket, buffer, BUFFERSIZE-1);
  printf("Server: %s\n", buffer);
  strcpy(buffer, "Hello from server\n");
  write(newSocket, buffer,strlen(buffer));
}
