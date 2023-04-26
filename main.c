#include "shell.h"

/**
 * main - This function prints the shell 
 *
 * Return: Success.
 */

int main(void)
{
        pid_t pid;
        char *input = NULL, *path = NULL;
        size_t input_size = 0;
        int status;

        while (1)
        {
                write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
                if (getline(&input, &input_size, stdin) == -1)
                {
                        write(STDOUT_FILENO, "\n", 1);
                        free(input);
                        exit(EXIT_FAILURE);
                }
                input[strcspn(input, "\n")] = '\0';

                // Handle exit built-in
                if (strcmp(input, "exit") == 0)
                {
                        free(input);
                        exit(EXIT_SUCCESS);
                }

                // Handle env built-in
                if (strcmp(input, "env") == 0)
                {
                        char **env = NULL;
                        int i;

                        for (i = 0; environ[i] != NULL; i++)
                        {
                                write(STDOUT_FILENO, environ[i], strlen(environ[i]));
                                write(STDOUT_FILENO, "\n", 1);
                        }
                        continue;
                }

                // Get the PATH environment variable
                path = _getenv("PATH");

                // Tokenize the command line
                char **args = tokenize_cmdline(input);

                // Search for the command in the directories listed in PATH
                char *dir, *cmd;
                int found = 0;
                while ((dir = strtok_r(path, ":", &path)) != NULL)
                {
                        cmd = malloc(strlen(dir) + strlen(args[0]) + 2);
                        sprintf(cmd, "%s/%s", dir, args[0]);

                        if (access(cmd, X_OK) == 0)
                        {
                                found = 1;
                                break;
                        }

                        free(cmd);
                }

                // If the command wasn't found, print an error message and continue
                if (!found)
                {
                        write(STDERR_FILENO, "Command not found\n", 18);
                        free(args);
                        continue;
                }

                // Execute the command
                pid = fork();
                if (pid < 0)
                {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                        if (execve(cmd, args, environ) < 0)
                        {
                                perror("execve");
                                exit(EXIT_FAILURE);
                        }
                }
                else
                {
                        wait(&status);
                }

                free(args);
                free(cmd);
        }

        free(input);
        exit(EXIT_SUCCESS);
}
