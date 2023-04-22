#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - This program runs a simple shell.
 *
 * Return: Always 0.
 */

#define MAX_INPUT 1024
#define PROMPT ">"

extern char **environ;

int main()
{
	pid_t pid;
	char input[MAX_INPUT];
	int status;

	while(1)
	{
		printf(PROMPT);
		fflush(stdout);

		if(fgets(input, MAX_INPUT, stdin) == NULL)
		{
			printf("\n");
			exit(EXIT_FAILURE);
		}

		input[strcspn(input, "\n")] = '\0';

		pid = fork();

		if(pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if(pid == 0)
		{
			char *args[2] = { NULL };
			args[0] = input;
			if(execve(input, args, environ) < 0)
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

	return (0);
}

