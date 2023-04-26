#include "shell.h"

/**
 * check_path - Check if a command exists in the PATH
 * @cmd: The command to check
 *
 * Return: The full path of the command if it exists, or NULL if not found
 */
char *check_path(char *cmd)
{
	char *path = getenv("PATH"), *dir = NULL, *fullpath = NULL;
	struct stat st;

	if (!path)
		exit(EXIT_FAILURE);

	dir = strtok(path, ":");
	while (dir)
	{
		fullpath = _strcat(dir, "/");
		fullpath = _strcat(fullpath, cmd);
		if (stat(fullpath, &st) == 0)
			exit(EXIT_SUCCESS);
		free(fullpath);
		dir = strtok(NULL, ":");
	}

	exit(EXIT_FAILURE);
}
