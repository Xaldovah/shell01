#include "shell.h"

/**
  * frees_first - ...
  * @thing: ...
  *
  * Return: ...
  */
void frees_first(char *thing)
{
	int a;

	for (a = 4; a >= 0; a--)
		thing--;

	free(thing);
}

/**
  * frees_second - ...
  * @tokens: ...
  * 
  * Return: ...
  */
void frees_second(char **tokens)
{
	char **temp = tokens;

	if (tokens)
	{
		while (*tokens)
			free(*tokens++);

		free(temp);
	}
}
