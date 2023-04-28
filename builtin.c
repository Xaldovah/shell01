#include "shell.h"

/**
 * builtin - This function executes built in cmds
 * @u_tokns: ...
 * @line: ...
 *
 * exit: EXIT_SUCCESS (1 or 0)
 */
int builtin(char **tokens, char *ln)
{
        int i = 0;
        char *listcommands[] = { "exit", "cd", "env", "echo", NULL };

        while (listcommands[i])
        {
                if (strcmp(tokens[0], listcommands[i]) == 0)
                {
                        switch (i)
                        {
                                case 0:
                                        _handle_exit(tokens, ln);
                                        break;
                                case 1:
                                        chdir(tokens[1]);
                                        return (1);
                                case 2:
                                        _print_env();
                                        return (1);
				case 3:
					int j = 1;
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
	exit(EXIT_SUCCESS);
}
