#include "errorMessage.h"
#include <stdio.h>
#include <stdlib.h>

void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageOut(char *str, Point *p)
{
  fprintf(stderr, "Out of bounds in %s, (%d, %d)\n", str, p->x, p->y);
  exit(EXIT_FAILURE);
}

void errorMessageMap(char *str)
{
  fprintf(stderr, "Ship==NULL in %s\n", str);
  exit(EXIT_FAILURE);
}
