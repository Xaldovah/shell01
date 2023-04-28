#include "shell.h"

/**
 * _print_environ - This function prints the current env.
 *
 * Return: Does not return.
 */
void _print_environ(void)
{
	int i = 0, j = 0;

	while (environ[i])
	{
		j = 0;
		while (environ[i][j])
		{
			write(STDOUT_FILENO, &environ[i][j], 1);
			j++;
		}
		if (j != 0)
			write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
