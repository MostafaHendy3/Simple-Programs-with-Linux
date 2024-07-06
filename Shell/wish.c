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

    /**
     * BATCH MODE
     */
    if (argc == 2)
    {
        // Batch mode to be implemented
        printf("Batch mode\n");
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
                line[read - 1] = '\0';
                pid_t f = fork();
                if (f == 0)
                {
                    char *str = strtok(line, " ");
                    char *arg = strtok(NULL, "\n");
                    char *args[] = {str, arg, NULL};
                    if (strcmp(line, "\n") == 0)
                    {
                        free(line);
                        continue;
                    }
                   
                    if (strcmp(line, "exit") == 0)
                    {
                        free(line);
                        break;
                    }
                    // printf("----------------\n");
                    execlp(str, str, arg, NULL);
                    char *err = "An error has occurred\n";
                    write(2, err, strlen(err));
                    return -1;
                }
                else if (f > 0)
                {
                    int status;
                    wait(&status);
                    // printf("%d\n", status);
                }
                else
                {
                    free(line);
                    // printf("Error: Fork failed\n");
                    return -1;
                }
            }
            exit(0);
        }
    }
    /**
     * INTERACTIVE MODE
     */

    while (1)
    {
        // interactive MODE
        printf("Wish> ");
        char *command;
        size_t n = 0;
        int returnFromGetline = getline(&command, &n, stdin);
        if (returnFromGetline == -1)
        {
            free(command);
            return -1;
        }
        else if (strcmp(command, "\n") == 0)
        {
            free(command);
            continue;
        }
        // Got the Whole Line
        strtok(command, "\n"); // strtok to remove the newline character
        // check If Exit is entered
        if (strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        }
        else
        {
            // normal command
            char *args[] = {NULL};
            pid_t f = fork();
            if (f == 0)
            {
                char *str = strtok(command, " ");
                char *arg = strtok(NULL, "\n");
                char *envp[] = {NULL};
                //use execlp
                execlp(str, str, arg, NULL);
                free(command);
            }
            else if (f > 0)
            {
                int status;
                wait(&status);
            }
            else
            {
                free(command);
                return -1;
            }
        }
    }
}
