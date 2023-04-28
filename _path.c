#include "shell.h"

/**
 * check_path - Check if a cmd exists
 * @cmd: cmd to check
 *
 * Return: ...
 */
char *check_path(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		if (!path_copy)
			return (NULL);

		cmd_len = strlen(cmd);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			file_path = malloc(cmd_len + dir_len + 2);
			if (!file_path)
			{
				free(path_copy);
				return (NULL);
			}

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
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
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}
