#include <stdio.h>
#include <stdlib.h>
/**
 * main - simple shell
 *
 * Return: void
 */
int main(void)
{
	char *prompt = ">";
	/*declare getline variables*/
	char *lineptr;
	size_t n = 0;
	/*declare exititing the shell vairiable*/
	ssize_t n_chars_read;

	while(1)
	{
		printf("%s\n", prompt);
		n_chars_read = getline(&lineptr, &n, stdin);

		if (n_chars_read == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}
		printf("%s\n", lineptr);

		/*getline allocates memory dinamically*/
		free(lineptr);
	}
	return (0);
}

