#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./wish [batch.txt]\n");
        return 1;
    }
    if (argc == 2)
    {
    }
    while (1)
    {
        printf("Wish> ");
        char *command;
        size_t n = 0;
        getline(&command, &n, stdin);
        if (strcmp(command, "\n") == 0)
        {
            continue;
        }
        strtok(command, "\n");
        // printf("Command is %s\n", command);
        if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            char *args[] = {NULL};
            pid_t f = fork();
            if (f == 0)
            {
                char *str = strtok(command, " ");
                char *arg = strtok(NULL, "\n");
                char *args[] = {str, arg, NULL};
                printf("%s\n", str);
                // printf("args is %s\n", args[0]);
                char * envp[] = {NULL};
                execve(str, args, envp);

            }
            else if (f > 0)
            {
                // printf("this is parent\n");
                int status;
                wait(&status);
            }
        }
    }
}
