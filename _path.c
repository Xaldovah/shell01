#include "shell.h"

/**
 * check_path - Check if a command exists in the PATH
 * @cmd: The command to check
 *
 * Return: The full path of the command if it exists, or NULL if not found
 */
char *check_path(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		cmd_len = strlen(cmd);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			file_path = malloc(cmd_len + dir_len + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				exit(EXIT_FAILURE);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);

		if (stat(cmd, &buffer) == 0)
		{
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}
