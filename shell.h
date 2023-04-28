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
#define MAX_ARGS 64
#define MAX_PATHS 64
#define MAX_PATH_LENGTH 256
#define BUFFER_SIZE 1024

/* Function prototypes */
extern char *path[MAX_PATHS + 1];
extern char **environ;

char *string_toupper(char *s);
struct stat buffer;
<<<<<<< HEAD
struct stat st;
=======
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
void _print_environ(void);
void handle_exit(char **tokens, char *line);
char **tokenize_cmdline(char *cmdline);
char *_strdup(const char *s);
char *check_path(char *cmd);
char *_getenv(const char *name);
size_t _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strcspn(const char *s, const char *reject);
char *my_getline(void);
void parse_input(char *input, char **args);
char *find_command(char *command);
void free_array(char **args);
<<<<<<< HEAD
=======
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int count_input(char *str);
int count_del(char *str, char *del);
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9
char *concatenate_path(char *pathname, char *name);
char *find_cmd(char *nomb);
int exec_cmd(char *cmd, char **args);
int builtin(char **tokens, char *ln);
<<<<<<< HEAD
int _strcmp(const char *s1, const char *s2);
void *_realloc (void *ptr, size_t size);
int count_del(char *str, char *del);
int count_input(char *str);
=======
void _handle_exit(char **u_tokns, char *line);
char **tokenize(char *str, char *del, int len);
void handle_signal(int sig_id);
char *find(char *nomb);
int exec(char *nomb, char **opts);
>>>>>>> edbbd58bb0a594190060339b47a426caab2508e9

#endif
