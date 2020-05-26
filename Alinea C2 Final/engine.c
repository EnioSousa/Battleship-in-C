#include "engine.h"
#include "input.h"
#include "interface.h"


int main(int argc, char **argv)
{
  signal(SIGINT, handle_sigint);

  pipeManagement();

  bufferManagement();

  int size = atoi(argv[2]);
  menuStar();
  Player *p = initiate(size);
  
  start(p, atoi(argv[1]));

  close(fd);
  unlink(FIFO_FILE);

  return 0;
}

void handle_sigint(int sig)
{
  printf("Caught signal %d. Stop and unlink has been done\n", sig);
  unlink(FIFO_FILE);
  close(fd);
  exit(EXIT_SUCCESS);
}


/* Basicamente o primeiro a criar o FIFO_FILE tambem
   sera responsavel por escrever stdin. Na nossa
   estrutura quem le stdin, ira ler do std input.
   Com esta estrutura ambos os player 1 e 2 podem
   ser os primeiros a jogar, ira depender de quem
   criar o FIFO_FILE Primeiro.*/
void pipeManagement()
{
  int initiateFifo = 0;

  if ( mkfifo(FIFO_FILE, S_IFIFO | 0666) >= 0 )
    initiateFifo = 1;

  fd = open(FIFO_FILE, O_RDWR);

  if ( fd < 0 )
    reportAndExit("Error on opening fifo. pipeManagement()\n");

  if ( initiateFifo )
    {
      flock(fd, LOCK_EX);
      write(fd, "stdin\n", 6);
      flock(fd, LOCK_UN);
    }
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  unlink(FIFO_FILE);
  close(fd);
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

  return buffer;
}

/* Altera esta função joão. Podes tambem alterar o tipo de retorno*/
Player *initiate(int size)
{
  char *name = getName();
  srand(time(NULL));
  Ship *s = initiateShip(size);
  inicGame(name, 0);
  waitS(0);
  printAllShip(s);
  waitS(0);
  Map *map = newMap(size, s);
  Player *p = initiatePlayer(name, map);
  printf(ANSI_COLOR_GREEN "If you want to insert Manual press y, if you want Random press any key\n" ANSI_COLOR_RESET);
  char ch = getchar();
  getchar();
  if (ch == 'y')
  {
    insertManual(p->map);
  }
  else
  {
    insertRandom(p->map);
  }
  clearTerminal();
  display(p->map);

  return p;
}

void start(Player *p, int nPlayer)
{
  if ( nPlayer!=1 && nPlayer!=2 )
    reportAndExit("Player has to be 1 or 2. start()\n");

  state0(p);
}

void state0(Player *p)
{
  printf("Wait\n");

  if ( p->map->won )
    return stateWin(p);

  else if ( p->map->lost )
    return stateLose(p);

  if ( flock(fd, LOCK_EX) < 0 )
    reportAndExit("Failed to acquire the lock\n");

  myReadLine(fd);

  state1(p);
}

void state1(Player *p)
{
  if ( strcmp("stdin", buffer)==0 )
    state2(p);

  else if ( strcmp("result", buffer)==0 )
    state5(p);

  else if ( strcmp("disparo", buffer)==0 )
    state9(p);

  else
    {
      printf(">>>%s<<<<", buffer);
      reportAndExit("Unknown type. state1()\n");
    }
}

/* Altera esta função para o programa não ler merda do utilizador.
   É importante isto tar a funcionar corretamente men!!!*/
void state2(Player *p)
{
  int cycle = 1;
  if (p->map->won)
    return stateWin(p);

  else if (p->map->lost)
    return stateLose(p);

  while (cycle)
  {
    cycle = 0;
    printf("Where to shoot?\n");
    printf("X coordinate\n");
    last.x = inputCheck();
    printf("Y coordinate\n");
    last.y = inputCheck();
    if (last.x > p->map->mapSize || last.y > p->map->mapSize || last.x <= 0 || last.y <= 0)
    {
      printf(ANSI_COLOR_RED "Coordinates goes beyond the battlefield\n\n" ANSI_COLOR_RESET);
      cycle = 1;
    }
  }
  clearTerminal();
  state3(p, last);
  
  
}

void state3(Player *m, Point p)
{
  snprintf(buffer, BUFFERSIZE, "disparo\n%d\n%d\n", p.x, p.y);

  write(fd, buffer, strlen(buffer));

  state4(m);
}

void state4(Player *p)
{
  if ( flock(fd, LOCK_UN) < 0 )
    reportAndExit("Failed to unlock the lock\n");


  /* É preciso parar este processo, para certificarmos que o outro
     processo, pede uma chave exclusiva ao FIFO_FILE. Basicamente
     estamos a dizer ao kernel: agora para este processo e ve se
     tens outros processos a espera de executar, caso afirmativo
     ele ira correr o outro processo, e o outro processo
     encontra-se num estado em que esta a espera ou ira pedir uma
     chave exclusiva. Com este sleep consiguimos uma cominicação
     sem corrupção */
  sleep(1);

  state0(p);
}

void state5(Player *p)
{
  myReadLine(fd);

  if ( strcmp("hit", buffer)==0 )
    state6(p);

  else if ( strcmp("fail", buffer)==0 )
    state7(p);

  else
    {
      printf("%s ", buffer);
      reportAndExit("Unkown result type. state5()\n");
    }
}

void state6(Player *p)
{
  updateHistory(p->map, &last, 1);

  display(p->map);

  state2(p);
}

void state7(Player *p)
{
  updateHistory(p->map, &last, 0);

  display(p->map);

  state8(p);
}

void state8(Player *p)
{
  snprintf(buffer, BUFFERSIZE, "stdin\n");

  write(fd, buffer, strlen(buffer));

  state4(p);
}

void state9(Player *pt)
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

  state10(pt, p);
}

void state10(Player *pt, Point p)
{
  int cnd = shoot(pt->map, &p);

 
  display(pt->map);
  state11(pt, cnd);
}

void state11(Player *p, int cnd)
{
  snprintf(buffer, BUFFERSIZE, "result\n%s", cnd==1 ? "hit\n": "fail\n");

  write(fd, buffer, strlen(buffer));

  state4(p);
}

void stateWin(Player *p)
{
  winMeme();
  printf("You won\n");
  inicGame(p->name, 2);
}

void stateLose(Player *p)
{
  
  inicGame(p->name, 1);
  printf("You lost\n");
}
