#include "shell.h"

/**
  * concat_path - Concatenate a path name and a program name
  * @pathname: The path name to concatenate with the program name
  * @name: The prog name
  *
  * Return: The path name concatenated with the program name
  */
char *concatenate_path(char *pathname, char *name)
{
	int program_len = 0, path_length = 0, size = 0;

	program_len = strlen(name);
	path_length = strlen(pathname);
	size = sizeof(char) * (path_length + program_len + 2);
	pathname = _realloc(pathname, (path_length + 1), size);
	if (!pathname)
		return (NULL);

	strcat(pathname, "/");
	strcat(pathname, name);

	return (pathname);
}

/**
  * find_cmd - Function to check if command is found
  * @nomb: The command name to find
  *
  * Return: Path name or NULL if failed
  */
char *find_cmd(char *nomb)
{
	char *environ_path = NULL, **u_tokens = NULL;
	int i = 0, num = 0;
	struct stat st;

	if (nomb)
	{
		if (stat(nomb, &st) != 0 && nomb[0] != '/')
		{
			environ_path = getenv("PATH");
			num = count_del(environ_path, ":") + 1;
			u_tokens = tokenize(environ_path, ":", num);

			while (u_tokens[i])
			{
				u_tokns[i] = concatenate_path(u_tokens[i], nomb);

				if (stat(u_tokens[i], &st) == 0)
				{
					free(nomb);
					nomb = strdup(u_tokns[i]);
					free(environ_path);
					free(u_tokens);
					return (nomb);
				}
				i++;
			}
			free(environ_path);
			free(u_tokens);
		}
		if (stat(nomb, &st) == 0)
			return (nomb);
	}
	free(nomb);
	return (EXIT_FAILURE);
}

/**
  * exec_cmd - ...
  * @command: ...
  * @args: ...
  *
  * Return: An int
  */
int exec_cmd(char *cmd, char **args)
{
	pid_t child;
	int prog;

	switch (child = fork())
	{
		case 1:
			perror("fork");
			return (-1);
		case 0:
			execve(cmd, args, environ);
			break;
		default:
			do
			{
				waitpid(child, &prog, WUNTRACED);
			}
			while (WIFEXITED(status) == 0 && WIFSIGNALED(prog) == 0);
	}
	return (EXIT_SUCCESS);
}
