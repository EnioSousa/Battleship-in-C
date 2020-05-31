#include "input.h"

/* Funções do enio*/

/**/
void bufferManagement()
{
  buffer = (char *)calloc(BUFFERSIZE, sizeof(char));

  if ( buffer == NULL )
    reportAndExit("Memory alocation failed. main\n");
}

/**/
char *myReadLine(int file)
{
  int i = 0, byteRead;

  do
  {
    byteRead = read(file, &buffer[i], 1);

    if ( byteRead < 0 )
      reportAndExit("Read failed. myReadLine()\n");

    if ( buffer[0] == '\n'|| buffer[0] == '\0' )
      i--;

    i++;

  } while ( readContinue(buffer, BUFFERSIZE, i) );

  return terminateString(file, buffer, i);
}

/**/
int readContinue(char *str, int size, int ind)
{
  if ( ind==0 && ind<size )
    return 1;

  if ( str[0]=='\n' || str[0]=='\0' || str[0]==EOF )
    return 1;

  if ( buffer[ind-1]!='\n' && buffer[ind-1]!='\0' && buffer[ind-1]!=EOF )
    return 1;

  return 0;
}

/**/
char *terminateString(int file, char *str, int ind)
{
  if ( ind==0 )
    reportAndExit("Error, invalid index. TerminateString()\n");

  /* Significa que o utilizador deu uma linha que não cabe
     no nosso buffer, i.e esta a haver um buffer
     overflow atack. Resolvemos ao ignorar o resto.*/
  if ( str[ind-1]!='\n' && str[ind-1]!='\0' && str[ind-1]!=EOF )
    for( char lixo; read(file, &lixo, 1) > 0 && lixo != '\n'; );

  str[ind-1] = '\0';

  return str;
}

/**/
char *getName()
{
  printf(ANSI_COLOR_RED "Your name please \n" ANSI_COLOR_RESET);

  myReadLine(STDIN_FILENO);

  char *temp = (char *)calloc(strlen(buffer)+1, sizeof(char));

  if ( temp==NULL )
    reportAndExit("Failed to alocate memory. enioGetName()\n");

  return strncpy(temp, buffer, strlen(buffer)+1);
}

/**/
int inputCheckInt(int file, char *str)
{
  int cnd = 1;

  while ( cnd )
    {
      if ( str[0] != '\0' )
	printf("%s", str);

      myReadLine(file);

      if ( !stringIsNumber(buffer) )
	printf("Entered input is not a number\n");

      else
	cnd = 0;
    }

  return atoi(buffer);
}

/**/
char inputCheckChar(int file, char *str)
{
  int cnd = 1;

  while ( cnd )
    {
      if ( str[0] != '\0' )
	printf("%s", str);

      myReadLine(file);

      if ( !isalpha(buffer[0]) || strlen(buffer) != 1 )
	printf("Entered input is not a char\n");

      else
	cnd = 0;
    }

  return buffer[0];
}

/**/
int getMapSize()
{
  int size = 0;

  while ( !size )
    {
      printf("Enter map size. Size should be between 20 and 40.\n");

      myReadLine(STDIN_FILENO);

      size = stringIsNumber(buffer)!=0 ? atoi(buffer): 0;

      size = size >= 10 && size <= 40 ? size: 0;
    }

  return size;
}

/**/
int stringIsNumber(char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
    if (!isdigit(str[i]))
      return 0;

  return 1;
}
