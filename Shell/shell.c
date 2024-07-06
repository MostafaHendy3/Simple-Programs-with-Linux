#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
void Linetokenizer(char *line, char **tokens);
void CommandExecuter(char **tokens);
int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./wish [batch.txt]\n");
        return 1;
    }
    if (argc == 2)
    {
        // Batch mode to be implemented
        // printf("Batch mode\n");
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Error: Couldn't open file\n");
            return -1;
        }
        else
        {
            printf("File opened\n");
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            // get delim
            int delim = '\n';
            while ((read = getdelim(&line, &len, delim, file)) != -1)
            {
                // printf("Retrieved line of length %zu :\n", read);
                // printf("%s", line);
                line[read - 1] = '\0';
                // printf("%s", line);
                pid_t f = fork();
                if (f == 0)
                {
                    char *str = strtok(line, " ");
                    char *arg = strtok(NULL, "\n");
                    char *args[] = {str, arg, NULL};
                    printf("%s\n", str);
                    // printf("args is %s\n", args[0]);
                    char *envp[] = {NULL};
                    // printf("----------------\n");
                    int returnFormExecve = execve(str, args, envp);
                    if (returnFormExecve == -1)
                    {
                        free(line);
                        printf("Couldn't Run Program\n");
                        return -1;
                    }
                    
                }
                else if (f > 0)
                {
                    int status;
                    wait(&status);
                }
                else
                {
                    free(line);
                    printf("Error: Fork failed\n");
                    return -1;
                }
            }
            exit(0);
        }
    }

    while (1)
    {
        printf("Wish> ");
        char *command;
        size_t n = 0;
        int returnFromGetline = getline(&command, &n, stdin);
        // error checking
        if (returnFromGetline == -1)
        {
            free(command);
            printf("Error: Couldn't read command\n");
            return -1;
        }
        else if (strcmp(command, "\n") == 0)
        {
            free(command);
            continue;
        }
        strtok(command, "\n");
        // printf("Command is %s\n", command);
        if (strcmp(command, "exit") == 0)
        {
            free(command);
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
                char *envp[] = {NULL};
                int returnFormExecve = execve(str, args, envp);
                if (returnFormExecve == -1)
                {
                    free(command);
                    printf("Couldn't Run Program\n");
                    return -1;
                }
            }
            else if (f > 0)
            {
                // printf("this is parent\n");
                int status;
                wait(&status);
            }
            else
            {
                free(command);
                printf("Error: Fork failed\n");
                return -1;
            }
        }
    }
}
