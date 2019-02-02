#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 5000
#define MAX_WORD_SIZE 200
#define MAX_ARGS_QUANTITY 30

void Read_Command(char **command, char *args[MAX_ARGS_QUANTITY])
{
  char string[MAX_STRING_SIZE+1], buffer[MAX_WORD_SIZE+1];
  fgets(string, MAX_STRING_SIZE+1, stdin);
  
  if(string[0] == '\n')
  {
    printf("Empty String.\n");
    exit(1);
  }
  string[strlen(string) - 1] = '\0';

  //filling buffer
  int i = 0, j = 0, flag = 0, arg = 0; //i for string, j for buffer, 
  while(i < MAX_STRING_SIZE)
  {
    buffer[j] = string[i];
    if(j == MAX_WORD_SIZE+1)
    {
      printf("Argument in position %d too long.\n", arg);
      exit(2);
    }

    if(!flag) //assigning command
    {
      if( (buffer[j] == ' ') || (buffer[j] == '\0') )
      {
        if(buffer[j] == ' ')
        {
          buffer[j] = '\0';
        }
        j = -1;
        *command = (char*) malloc(sizeof(buffer));
        strcpy(*command, buffer);

        flag++;
        arg++;

        if(string[i] == '\0')
        {
          break;
        }
      }
    }
    else  //assigning arguments
    {
      if( (buffer[j] == ' ') || (buffer[j] == '\0') )
      {
        if(buffer[j] == ' ')
        {
          buffer[j] = '\0';
        }
        j = -1;
        args[arg-1] = (char*) malloc(sizeof(buffer));
        strcpy(args[arg-1], buffer);

        flag++;
        arg++;

        if(string[i] == '\0')
        {
          break;
        }
      }
    }

    j++;
    i++;
  }
  args[arg-1] = NULL;

}

int main(void) {
  char *command = NULL, *args[MAX_ARGS_QUANTITY];
  Read_Command(&command, args);

  return 0;
}
