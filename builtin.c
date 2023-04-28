#include "shell.h"

/**
 * builtin - This function executes built in cmds
 * @tokens: ...
 * @ln: ...
 *
 * Return: EXIT_SUCCESS (1 or 0)
 */
int builtin(char **tokens, char *ln)
{
	int j, i = 0;
	char *listcommands[] = { "exit", "cd", "env", "echo", NULL };

	while (listcommands[i])
	{
		if (_strcmp(tokens[0], listcommands[i]) == 0)
		{
			switch (i)
			{
				case 0:
					handle_exit(tokens, ln);
					break;
				case 1:
					chdir(tokens[1]);
					return (1);
				case 2:
					_print_environ();
					return (1);
				case 3:
					j = 1;

					while (tokens[j])
					{
						write(STDOUT_FILENO, tokens[j], _strlen(tokens[j]));
						write(STDOUT_FILENO, " ", 1);
						j++;
					}
					write(STDOUT_FILENO, "\n", 1);
					return (1);

				default:
					break;
			}
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}
