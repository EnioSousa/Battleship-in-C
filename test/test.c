#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>

union semun
{
  /* SUSv3 force definition in user programs */
  int val ;
  struct semid_ds *buf ;
  unsigned short *array ;
} ;

int main (int argc ,char **argv )
{
  int semid ;

  if( argc < 2 || argc > 3)
    {
      fprintf(stderr,"Usage : svsem_demo [ SEM_ID ] SEM_OP" ) ;
      exit(EXIT_FAILURE);
    }

  else if( argc == 2)
  {
    /* create & i n i t semaphore */
    union semun arg;

    if ( (semid = semget(IPC_PRIVATE, 1, S_IRUSR | S_IWUSR)) < 0 )
      {
	fprintf(stderr, "semid error");
	exit(EXIT_FAILURE);
      }

    arg.val = atoi(argv[1]);

    if ( semctl(semid, 0, SETVAL, arg) < 0 )
      {
	fprintf(stderr, "semctl error");
	exit(EXIT_FAILURE);
      }

    printf("semaphore ID = %d\n", semid);
  }

  else
    {
      struct sembuf sop;

      semid = atoi(argv[1]);
      sop.sem_num = 0;
      sop.sem_op = atoi(argv[2]);
      sop.sem_flg = 0;

      printf("%d: about to semip\n", getpid());

      if ( semop(semid, &sop, 1) < 0 )
	{
	  fprintf(stderr, "semop error\n");
	  exit(EXIT_FAILURE);
	}

      printf("%d: semop completed\n", getpid());

    }

  return 0;
}
