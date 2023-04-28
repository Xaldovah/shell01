#include "shell.h"

/**
  * tokenize_cmdline - ...
  * @cmdline: ...
  *
  * Return: array of args or NULL
  */
char **tokenize_cmdline(char *cmdline)
{
	char **args = NULL, *token = NULL, *temp = NULL;
	int arg_count = 0, i;

	for (i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == ' ')
		{
			arg_count++;
			while (cmdline[i] == ' ')

			i++;
		}
	}
	arg_count++; /* Account for the last argument */

	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		return (NULL);
	}
	temp = strdup(cmdline);
	if (!temp)
	{
		free(args);
		return (NULL);
	}
	token = strtok(temp, " ");
	for (i = 0; token != NULL; i++)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			free(args);
			return (NULL);
		}
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	free(temp);
	return (args);
}
