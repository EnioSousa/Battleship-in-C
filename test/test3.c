#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#include <stdio.h>
#include <stdlib.h>

#define SEMAPHORE_KEY 69

void errorExit(char *str);

int semaid;

int main()
{
  if ( (semaid = semget(SEMAPHORE_KEY, 2, IPC_CREAT)) < 0 )
    errorExit("semget failure");

  for ( int i=0; i<2; i++ )
    {
      wait[i].sem_num = i;
      wait[i].sem_op = -1;
      wait[i].sem_flg = SEM_UNDO;

      signal[i].sem_num = i;
      signal[i].sem_op = 1;
      signal[i].sem_flg =SEM_UNDO;
    }



  return 0;
}

void errorExit(char *str)
{
  fprintf(stderr, "%s\n", str);
  exit(EXIT_FAILURE);
}
