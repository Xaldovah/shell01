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
	int i;

	if (tokens[1] == NULL) /* No arguments passed to exit */
	{
		free(tokens);
		free(line);
		exit(0);
	}
	for (i = 0; tokens[1][i] != '\0'; i++)
	{
		if (!isdigit(tokens[1][i]))
		{
			char *msg1 = "exit: ";
			char *msg2 = ": numeric argument required\n";

			write(STDOUT_FILENO, msg1, strlen(msg1));
			write(STDOUT_FILENO, tokens[1], strlen(tokens[1]));
			write(STDOUT_FILENO, msg2, strlen(msg2));
			free(tokens);
			free(line);
			return;
		}
	}
	status = atoi(tokens[1]);

	free(tokens);
	free(line);
	exit(status);
}
