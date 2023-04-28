#include "shell.h"

/**
<<<<<<< HEAD
  * concatenate_path - Concatenate a path name and a program name
  * @pathname: The path name to concatenate with the program name
  * @name: The prog name
  *
  * Return: The path name concatenated with the program name
=======
  * concatenate_path - ...
  * @pathname: ...
  * @name: ...
  *
  * Return: ...
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
  */
char *concatenate_path(char *pathname, char *name)
{
	int program_len = 0, path_length = 0, size = 0;

	program_len = _strlen(name);
	path_length = _strlen(pathname);
	size = sizeof(char) * (path_length + program_len + 2);
	pathname = _realloc(pathname, (path_length + 1), size);
	if (!pathname)
		return (NULL);

	_strcat(pathname, "/");
	_strcat(pathname, name);

	return (pathname);
}

/**
<<<<<<< HEAD
  * find_cmd - Function to check if command is found
  * @nomb: The command name to find
  *
  * Return: Path name or NULL if failed
=======
  * find_cmd - ...
  * @nomb: ...
  *
  * Return: Path name or NULL
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
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
<<<<<<< HEAD
			environ_path = _getenv("PATH");
=======
			environ_path = getenv("PATH");
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
			num = count_del(environ_path, ":") + 1;
			u_tokens = tokenize(environ_path, ":", num);

			while (u_tokens[i])
			{
				u_tokens[i] = concatenate_path(u_tokens[i], nomb);

				if (stat(u_tokens[i], &st) == 0)
				{
					free(nomb);
<<<<<<< HEAD
					nomb = _strdup(u_tokens[i]);
=======
					nomb = strdup(u_tokens[i]);
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
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
