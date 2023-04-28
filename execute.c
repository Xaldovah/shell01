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

	return (pathname);
}

/**
  * find_cmd - ...
  * @nomb: ...
  *
  * Return: Path name or NULL
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
				u_tokens[i] = concatenate_path(u_tokens[i], nomb);

				if (stat(u_tokens[i], &st) == 0)
				{
					free(nomb);
					nomb = strdup(u_tokens[i]);
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
			do {
				waitpid(child, &prog, WUNTRACED);
			} while (WIFEXITED(prog) == 0 && WIFSIGNALED(prog) == 0);
	}
	return (0);
}
