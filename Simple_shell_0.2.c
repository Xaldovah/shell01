#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "shell$ "
/**
 * main - Handle command lines with arguments
 *
 * Return: void
 */
int main(void)
{
	char *cmd = NULL, *cmd_cpy = NULL, *token = NULL;
	char *delim = " \n";
	size_t n = 0;
	int argc = 0, i = 0;
	char **argv = NULL;

	while(1)
	{
		write(STDOUT_FILENO, PROMPT, 7);
		
		if (getline(&cmd, &n, stdin) == -1)
		{
			exit(EXIT_FAILURE);
		}
		cmd_cpy = strdup(cmd);
		token = strtok(cmd, delim);

		while (token)
		{
			token = strtok(NULL, delim);
			argc++;
		}
		printf("%d\n", argc);

		argv = malloc(sizeof(char *) * argc);

		token = strtok(cmd_cpy, delim);
		while (token)
		{
			argv[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		argv[i] = NULL;

		free(cmd);
		free(argv);
	}

	exit(EXIT_SUCCESS);
}
