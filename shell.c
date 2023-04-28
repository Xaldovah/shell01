#include "shell.h"
/**
 * main - Entry point for the shell
 * @argc: Number of arguments
 * @argv: Array...
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char *prompt = "shell$ ";
	char *lnptr = NULL, *lnptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	(void)argc;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lnptr, &n, stdin);
		if (nchars_read == -1)
		{
			printf("Exiting shell....\n");
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
	}
	free(lnptr_copy);
	free(lnptr);
	return (0);
}
