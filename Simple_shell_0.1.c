#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - This program runs a simple shell.
 *
 * Return: Always 0.
 */

#define MAX_INPUT 1024
#define PROMPT "shell$ "

int main(void)
{
	pid_t pid;
	char *input = NULL;
	size_t input_size = 0;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, 1);
		fflush(stdout);
		if (getline(&input, &input_size, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(input);
			exit(EXIT_FAILURE);
		}
		input[strcspn(input, "\n")] = '\0';
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *args[2] = { NULL };

			args[0] = input;
			if (execve(args[0], args, NULL) < 0)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(input);
	exit(EXIT_SUCCESS);
}

