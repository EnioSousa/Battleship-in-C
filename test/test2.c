#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#include <stdio.h>
#include <stdlib.h>

#define SEMAPHORE_KEY 69


void errorExit(char *str);

int semaid;

union semun
{
  int val; /* Ysed for SETVAL only*/
  struct semid_ds *buf; /* For IPC_STAT and IPC_SET */
  ushort *array; /* Used for GETALL and SETALL*/
};

struct sembuf wait[2], signal[2];

int main(int argc, char **argv)
{

  if ( (semaid = semget(SEMAPHORE_KEY, 2, IPC_CREAT | IPC_EXCL)) < 0)
    errorExit("semget failure");

  union semun arg;
  ushort arr[2];
  arr[0] = 1;
  arr[1] = 0;
  arg.array = arr;

  semctl(semaid, 0, SETALL, arg);

  for ( int i=0; i<2; i++ )
    {
      wait[i].sem_num = i;
      wait[i].sem_op = -1;
      wait[i].sem_flg = SEM_UNDO;

      signal[i].sem_num = i;
      signal[i].sem_op = 1;
      signal[i].sem_flg =SEM_UNDO;
    }



  semctl(semaid, 0, IPC_RMID, 0);

  return 0;
}

void errorExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  exit(EXIT_FAILURE);
}
