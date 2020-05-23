#include "engine.h"

int main(int argc, char **argv)
{
  fileManagement(argc, argv);

  semaphoreManagement(argc, argv);

  bufferManagement();

  Map *map = initiatePlayer();

  start(map, atoi(argv[1]));

  /* Fechar semaforo. Se por alguma razão o programa não fechou
     fazer: $ipcrm sem "semaphore id"*/
  semctl (semaid, 0, IPC_RMID, 0);

  return 0;
}

void reportAndExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  semctl (semaid, 0, IPC_RMID, 0);
  exit(EXIT_FAILURE);
}

void fileManagement(int argc, char **argv)
{
  if ( argc!=2 || !stringIsNumber(argv[1]) )
    reportAndExit("Passing wrong arguments to main\n");

  /* Definir onde ler e onde escrever*/
  rd = atoi(argv[1])==1 ? 0: 1;
  wr = rd == 0 ? 1: 0;

  /* Apaga o conteudo dos files*/
  fclose(fopen("player1.txt", "w"));
  fclose(fopen("player2.txt", "w"));

  /* Abrir os ficheiros para ler e escrever.*/
  if ( atoi(argv[1])==1 )
    {
      fd[rd] = open("player1.txt", O_RDONLY | O_CREAT, 0666);
      fd[wr] = open("player2.txt", O_WRONLY | O_CREAT, 0666);

      if ( fd[rd] < 0 || fd[wr] < 0 )
	reportAndExit("Failed to open. main\n");
    }

  else if ( atoi(argv[1])==2 )
    {
      fd[rd] = open("player2.txt", O_RDONLY | O_CREAT, 0666);
      fd[wr] = open("player1.txt", O_WRONLY | O_CREAT, 0666);

      if ( fd[rd] < 0 || fd[wr] < 0 )
	reportAndExit("Failed to open. main\n");
    }

  else
    reportAndExit("Something wrong with argv[1]. main\n");
}

int stringIsNumber(char *str)
{
  for( int i=0; str[i]!='\0'; i++ )
    if ( !isdigit(str[i]) )
      return 0;

  return 1;
}

void semaphoreManagement(int argc, char **argv)
{
  /* create semaphore */
  semaid = semget(SEMKEY, 2, IPC_CREAT | 0600);

  if ( semaid < 0 )
    reportAndExit("Failed to get semaphore\n");

  if ( argc!=2 || !stringIsNumber(argv[1]) )
    reportAndExit("Passing wrong arguments to main\n");

  /* definir que player fica com que semaforo */
  you = atoi(argv[1])==1 ? 0: 1;
  him = you==0 ? 1: 0;

  /* Iniciar o semaforo */
  union semun arg;
  ushort arr[2];
  arr[0] = 1;
  arr[1] = 0;
  arg.array = arr;

  /* Basicamente estamos a ver se foi este o processo que
     criou o semaforo ou o kernel. Caso afirmativo, iniciamos.
     Fazemos isto para não haver "corrupção" dos valores
     inicias do semafro*/
  int lastChange = semctl(semaid, 0, GETPID);

  if ( lastChange==0 || lastChange==getpid() )
    if ( semctl(semaid, 0, SETALL, arg) < 0 )
      reportAndExit("Set semaphore error. main\n");

  /* Definir como mudar de jogador e quando é que se pode jogar*/
  for( int i=0; i<2; i++ )
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

  /* Player1 escreve. Para certificar que temos algo para ler*/
  if ( nPlayer==1 )
    {
      int temp = open("player1.txt", O_WRONLY | O_CREAT, 0666);

      write(temp, "stdin\n", 6);

      close(temp);
    }
  /* Player 2 escreve. Para sinconizar o cursor caso palyer 1 tenha
     escrito alguma coisa*/
  else
    write(fd[wr], "stdin\n", 6);

  state0(map);
}

void state0(Map *map)
{
  printf("Wait\n");

  /* Test if you can play*/
  semop(semaid, youPlay, 2);

  /* Onwards its critical*/
  if ( map->won )
    return stateWin(map);

  else if ( map->lost )
    return stateLose(map);

  myReadLine(fd[rd]);

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
      printf("%s", buffer);
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

  write(fd[wr], buffer, strlen(buffer));

  state4(map);
}

void state4(Map *map)
{
  if ( semop(semaid, changePlayer, 2) < 0 )
    reportAndExit("Failed to change Player. state4()\n");

  state0(map);
}

void state5(Map *map)
{
  myReadLine(fd[rd]);

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

  write(fd[wr], buffer, strlen(buffer));

  state4(map);
}

void state9(Map *map)
{
  Point p;

  myReadLine(fd[rd]);

  if ( !stringIsNumber(buffer) )
    {
      printf("%s ", buffer);
      reportAndExit("Not a number. state9()\n");
    }

  p.x = atoi(buffer);

  myReadLine(fd[rd]);

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

  write(fd[wr], buffer, strlen(buffer));

  state4(map);
}

void stateWin(Map *map)
{
  printf("You won\n");

  semop(semaid, changePlayer, 2);
}

void stateLose(Map *map)
{
  printf("You lost\n");

  semop(semaid, changePlayer, 2);
}
