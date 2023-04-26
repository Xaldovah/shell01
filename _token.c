/**
  * tokenize_cmdline - Tokenize a command line into arguments
  * @cmdline: The command line to tokenize
  *
  * Return: An array of arguments or NULL if failed to allocate memory
  */
char **tokenize_cmdline(char *cmdline)
{
	char **args = NULL;
	char *token = NULL;
	int arg_count = 0;

	/* Count the number of arguments in the command line */
	for (int i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == ' ')
		{
			arg_count++;
			while (cmdline[i] == ' ')
				i++;
		}
	}
	arg_count++; /* Account for the last argument */

	/* Allocate memory for the arguments */
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);

	/* Tokenize the command line */
	token = strtok(cmdline, " ");
	for (int i = 0; token != NULL; i++)
	{
		args[i] = _strdup(token);
		token = strtok(NULL, " ");
	}

	/* Set the last argument to NULL */
	args[arg_count] = NULL;

	return (args);
}

