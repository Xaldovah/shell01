#include "shell.h"
/**
 * execmd - execute command
 */
void execmd(char **argv)
{
	char *cmd = NULL, *a_cmd = NULL;

	if (argv)
	{
		cmd = argv[0];
		a_cmd = check_path(cmd);
		if (execve(a_cmd, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
