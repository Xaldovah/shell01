#include "shell.h"

/**
 * my_getline - ...
 *
 * Return: EXIT_SUCCESS
 */

char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_index;
	static int chars_in_buffer;
	char *line = NULL;
	int line_size = 0;

	while (1)
	{
		if (buffer_index >= chars_in_buffer)
		{
			chars_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (chars_in_buffer <= 0)
			{
				if (line_size > 0)
				{
					break;
				}
				else
				{
					exit(EXIT_FAILURE);
				}
			}
		}
		char c = buffer[buffer_index];

		buffer_index++;
		if (c == '\n')
		{
			break;
		}
		line_size++;
		line = realloc(line, line_size);
		line[line_size - 1] = c;
	}
	if (line)
	{
		line[line_size] = '\0';
	}
	return (line);
	}
}
