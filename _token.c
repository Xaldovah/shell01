#include "shell.h"

/**
  * tokenize_cmdline - ...
  * @str: ...
  * @del: ...
  * @num:
  *
  * Return: array of args or NULL
  */
char **tokenize_cmdline(char *str, char *del, int num)
{
	char **args = NULL, *token = NULL, *temp = NULL;
	int arg_count = 0;

	args = malloc(sizeof(char *) * (num + 1));
	if (!args)
	{
		return (NULL);
	}
	str = del_ln(str);
	temp = strdup(str);
	token = strtok(temp, del);
	while (token)
	{
		args[arg_count] = strdup(token);
		token = strtok(NULL, token);
		arg_count++;
	}
	args[arg_count] = NULL;
	free(temp);
	return (args);
}
