#include "shell.h"

/**
  * concatenate_path - Concatenate both names
  * @dir_path: ...
  * @file_name: ...
  *
  * Return: Concatenated names
  */

char *concatenate_path(const char *dir_path, const char *file_name)
{
    size_t file_name_len = 0, dir_path_len = 0, new_size = 0;
    char *result = NULL;

    file_name_len = _strlen(file_name);
    dir_path_len = _strlen(dir_path);
    new_size = dir_path_len + file_name_len + 2;
    result = malloc(sizeof(char) * new_size);

    if (!result)
    {
        return NULL;
    }

    strcpy(result, dir_path);
    _strcat(result, "/");
    _strcat(result, file_name);

    return result;
}

/**
  * lookup_path - ...
  * @command_name: ...
  *
  * Return: Path name or NULL
  */

char *lookup_path(const char *command_name)
{
    const char *environ_path = NULL;
    char **path_tokens = NULL;
    int a = 0, num_delims = 0;
    struct stat st;

    if (command_name)
    {
        if (stat(command_name, &st) != 0 && command_name[0] != '/')
        {
            environ_path = getenv("PATH");
            num_delims = count_chars(environ_path, ":") + 1;
            path_tokens = custom_tokenize(environ_path, ":", num_delims);

            while (path_tokens[a])
            {
                char *concatenated_path = concatenate_path(path_tokens[a], command_name);

                if (!concatenated_path)
                {
                    /* Handle memory allocation failure */
                    free(path_tokens);
                    return NULL;
                }

                if (stat(concatenated_path, &st) == 0)
                {
                    free((void *)command_name);
                    command_name = strdup(concatenated_path);
                    free(concatenated_path);
                    free(path_tokens);
                    return (char *)command_name;
                }

                free(concatenated_path);
                a++;
            }

            free(path_tokens);
        }

        if (stat(command_name, &st) == 0)
            return (char *)command_name;
    }

    free((void *)command_name);
    return NULL;
}

/**
  * execute_cmd - ...
  * @command_name: ...
  * @arguments: ...
  *
  * Return: ...
  */

int execute_cmd(const char *command_name, char **arguments)
{
    pid_t child_pid;
    int status;

    switch (child_pid = fork())
    {
        case -1:
            perror("fork");
            return -1;
        case 0:
            execve(command_name, arguments, environ);
            perror("execve"); /* Handle execve error */
            exit(EXIT_FAILURE); /* Terminate child process on error */
        default:
            do {
                waitpid(child_pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}
