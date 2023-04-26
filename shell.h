#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_INPUT 1024
#define PROMPT "shell$ "

/* Function prototypes */
extern char **environ;

char *string_toupper(char *s);
struct stat buffer;
void _print_environ(void);
void handle_exit(char **tokens, char *line);
char **tokenize_cmdline(char *cmdline);
char *strdup(const char *s);
char *check_path(char *cmd);
char *getenv(const char *name);
size_t strlen(const char *s);
char *strcat(char *dest, const char *src);
char *strcpy(char *dest, const char *src);
size_t strcspn(const char *s, const char *reject);

#endif
