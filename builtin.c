#include "shell.h"

/**
 * builtin - This function executes built in cmds
 * @tokens: An array of strings containing the tokens
 * @ln: A string containing the user input
 *
 * Return: 0
 */
int builtin(char **tokens, char *ln)
{
	int i = 0, j;
	char *listcommands[] = { "exit", "cd", "env", "echo", NULL };

	while (listcommands[i])
	{
		if (strcmp(tokens[0], listcommands[i]) == 0)
		{
			switch (i)
			{
				case 0:
					handle_exit(tokens, ln);
					break;
				case 1:
					if (tokens[1] == NULL)
					{
						fprintf(stderr, "cd: no argument provided\n");
						return (1);
					}
					chdir(tokens[1]);
					return (1);
				case 2:
					_print_environ();
					return (1);
				case 3:
					j = 1;
					while (tokens[j])
					{
						write(STDOUT_FILENO, tokens[j], strlen(tokens[j]));
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
	return (0);
}
