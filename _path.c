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

	path = _getenv("PATH");

	if (path)
	{
		path_copy = _strdup(path);
		cmd_len = _strlen(cmd);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_len = _strlen(path_token);
			file_path = malloc(cmd_len + dir_len + 2);
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			_strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				free(file_path);
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
