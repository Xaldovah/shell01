#include "shell.h"

#define MAX_ARGS 64
#define MAX_PATHS 64
#define MAX_PATH_LENGTH 256
#define PROMPT ":) "

/**
 * This function initializes the path array by parsing PATH environ variable.
 * It splits the string into individual paths and stores them in the path array
 */
void init_paths(void)
{
	char *path_var;
	char *path_str;
	int i = 0;
	char *path_token;

	path_var = getenv("PATH");
	if (path_var == NULL)
	{
		perror("PATH environment variable not found");
		exit(EXIT_FAILURE);
	}

	path_str = strdup(path_var);
	if (path_str == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	path_token = strtok(path_str, ":");
	while (path_token != NULL && i < MAX_PATHS - 1)
	{
		path[i++] = path_token;
		path_token = strtok(NULL, ":");
	}
	path[i] = NULL;
}

char *find_command(char *command)
{
	char path_buffer[MAX_PATH_LENGTH];
	int i;

	for (i = 0; path[i] != NULL; i++)
	{
		snprintf(path_buffer, MAX_PATH_LENGTH, "%s/%s", path[i], command);
		if (access(path_buffer, X_OK) == 0)
		{
			return (strdup(path_buffer)); /* make str cpy to avoid modifying original */
		}
	}
	exit(EXIT_FAILURE);
}

void parse_input(char *input, char *args[])
{
	int i = 0;
	char *token = NULL;

	token = strtok(input, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL; /* add a NULL pointer to mark the end of the array */
}

int main(void)
{
	char *input_buffer = NULL;
	char *args[MAX_ARGS];
	size_t buffer_size = 0;
	pid_t pid;
	int status;
	char *command;

	init_paths();

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		fflush(stdout);

		if (getline(&input_buffer, &buffer_size, stdin) == -1)
		{
			/* handle EOF or error */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		input_buffer[strcspn(input_buffer, "\n")] = '\0'; /* remove trailing \n */

		parse_input(input_buffer, args);

		if (args[0] == NULL)
		{
			continue; /* empty input, prompt again */
		}

		command = find_command(args[0]);
		if (command == NULL)
		{
			/* Command doesn't exist, */
			perror(args[0]);
			continue;
		}

		pid = fork();
		if (pid < 0)
		{
			perror("Error: fork() failed");
			continue;
		}
		else if (pid == 0)
		{
			execve(command, args, environ);
			perror("Error: execv() failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		free(command);
		free(input_buffer);
	}
	exit(EXIT_SUCCESS);
}
