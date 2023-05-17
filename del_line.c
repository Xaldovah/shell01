#include "shell.h"

/**
  * rem_newline_char - ...
  * @str: ...
  *
  * Return: string sino new line
  */

char *rem_newline_char(const char *str)
{
    char *res;
    size_t len = strlen(str);

    if (len == 0)
        return NULL;

    res = malloc((len + 1) * sizeof(char));
    if (res == NULL)
        return NULL;

    strncpy(res, str, len);
    res[len - 1] = '\0';

    return (res);
}

