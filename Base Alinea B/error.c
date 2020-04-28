#include "error.h"

void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageOut(char *str)
{
  fprintf(stderr, "Out of bounds in %s\n", str);
  
  exit(EXIT_FAILURE);
}

void errorMessageMap(char *str)
{
  fprintf(stderr, "Ship==NULL in %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessagePointer(char *str)
{
  fprintf(stderr, "Tried to access a null pointer in %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageIllegalSize(char *str)
{
  fprintf(stderr, "Illegal size on %s\n",str);
  exit(EXIT_FAILURE);
}
