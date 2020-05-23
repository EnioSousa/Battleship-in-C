#include "engine.h"

int main(int argc, char **argv)
{
  pipeManagement();

  bufferManagement();

  Map *map = initiatePlayer();

  start(map, atoi(argv[1]));

  close(fd);
  unlink(FIFO_FILE);

  return 0;
}

void pipeManagement()
{
  mkfifo(FIFO_FILE, S_IFIFO | 0666);

  fd = open(FIFO_FILE, O_RDWR);

  if ( fd < 0 )
    reportAndExit("Error on opening fifo. pipeManagement()\n");
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  unlink(FIFO_FILE);
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

      if ( buffer[0]=='\n' )
	continue;

      i++;

    }while( byteRead > 0 && i<BUFFERSIZE-1 && buffer[i-1]!='\n' && buffer[i-1]!='\0');

  if ( i==0 )
    reportAndExit("Someting wrong with myReadLine. myReadLine\n");

  buffer[i-1] = '\0';

  printf(">>>>>>>>>%s<<<<<<<<<\n", buffer);

  return buffer;
}

/* Altera esta função joão. Podes tambem alterar o tipo de retorno*/
Map *initiatePlayer()
{
  srand(time(NULL));

  Map *map = newMap(10, initiateShip(10));
  insertRandom(map);

  display(map);

  return map;
}

void start(Map *map, int nPlayer)
{
  if ( nPlayer!=1 && nPlayer!=2 )
    reportAndExit("Player has to be 1 or 2. start()\n");

  if ( nPlayer==1 )
    write(fd, "stdin\n", 6);

  state0(map);
}

void state0(Map *map)
{
  printf("State 0\n");
  printf("Wait\n");

  if ( map->won )
    return stateWin(map);

  else if ( map->lost )
    return stateLose(map);

  if ( flock(fd, LOCK_EX) < 0 )
    reportAndExit("Failed to acquire the lock\n");

  myReadLine(fd);

  state1(map);
}

void state1(Map *map)
{
  printf("State 1\n");
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
  printf("State 2\n");
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
  printf("State 3\n");
  snprintf(buffer, BUFFERSIZE, "disparo\n%d\n%d\n", p.x, p.y);

  write(fd, buffer, strlen(buffer));

  state4(map);
}

void state4(Map *map)
{
  printf("State 4\n");
  if ( flock(fd, LOCK_UN) < 0 )
    reportAndExit("Failed to unlock the lock\n");

  state0(map);
}

void state5(Map *map)
{
  printf("State 5\n");
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
  printf("State 6\n");
  updateHistory(map, &last, 1);

  display(map);

  state2(map);
}

void state7(Map *map)
{
  printf("State 7\n");
  updateHistory(map, &last, 0);

  display(map);

  state8(map);
}

void state8(Map *map)
{
  printf("State 8\n");
  snprintf(buffer, BUFFERSIZE, "stdin\n");

  write(fd, buffer, strlen(buffer));

  state4(map);
}

void state9(Map *map)
{
  printf("State 9\n");
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
  printf("State 10\n");
  int cnd = shoot(map, &p);

  display(map);

  state11(map, cnd);
}

void state11(Map *map, int cnd)
{
  printf("State 11\n");
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
