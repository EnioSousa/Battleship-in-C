#include "engine.h"

int main(int argc, char **argv)
{
  if ( argc<3 && !stringIsNumber(argv[1]) )
    reportAndExit("Wrong arguments in main. main\n");

  signal(SIGINT, handle_sigint);

  bufferManagement();

  fd = atoi(argv[1]); // sock id

  menuStar();

  int size = agreedMapSize(atoi(argv[2])); // argv[2] -> Player number, 1 or 2

  /* Existe a possibilidade de ambos os jogadores entrarem
     ao mesmo tempo e ambos ficarem com a mesma semente
     dai a ter um bias para cada jogador*/
  srand(time(NULL) + (atoi(argv[2])==1 ? 123: 789) );

  Player *p = initiate(size);

  start(p, atoi(argv[2]));

  close(fd);

  return 0;
}

void handle_sigint(int sig)
{
  printf("Caught signal %d. Safe Exit done\n", sig);

  unlink(FIFO_FILE);
  close(fd);

  exit(EXIT_SUCCESS);
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  close(fd);
  exit(EXIT_FAILURE);
}

/* Função que sincroniza o tamanho dos mapas*/
int agreedMapSize(int p)
{
  /* Busca o tamanho do mapa proposto pelo jogador*/
  int size = getMapSize();

  /* Guarda o tempo de chegada a esta linha*/
  time_t timeOfDecision = time(NULL);

  /* Escreve o tempo de decição e o tamanho que o jogador quer*/
  snprintf(buffer, BUFFERSIZE, "%ld\n%d\n", timeOfDecision, size);
  write(fd, buffer, strlen(buffer));

  /* Le o tempo de decição do outro jogador*/
  if ( !stringIsNumber(myReadLine(fd)) )
    reportAndExit("Bad sincronization. agreedMapSize()\n");

  /* Converte o tempo de decição para um long*/
  time_t otherTimeOfDecision = atoll(buffer);

  /* Le o tamanho que o outro jogador propos*/
  int otherSize = atoi(myReadLine(fd));

  /* Ve quem chegou primeiro e faz decisão baseado nisso*/
  if ( timeOfDecision < otherTimeOfDecision || ( timeOfDecision == otherTimeOfDecision && p == 1 ) )
    return size;

  /* O outro jogador é que decidio o tamanho do mapa então
     vamos dizer a ele para começar a jogar*/
  else
    {
      write(fd, "stdin\n", 6);
      return otherSize;
    }
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

/* Com sockets a passagem de jogador é bastante facil,
   decidimos manter o state4 para manter o "contexto"
   que ja vem das alineas C*/
void state4(Player *p)
{
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
