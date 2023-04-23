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
		printf(PROMPT);
		fflush(stdout);
<<<<<<< HEAD:shell.c

		if (fgets(input, MAX_INPUT, stdin) == NULL)
=======
		if (getline(&input, &input_size, stdin) == -1)
>>>>>>> cd8e2033817997627548c4f97d73ccfe9b0c2fc2:Simple_shell_0.1.c
		{
			write(STDOUT_FILENO, "\n", 1);
			free(input);
			exit(EXIT_FAILURE);
		}
		input[strcspn(input, "\n")] = '\0';
		pid = fork();
<<<<<<< HEAD:shell.c

=======
>>>>>>> cd8e2033817997627548c4f97d73ccfe9b0c2fc2:Simple_shell_0.1.c
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
<<<<<<< HEAD:shell.c

		if (pid == 0)
=======
		else if (pid == 0)
>>>>>>> cd8e2033817997627548c4f97d73ccfe9b0c2fc2:Simple_shell_0.1.c
		{
			char *args[2] = { NULL };

			args[0] = input;
<<<<<<< HEAD:shell.c
			if (execve(input, args, environ) < 0)
=======
			if (execve(args[0], args, NULL) < 0)
>>>>>>> cd8e2033817997627548c4f97d73ccfe9b0c2fc2:Simple_shell_0.1.c
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

