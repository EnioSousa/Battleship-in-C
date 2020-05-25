#include "engine.h"

int main(int argc, char **argv)
{
  int seed = atoi(argv[2])==2 ? time(NULL) + 1250: time(NULL);
  srand(seed);

  signal(SIGINT, handle_sigint);

  bufferManagement();

  fd = atoi(argv[1]);

  Map *map = initiatePlayer();

  start(map, atoi(argv[2]));

  return 0;
}

void handle_sigint(int sig)
{
  printf("Caught signal %d. Stop and unlink has been done\n", sig);
  unlink(FIFO_FILE);
  close(fd);
  exit(EXIT_SUCCESS);
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  exit(EXIT_FAILURE);
}

int stringIsNumber(char *str)
{
  for( int i=0; str[i]!='\0'; i++ )
    if ( !isdigit(str[i]) )
      return 0;

  return 1;
}

void bufferManagement()
{
  buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  if ( buffer == NULL )
    reportAndExit("Memory alocation failed. main\n");
}

char *myReadLine(int file)
{
  int i=0, byteRead;

  do
    {
      byteRead = read(file, &buffer[i], 1);

      if ( byteRead < 0 )
	reportAndExit("Read failed. myReadLine()\n");

      if ( buffer[0]=='\n' || buffer[0]=='\0' )
	continue;

      i++;

    }while( byteRead > 0 && i<BUFFERSIZE-1 && buffer[i-1]!='\n' );

  if ( i==0 )
    reportAndExit("Someting wrong with myReadLine. myReadLine\n");

  buffer[i-1] = '\0';

  return buffer;
}

/* Altera esta função joão. Podes tambem alterar o tipo de retorno*/
Map *initiatePlayer()
{
  Map *map = newMap(10, initiateShip(10));
  insertRandom(map);

  display(map);

  return map;
}

void start(Map *map, int nPlayer)
{
  if ( nPlayer!=1 && nPlayer!=2 )
    reportAndExit("Player has to be 1 or 2. start()\n");

  state0(map);
}

void state0(Map *map)
{
  printf("Wait\n");

  if ( map->won )
    return stateWin(map);

  else if ( map->lost )
    return stateLose(map);

  if ( flock(fd, LOCK_EX) < 0 )
    reportAndExit("Failed to acquire the lock\n");

  myReadLine(fd);

  printf(">>>>>>>>>>>>>>%s<<<<<<<<<<<<<\n", buffer);

  state1(map);
}

void state1(Map *map)
{
  if ( strcmp("stdin", buffer)==0 )
    state2(map);

  else if ( strcmp("result", buffer)==0 )
    state5(map);

  else if ( strcmp("disparo", buffer)==0 )
    state9(map);

  else
    {
      printf(">>>%s<<<<", buffer);
      reportAndExit("Unknown type. state1()\n");
    }
}

/* Altera esta função para o programa não ler merda do utilizador.
   É importante isto tar a funcionar corretamente men!!!*/
void state2(Map *map)
{
  if ( map->won )
    return stateWin(map);

  else if ( map->lost )
    return stateLose(map);

  printf("Where to shoot?\n");

  /*Read point. Cetificate que ele não le merda*/
  scanf("%d %d", &last.x, &last.y);

  state3(map, last);
}

void state3(Map *map, Point p)
{
  snprintf(buffer, BUFFERSIZE, "disparo\n%d\n%d\n", p.x, p.y);

  write(fd, buffer, strlen(buffer));

  state4(map);
}

void state4(Map *map)
{
  if ( flock(fd, LOCK_UN) < 0 )
    reportAndExit("Failed to unlock the lock\n");

  state0(map);
}

void state5(Map *map)
{
  myReadLine(fd);

  if ( strcmp("hit", buffer)==0 )
    state6(map);

  else if ( strcmp("fail", buffer)==0 )
    state7(map);

  else
    {
      printf("%s ", buffer);
      reportAndExit("Unkown result type. state5()\n");
    }
}

void state6(Map *map)
{
  updateHistory(map, &last, 1);

  display(map);

  state2(map);
}

void state7(Map *map)
{
  updateHistory(map, &last, 0);

  display(map);

  state8(map);
}

void state8(Map *map)
{
  snprintf(buffer, BUFFERSIZE, "stdin\n");

  write(fd, buffer, strlen(buffer));

  state4(map);
}

void state9(Map *map)
{
  Point p;

  myReadLine(fd);

  if ( !stringIsNumber(buffer) )
    {
      printf("%s ", buffer);
      reportAndExit("Not a number. state9()\n");
    }

  p.x = atoi(buffer);

  myReadLine(fd);

  if ( !stringIsNumber(buffer) )
    {
      printf("%s ", buffer);
      reportAndExit("Not a number. state9()\n");
    }

  p.y = atoi(buffer);

  state10(map, p);
}

void state10(Map *map, Point p)
{
  int cnd = shoot(map, &p);

  display(map);

  state11(map, cnd);
}

void state11(Map *map, int cnd)
{
  snprintf(buffer, BUFFERSIZE, "result\n%s", cnd==1 ? "hit\n": "fail\n");

  write(fd, buffer, strlen(buffer));

  state4(map);
}

void stateWin(Map *map)
{
  printf("You won\n");
}

void stateLose(Map *map)
{
  printf("You lost\n");
}
