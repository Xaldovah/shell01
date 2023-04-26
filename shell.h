#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 64
#define MAX_PATHS 64
#define MAX_PATH_LENGTH 256

/* Function prototypes */
void init_paths();
char *find_command(char *command);
void parse_input(char *input, char *args[]);
void free_array(char *args[]);
void free_paths();
extern char **environ;
char *string_toupper(char *s);
char *path[MAX_PATHS + 1];
void print_environment(void);
struct stat st;
void _print_environ(void);

#endif
