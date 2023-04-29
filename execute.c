#include "shell.h"

/**
 * concatenate_path - ...
 * @pathname: ...
 * @name: ...
 *
 * Return: ...
 */
char *concatenate_path(char *pathname, char *name)
{
	int program_len = 0, path_length = 0, size = 0;

	program_len = strlen(name);
	path_length = strlen(pathname);
	size = sizeof(char) * (path_length + program_len + 2);
	pathname = realloc(pathname, size);
	if (!pathname)
		return (NULL);

	strcat(pathname, "/");
	strcat(pathname, name);
	pathname[path_length + program_len + 1] = '\0';

	return (pathname);
}

/**
 * find_cmd - ...
 * @command: cmd to find
 *
 * Return: Path name or NULL
 */
char *find_cmd(char *command)
{
	char *environ_path = NULL, *u_token = NULL, *del = ":", *token = NULL;
	struct stat st;

	if (command)
	{
		if (stat(command, &st) != 0 && command[0] != '/')
		{
			environ_path = getenv("PATH");
			if (environ_path == NULL) /* Add null check */
				return (NULL);
			u_token = strtok(environ_path, del);
			while (u_token)
			{
				token = concatenate_path(u_token, command);
				if (stat(token, &st) == 0)
				{
					free(command);
					command = strdup(token);
					free(token);
					free(environ_path);
					return (command);
				}
				free(token);
				u_token = strtok(NULL, del);
			}
			free(environ_path);
		}
		if (stat(command, &st) == 0)
			return (command);
	}
	free(command);
	return (NULL);
}


/**
  * exec_cmd - ...
  * @cmd: ...
  * @args: ...
  *
  * Return: An int
  */
int exec_cmd(char *cmd, char **args)
{
	pid_t child;
	int status;

	switch (child = fork())
	{
		case -1:
			perror("fork");
			return (-1);
		case 0:
			execve(cmd, args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		default:
			do {
				status = waitpid(child, &status, WUNTRACED);
				if (status == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			} while (WIFEXITED(status) == 0 && WIFSIGNALED(status) == 0);
	}
	return (0);
}
