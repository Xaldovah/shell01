#include "shell.h"

/**
  * del_ln - ...
  * @str: ...
  *
  * Return: string sino new line
  */
char *del_ln(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}

	return (str);
}
