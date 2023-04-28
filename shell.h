#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <ctype.h>

#define MAX_INPUT 1024
#define PROMPT "shell$ "
#define MAX_ARGS 64
#define MAX_PATHS 64
#define MAX_PATH_LENGTH 256
#define BUFFER_SIZE 1024

extern char **environ;

/* Function prototypes */
char *string_toupper(char *s);
char *find(char *command);
char *find_cmd(char *nomb);
void _print_environ(void);
void handle_exit(char **tokens, char *line);
char **tokenize_cmdline(char *cmdline);
char *check_path(char *cmd);
char *my_getline(void);
void parse_input(char *input, char **args);
char *find_command(char *command);
void free_array(char **args);
int count_input(char *str);
int count_del(char *str, char *del);
char *concatenate_path(char *pathname, char *name);
int exec_cmd(char *cmd, char **args);
int builtin(char **tokens, char *ln);
void handle_exit(char **u_tokns, char *line);
char **tokenize(char *str, char *del, int len);
void handle_signal(int sig_id);
int exec(char *nomb, char **opts);


/**
 * _strcpy -  copies the string pointed to by src
 *
 * @dest: copy to
 *
 * @src: copy from
 *
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	int x = 0;

	while (*(src + i) != '\0')
	{
		i++;
	}
	for ( ; x < i ; x++)
	{
		dest[x] = src[x];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strlen - returns the length of a string
 *
 * @s: string
 *
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}
	return (longi);
}

/**
 * _strcat - concatenates two strings
 *
 * @src: input value
 *
 * @dest: input value
 *
 * Return: void
 */
char *_strcat(char *dest, char *src)
{
	int n;
	int m;

	n = 0;
	while (dest[n] != '\0')
	{
		n++;
	}
	m = 0;
	while (src[m] != '\0')
	{
		dest[n] = src[m];
			n++;
		m++;
	}
	dest[n] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: string being compared
 * @s2: string s1 is being compared to
 * Return: void
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

#endif
