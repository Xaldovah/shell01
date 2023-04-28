#include "shell.h"

/**
 * main - Entry point for the shell
 *
 * Return: Always 0.
 */
int main(void)
{
        char *ln = NULL, **tokens = NULL;
        int str_len = 0, flag = 0;
        size_t ln_size = 0;
        ssize_t ln_length = 0;

        signal(SIGINT, handle_signal);

        while (ln_length >= 0)
        {
                if (isatty(STDIN_FILENO))
                {
                        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
                }
                ln_length = getline(&ln, &ln_size, stdin);
                if (ln_length == -1)
                {
                        if (isatty(STDIN_FILENO))
                        {
                                write(STDOUT_FILENO, "\n", 1);
                        }
                        break;
                }
                str_len = count_input(ln);
                if (ln[0] != '\n' && str_len > 0)
                {
                        tokens = tokenize(ln, " \t\n", str_len);
                        if (tokens != NULL)
                        {
                                flag = builtin(tokens, ln);
                                if (!flag && tokens[0] != NULL)
                                {
                                        tokens[0] = find(tokens[0]);
                                        if (tokens[0] && access(tokens[0], X_OK) == 0)
                                        {
                                                exec(tokens[0], tokens);
                                        }
                                }
                                free(tokens);
                        }
                }
        }
        free(ln);
        return (0);
}
