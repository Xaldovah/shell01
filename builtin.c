#include "shell.h"

/**
 * builtin - This function executes built in cmds
 * @tokens: ...
 * @ln: ...
 *
<<<<<<< HEAD
 * Return: EXIT_SUCCESS (1 or 0)
 */
int builtin(char **tokens, char *ln)
{
	int j, i = 0;
=======
 * Return: (1 or 0)
 */
int builtin(char **tokens, char *ln)
{
	int i = 0, j;
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
	char *listcommands[] = { "exit", "cd", "env", "echo", NULL };

	while (listcommands[i])
	{
<<<<<<< HEAD
		if (_strcmp(tokens[0], listcommands[i]) == 0)
=======
		if (strcmp(tokens[0], listcommands[i]) == 0)
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
		{
			switch (i)
			{
				case 0:
<<<<<<< HEAD
					handle_exit(tokens, ln);
=======
					_handle_exit(tokens, ln);
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
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
<<<<<<< HEAD
						write(STDOUT_FILENO, tokens[j], _strlen(tokens[j]));
=======
						write(STDOUT_FILENO, tokens[j], strlen(tokens[j]));
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
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
<<<<<<< HEAD
	exit(EXIT_SUCCESS);
=======
	return (0);
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
}
