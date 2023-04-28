#include "shell.h"

/**
 * handle_exit - This function is responsible for handling exit
 * @tokens: checks arguments
 * @line: ...
 * Return: No return expected
 */

void handle_exit(char **tokens, char *line)
{
	int status = 0;

	if (tokens[1] == NULL || (!strcmp(tokens[1], "0")))
	{
		free(tokens);
		free(line);
		exit(0);
	}

	status = atoi(tokens[1]);

	if (status != 0)
	{
		free(tokens);
		free(line);
		exit(status);
	}
	else
	{
		char *msg1 = "exit: prohibited number: ";
		char *msg2 = "\n";

		write(STDOUT_FILENO, msg1, strlen(msg1));
		write(STDOUT_FILENO, tokens[1], strlen(tokens[1]));
		write(STDOUT_FILENO, msg2, strlen(msg2));
		free(tokens);
		free(line);
		exit(2);
	}
	free(tokens);
	free(line);
	exit(EXIT_SUCCESS);
}
