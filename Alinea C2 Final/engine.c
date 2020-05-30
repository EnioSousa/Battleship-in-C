#include "engine.h"

int main(int argc, char **argv)
{
  if ( argc<2 && !stringIsNumber(argv[1]) )
    reportAndExit("Wrong arguments in main. main\n");

  signal(SIGINT, handle_sigint);

  sleepManagement();

  bufferManagement();

  menuStar();

  /* PipeManagement tambem retorna o tamanho do mapa a ser utilizado*/
  int size = pipeManagement(atoi(argv[1]), getMapSize());

  /* Existe a possibilidade de ambos os jogadores entrarem
     ao mesmo tempo e ambos ficarem com a mesma semente
     dai a ter um bias para cada jogador*/
  srand(time(NULL) + (atoi(argv[1])==1 ? 123: 789) );

  Player *p = initiate(size);

  start(p, atoi(argv[1]));

  close(fd);
  unlink(FIFO_FILE);

  return 0;
}

void handle_sigint(int sig)
{
  printf("Caught signal %d. Safe Exit done\n", sig);

  unlink(FIFO_FILE);
  close(fd);

  exit(EXIT_SUCCESS);
}

/* Basicamente o primeiro a criar o FIFO_FILE tambem
   sera responsavel por sincronizar o tamanho do mapa
   entre os jogadores e tambem será o primeiro a jogar*/
int pipeManagement(int p, int size)
{
  int initiateFifo = 0;

  /* Cria o fifo*/
  if ( mkfifo(FIFO_FILE, S_IFIFO | 0666) >= 0 )
    initiateFifo = 1;

  fd = open(FIFO_FILE, O_RDWR);

  if ( fd < 0 )
    reportAndExit("Error on opening fifo. pipeManagement()\n");

  /* Se este foi o programa que criou o fifo então executa
     agreedMapSize, que sincroniza o tamanho dos mapas*/
  if ( initiateFifo )
    return agreedMapSize(p, size);

  /* Caso contrario, tudo o que este processo tem que fazer é ler
     o tamanho do mapa que o outro jogador decidiu*/
  else
    {
      flock(fd, LOCK_EX);

      myReadLine(fd);

      if ( !stringIsNumber(buffer) )
	reportAndExit("Error on reading map size. pipeManagement()\n");

      write(fd, "play\nstdin\n", 11);

      flock(fd, LOCK_UN);

      /* Espera pelo o outro processo apanhar a chave exclusiva*/
      if ( nanosleep(&req, NULL) < 0 )
	reportAndExit("nanosleep failed. state4\n");

      return atoi(buffer);
    }
}

/* Basicamente, é este o processo que define o tamanho do mapa
   e agora vamos esperar que o outro processo veja a nossa mensagem.*/
int agreedMapSize(int p, int size)
{
  flock(fd, LOCK_EX);

  snprintf(buffer, BUFFERSIZE, "%d\n", size);

  write(fd, buffer, strlen(buffer));

  flock(fd, LOCK_UN);

  int cnd = 1;

  while ( cnd )
    {
      if ( nanosleep(&req, NULL) < 0 )
	reportAndExit("nanosleep failed. state4\n");

      flock(fd, LOCK_EX);

      myReadLine(fd);

      if ( strcmp(buffer, "play") != 0 )
	{
	  snprintf(buffer, BUFFERSIZE, "%d\n", size);

	  write(fd, buffer, strlen(buffer));

	  flock(fd, LOCK_UN);
	}

      /* Se chegar aqui, significa que o outro jogador
	 recebeu o tamanho do mapa, portanto poemos
	 sair do ciclo, MAS mantemos o lock do file,
	 para podermos ser os primeiros a jogar*/
      else
	cnd = 0;
    }

  return size;
}

void sleepManagement()
{
  req.tv_sec = 0;
  req.tv_nsec = 50 * 1000000; // 50 milesegundos
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  unlink(FIFO_FILE);
  close(fd);
  exit(EXIT_FAILURE);
}

/**/
Player *initiate(int size)
{
  char *name = getName();

  Ship *s = initiateShip(size);
  inicGame(name, 0);
  waitS(0);

  printAllShip(s);
  waitS(0);

  Map *map = newMap(size, s);
  Player *p = initiatePlayer(name, map);

  printf(ANSI_COLOR_GREEN "Press y for Manual, any key for Random.\n" ANSI_COLOR_RESET);

  myReadLine(STDIN_FILENO);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
    insertManual(p->map);

  else
    insertRandom(p->map);

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

  if ( flock(fd, LOCK_EX) < 0 )
    reportAndExit("Failed to acquire the lock\n");

  if ( p->map->won )
    return stateWin(p);

  else if ( p->map->lost )
    return stateLose(p);

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

      last.x = inputCheckInt(STDIN_FILENO, "X coordinate\n");

      last.y = inputCheckInt(STDIN_FILENO, "Y coordinate\n");


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
  if ( nanosleep(&req, NULL) < 0 )
    reportAndExit("nanosleep failed. state4\n");

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
