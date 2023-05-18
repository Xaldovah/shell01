#include "shell.h"

/**
  * tokenize_cmdline - ...
  * @str: ...
  * @delimiter: ...
  * @count:
  *
  * Return: array of args or NULL
  */
char **custom_tokenize(const char *str, const char *delimiter, int count)
{
    char **token_array = NULL, *current_token = NULL, *temp_str = NULL;
    int a = 0, i;

    token_array = malloc(sizeof(char *) * (count + 1));
    if (!token_array)
    {
        return NULL;
    }
    str = rem_newline_char(str);
    temp_str = strdup(str);
    current_token = strtok(temp_str, delimiter);

    while (current_token)
    {
        token_array[a] = strdup(current_token);
        if (!token_array[a])
        {
            /* Free previously allocated memory and return NULL */
            for (i = 0; i < a; i++)
            {
                free(token_array[i]);
            }
            free(token_array);
            free(temp_str);

	    for (i = 0; i < a; i++)
            {
                free(token_array[i]);
            }
            free(token_array);
            return NULL;
        }
        current_token = strtok(NULL, delimiter);
        a++;
    }

    token_array[a] = NULL;
    free(temp_str);
    return token_array;
}
