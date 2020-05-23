#include "engine.h"
#include "input.h"
#include "interface.h"
#

int main(int argc, char **argv)
{
  fileManagement(argc, argv);
  semaphoreManagement(argc, argv);
  bufferManagement();
  int size = atoi(argv[2]);
  menuStar();
  Player *p = initiate(size);

  start(p, atoi(argv[1]));

  /* Fechar semaforo. Se por alguma razão o programa não fechou
     fazer: $ipcrm sem "semaphore id"*/
  semctl(semaid, 0, IPC_RMID, 0);

  return 0;
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  semctl(semaid, 0, IPC_RMID, 0);
  exit(EXIT_FAILURE);
}

void fileManagement(int argc, char **argv)
{
  if (argc != 3 || (!stringIsNumber(argv[1]) && !stringIsNumber(argv[2])))
    reportAndExit("Passing wrong arguments to main  \n");

  /* Definir onde ler e onde escrever*/
  rd = atoi(argv[1]) == 1 ? 0 : 1;
  wr = rd == 0 ? 1 : 0;

  /* Apaga o conteudo dos files*/
  fclose(fopen("player1.txt", "w"));
  fclose(fopen("player2.txt", "w"));

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

int stringIsNumber(char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
    if (!isdigit(str[i]))
      return 0;

  return 1;
}

void semaphoreManagement(int argc, char **argv)
{
  /* create semaphore */
  semaid = semget(SEMKEY, 2, IPC_CREAT | 0600);

  if (semaid < 0)
    reportAndExit("Failed to get semaphore\n");

  /* definir que player fica com que semaforo */
  if (argc != 3 || !stringIsNumber(argv[1]))
    reportAndExit("Passing wrong arguments to main\n");

  you = atoi(argv[1]) == 1 ? 0 : 1;
  him = you == 0 ? 1 : 0;

  /* Iniciar o semaforo */
  union semun arg;
  ushort arr[2];
  arr[0] = 1;
  arr[1] = 0;
  arg.array = arr;

  //printf("%d\n", semctl(semaid, 0, GETPID));
  //printf("%d\n", getpid());

  /* Basicamente estamos a ver se foi este o processo que
     criou o semaforo. Caso afirmativo, iniciamos.
     Fazemos isto para não haver "corrupção" dos valores
     inicias do semafro*/
  int lastChange = semctl(semaid, 0, GETPID);

  if (lastChange == 0 || lastChange == getpid())
    if (semctl(semaid, 0, SETALL, arg) < 0)
      reportAndExit("Set semaphore error. main\n");

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

void bufferManagement()
{
  buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  if (buffer == NULL)
    reportAndExit("Memory alocation failed. main\n");
}

char *myReadLine(int file)
{
  int i = 0, byteRead;

  do
  {
    byteRead = read(file, &buffer[i], 1);

    if (byteRead < 0)
      reportAndExit("Read failed. myReadLine()\n");

    if (buffer[0] == '\n')
      continue;

    i++;

  } while (byteRead > 0 && i < BUFFERSIZE - 1 && buffer[i - 1] != '\n' && buffer[i - 1] != '\0');

  if (i == 0)
    reportAndExit("Someting wrong with myReadLine. myReadLine\n");

  buffer[i - 1] = '\0';

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
  if (nPlayer != 1 && nPlayer != 2)
    reportAndExit("Player has to be 1 or 2. start()\n");

  /* Player1 escreve. Para certificar que temos algo para ler*/
  if (nPlayer == 1)
  {
    int temp = open("player1.txt", O_WRONLY | O_CREAT, 0666);

    write(temp, "stdin\n", 6);

    close(temp);
  }
  /* Player 2 escreve. Para sinconizar o cursor caso palyer 1 tenha
     escrito alguma coisa*/
  else
    write(fd[wr], "stdin\n", 6);

  state0(p);
}

void state0(Player *p)
{
  printf("Wait\n");

  /* Test if you can play*/
  semop(semaid, youPlay, 2);

  if (p->map->won)
    return stateWin(p);

  else if (p->map->lost)
    return stateLose(p);

  /* Onwards its critical*/
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
    printf("%s===", buffer);
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
