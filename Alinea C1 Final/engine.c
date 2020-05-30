#include "engine.h"

int main(int argc, char **argv)
{
  signal(SIGINT, handler_sigint);

  fileManagement(argc, argv);

  bufferManagement();

  menuStar();

  semaphoreManagement(argv, getMapSize());

  /* Existe a possibilidade de ambos os jogadores entrarem
     ao mesmo tempo e ambos ficarem com a mesma semente
     dai a ter um bias para cada jogador*/
  srand(time(NULL) + (atoi(argv[1])==1 ? 123: 789) );

  Player *p = initiate(agreedMapSize());

  start(p, atoi(argv[1]));

  /* Fechar semaforo. Se por alguma razão o programa não fechou
     fazer: $ipcrm sem "semaphore id"*/
  semctl(semaid, 0, IPC_RMID, 0);

  return 0;
}

/**/
void handler_sigint(int sig)
{
  printf("Caught signal %d. Left safely.\n", sig);

  semctl(semaid, 0, IPC_RMID, 0);

  exit(EXIT_SUCCESS);
}
/**/
void reportAndExit(char *str)
{
  printf("\n%s\nLeft safely.", str);

  semctl(semaid, 0, IPC_RMID, 0);

  exit(EXIT_FAILURE);
}

/**/
void fileManagement(int argc, char **argv)
{
  if ( argc != 2 || !stringIsNumber(argv[1]) )
    reportAndExit("Passing wrong arguments to main. fileManagement()\n");

  /* Definir onde ler e onde escrever.*/
  rd = atoi(argv[1]) == 1 ? 0 : 1;
  wr = rd == 0 ? 1 : 0;

  /* Abrir os ficheiros para ler e escrever.*/
  if (atoi(argv[1]) == 1)
  {
    fd[rd] = open("player1.txt", O_RDONLY | O_CREAT, 0666);
    fd[wr] = open("player2.txt", O_WRONLY | O_CREAT, 0666);

    if (fd[rd] < 0 || fd[wr] < 0)
      reportAndExit("Failed to open. main\n");
  }

  else if (atoi(argv[1]) == 2)
  {
    fd[rd] = open("player2.txt", O_RDONLY | O_CREAT, 0666);
    fd[wr] = open("player1.txt", O_WRONLY | O_CREAT, 0666);

    if (fd[rd] < 0 || fd[wr] < 0)
      reportAndExit("Failed to open. main\n");
  }

  else
    reportAndExit("Something wrong with argv[1]. main\n");
}

/**/
void semaphoreManagement(char **argv, int mapSize)
{
  /* Criar semaforo */
  semaid = semget(SEMKEY, 2, IPC_CREAT | 0600);

  if (semaid < 0)
    reportAndExit("Failed to get semaphore\n");

  /* Definir que player fica com que semaforo */
  if ( !stringIsNumber(argv[1]) )
    reportAndExit("Passing wrong arguments to main\n");

  int tp = atoi(argv[1]);

  you = tp == 1 ? 0 : 1;
  him = you == 0 ? 1 : 0;

  /* Iniciar o semaforo */
  union semun arg;
  ushort arr[2];

  /* Ambos os jogadores vão querer jogar primeiro*/
  if ( tp == 1 )
    {
      arr[0] = 1;
      arr[1] = 0;
    }
  else
    {
      arr[0] = 0;
      arr[1] = 1;
    }

  arg.array = arr;

  /* Nesta condição iremos ver quem foi o ultimo
     a mexer no semaro com key SEMKEY.
     Caso o pid seja diferente de 0 então sabemos
     que algum processo criou e inicou o semaforo,
     portanto este processo não pode mexer neste
     semaforo. Fazemos isto para não haver
     corrupção dos valores iniciais e para ver
     quem joga primeiro*/
  if ( semctl(semaid, 0, GETPID) == 0 )
    {
      if (semctl(semaid, 0, SETALL, arg) < 0)
	reportAndExit("Set semaphore error. main\n");

      /* Apaga o conteudo dos files*/
      fclose(fopen("player1.txt", "w"));
      fclose(fopen("player2.txt", "w"));

      /* Temos que escrever o tamanho do mapa e quem
	 inicia o jogo nos ficheiros correpondentes
	 onde os programas iram ler.*/
      int tFirst = open(tp==1 ? "player1.txt": "player2.txt", O_WRONLY | O_CREAT, 0666);
      int tSecond = open(tp==1 ? "player2.txt": "player1.txt", O_WRONLY | O_CREAT, 0666);

      if ( snprintf(buffer, BUFFERSIZE, "%2d\nstdin\n", mapSize) <= 0 )
	reportAndExit("Failed to snprintf. pipemanagement()\n");

      if ( write(tFirst, buffer, strlen(buffer)) <= 0)
	reportAndExit("Failed to write in tempFd. pipeManagement()\n");

      if ( snprintf(buffer, BUFFERSIZE, "%2d\n", mapSize) <= 0 )
	reportAndExit("Failed to snprintf. pipemanagement()\n");

      if ( write(tSecond, buffer, strlen(buffer)) <= 0)
	reportAndExit("Failed to write in tempFd. pipeManagement()\n");

      close(tFirst);
      close(tSecond);
    }

  /* Meter o cursor de escrever no lugar direito*/
  lseek(fd[wr], 0, SEEK_END);

  /* Definir como mudar de jogador e quando é que se pode jogar*/
  for (int i = 0; i < 2; i++)
  {
    changePlayer[i].sem_num = i;
    changePlayer[i].sem_flg = SEM_UNDO;

    youPlay[i].sem_num = i;
    youPlay[i].sem_flg = SEM_UNDO;
  }

  youPlay[you].sem_op = -1;
  changePlayer[you].sem_op = 0;

  youPlay[him].sem_op = 0;
  changePlayer[him].sem_op = 1;
}

/**/
int agreedMapSize()
{
  if ( !stringIsNumber(myReadLine(fd[rd])) )
    reportAndExit("Failed to print the map size on the file. agreedMapSize()\n");

  return atoi(buffer);
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
  if ( nPlayer != 1 && nPlayer != 2 )
    reportAndExit("Player has to be 1 or 2. start()\n");

  state0(p);
}

void state0(Player *p)
{
  printf("Wait\n");

  /* Test if you can play*/
  semop(semaid, youPlay, 2);

  /* Onwards its critical*/
  if (p->map->won)
    return stateWin(p);

  else if (p->map->lost)
    return stateLose(p);

  myReadLine(fd[rd]);

  state1(p);
}

void state1(Player *p)
{
  if (strcmp("stdin", buffer) == 0)
    state2(p);

  else if (strcmp("result", buffer) == 0)
    state5(p);

  else if (strcmp("disparo", buffer) == 0)
    state9(p);

  else
  {
    printf(">>>>>>%s<<<<<<", buffer);
    reportAndExit("Unknown type. state1()\n");
  }
}

void state2(Player *p)
{
  int cycle = 1;

  if (p->map->won)
    return stateWin(p);

  else if (p->map->lost)
    return stateLose(p);

  while ( cycle )
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

void state3(Player *pt, Point p)
{
  snprintf(buffer, BUFFERSIZE, "disparo\n%d\n%d\n", p.x, p.y);

  write(fd[wr], buffer, strlen(buffer));

  state4(pt);
}

void state4(Player *p)
{
  if (semop(semaid, changePlayer, 2) < 0)
    reportAndExit("Failed to change Player. state4()\n");

  state0(p);
}

void state5(Player *p)
{
  myReadLine(fd[rd]);

  if (strcmp("hit", buffer) == 0)
    state6(p);

  else if (strcmp("fail", buffer) == 0)
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

  clearTerminal();
  display(p->map);

  state2(p);
}

void state7(Player *p)
{
  updateHistory(p->map, &last, 0);

  clearTerminal();
  display(p->map);

  state8(p);
}

void state8(Player *p)
{
  snprintf(buffer, BUFFERSIZE, "stdin\n");

  write(fd[wr], buffer, strlen(buffer));

  state4(p);
}

void state9(Player *pt)
{
  Point p;

  myReadLine(fd[rd]);

  if (!stringIsNumber(buffer))
  {
    printf("%s ", buffer);
    reportAndExit("Not a number. state9()\n");
  }

  p.x = atoi(buffer);

  myReadLine(fd[rd]);

  if (!stringIsNumber(buffer))
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

  clearTerminal();
  display(pt->map);

  state11(pt, cnd);
}

void state11(Player *p, int cnd)
{
  snprintf(buffer, BUFFERSIZE, "result\n%s", cnd == 1 ? "hit\n" : "fail\n");

  write(fd[wr], buffer, strlen(buffer));

  state4(p);
}

void stateWin(Player *p)
{
  winMeme();
  printf("You won\n");
  inicGame(p->name, 2);

  semop(semaid, changePlayer, 2);
}

void stateLose(Player *p)
{
  printf("You lost\n");
  inicGame(p->name, 1);

  semop(semaid, changePlayer, 2);
}
