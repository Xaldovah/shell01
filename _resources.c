#include "shell.h"

/**
  * _strcat - ...
  * @destination: ...
  * @source: ...
  *
  * Return: ...
  */
char *_strcat(char *destination, char *source)
{
        int dest_length = 0, a = 0;

        while (destination[dest_length])
                dest_length++;

        for (a = 0; source[a] != '\0'; a++)
        {
                destination[dest_length] = source[a];
                dest_length++;
        }

        destination[dest_length] = '\0';
        return (destination);
}

/**
  * _strlen - ...
  * @str: ...
  *
  * Return: ...
  */
int _strlen(const char *str)
{
	int a = 0;

	while (str[a])
		a++;

	return (a);
}

/**
  * _strcmp - ...
  * @s1: ...
  * @s2: ...
  *
  * Return: ...
  */
int _strcmp(char *s1, char *s2)
{
        int length_s1 = 0, length_s2 = 0, loc = 0, variance = 0, limit = 0;

        length_s1 = _strlen(s1);
        length_s2 = _strlen(s2);

        if (length_s1 <= length_s2)
                limit = length_s1;
        else
                limit = length_s2;

        while (loc <= limit)
        {
                if (s1[loc] == s2[loc])
                {
                        loc++;
                        continue;
                }
                else
                {
                        variance = s1[loc] - s2[loc];
                        break;
                }

                loc++;
        }

        return (variance);
}

/**
  * _strdup - ...
  * @str: ...
  *
  * Return: ...
  */
char *_strdup(const char *str)
{
        int index = 0, length = 1;
        char *dup_str;

        if (str == NULL)
                return (NULL);

        length = _strlen(str);
        dup_str = malloc((sizeof(char) * length) + 1);
        if (dup_str == NULL)
                return (NULL);

        while (index < length)
        {
                dup_str[index] = str[index];
                index++;
        }

        dup_str[index] = '\0';
        return (dup_str);
}

/**
  * _atoi - ...
  * @str: ...
  *
  * Return: ...
  */
int _atoi(char *str)
{
        int sign = 1, digit_count = 0, a = 0;
        unsigned int result = 0;

        while (str[a])
        {
                if (str[a] == '-')
                        sign = -1;

                while (str[a] >= '0' && str[a] <= '9')
                {
                        digit_count = 1;
                        result = (result * 10) + (str[a] - '0');
                        a++;
                }

                if (digit_count == 1)
                        break;

                a++;
        }

        result *= sign;
        return (result);
}
