#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <sys/wait.h>

#define TRUE 1
#define MAX_STRING_SIZE 5000
#define MAX_WORD_SIZE 200
#define MAX_ARGS_QUANTITY 30

void type_prompt();
void Read_Command(char **command, char *args[MAX_ARGS_QUANTITY]);

int main(int argc, char const *argv[])
{
    char *command = NULL, *args[MAX_ARGS_QUANTITY];
    int status, pid;

    while(TRUE)
    {
        type_prompt();
        Read_Command(&command, args);
        pid = fork();
        
        if (pid != 0) {
            waitpid(-1, &status, 0);
        }
        else
        {
            execve(command, args, 0);
            printf("%s\n", strerror(errno));
            command = NULL;
        }
    }

    return 0;
}

void type_prompt()
{
    system("clear");
    printf("\nUser:~$ ");
}

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
