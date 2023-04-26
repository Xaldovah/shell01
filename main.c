#include "shell.h"

/**
 * This function initializes the path array by parsing PATH environ variable.
 * It splits the string into individual paths and stores them in the path array
 */
void init_paths()
{
	char *path_var;
	char *path_str;
	int i = 0;
	char *path_token;
	
	path_var = getenv("PATH");
	if (path_var == NULL)
	{
		perror("PATH");
		exit(EXIT_FAILURE);
	}
	path_str = strdup(path_var);
	if (path_str == NULL)
	{
		perror("memory");
		exit(EXIT_FAILURE);
	}
	path_token = strtok(path_str, ":");
	while (path_token != NULL && i < MAX_PATHS - 1)
	{
		path[i++] = path_token;
		path_token = strtok(NULL, ":");
	}
	path[i] = NULL;
	free(path_str);
}

char *find_command(char *command)
{
	char path_buffer[MAX_PATH_LENGTH];
	int i;
	for (i = 0; path[i] != NULL; i++) {
		snprintf(path_buffer, MAX_PATH_LENGTH, "%s/%s", path[i], command);
		if (access(path_buffer, X_OK) == 0)
		{
			return strdup(path_buffer); /* make str cpy */
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
	char *args[MAX_ARGS];
	pid_t pid;
	int status;
	char *command;

	init_paths();

	while (1)
	{
		char *input_buffer = NULL;
		size_t buffer_size = 0;

		write(STDOUT_FILENO, PROMPT, strlen(PROMPT) + 1);
		fflush(stdout);
		if (getline(&input_buffer, &buffer_size, stdin) == -1)
		{
			/* handle EOF or error */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		input_buffer[strcspn(input_buffer, "\n")] = '\0';
		
		parse_input(input_buffer, args);
		
		if (args[0] == NULL)
		{
			continue; /* empty input, prompt again */
		}
		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		command = find_command(args[0]);
		if (command == NULL)
		{ /* Command doesn't exist, */
			char *msg = "command not found\n";
			write(STDERR_FILENO, args[0], strlen(args[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, msg, strlen(msg));
			continue;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(command);
			continue;
		}
		else if (pid == 0)
		{
			execve(command, args, environ);
			perror("execve");
			free(command);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(command);
		}
	}
	exit(EXIT_SUCCESS);
}
