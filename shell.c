#include "shell.h"
/**
 * main - Entry point for the shell
 * @argc: Unused param
 * @argv: Array...
 *
 * Return: 0.
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *lnptr = NULL, *lnptr_copy = NULL, *token;
	const char *delim = " \n";
	size_t n = 0;
	ssize_t nchars_read;
	int num_tokens = 0, i;

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT) + 1);
		nchars_read = getline(&lnptr, &n, stdin);
		if (nchars_read == -1)
		{
			write(STDOUT_FILENO, "Exiting shell....\n", 18);
			return (-1);
		}
		lnptr_copy = malloc(sizeof(char) * nchars_read);
		if (lnptr_copy == NULL)
		{
			perror("hsh: memory allocation error");
			return (-1);
		}
		strcpy(lnptr_copy, lnptr);
		token = strtok(lnptr, delim);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;
		argv = malloc(sizeof(char *) * num_tokens);
		token = strtok(lnptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		execmd(argv);
	}
	free(lnptr), free(lnptr_copy), free(argv);
	return (0);
}
