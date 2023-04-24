#include "shell.h"

#define MAX_ARGS 64
#define MAX_PATHS 64
#define MAX_PATH_LENGTH 256

char *path[MAX_PATHS + 1]; /* array to hold paths from PATH environment variable */

/**
 * This function initializes the path array by parsing PATH environ variable.
 * It splits the string into individual paths and stores them in the path array
 */
void init_paths() {
    char *path_var;
    char *path_str;
    int i = 0;
    char *path_token;

    path_var = getenv("PATH");
    if (path_var == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        exit(EXIT_FAILURE);
    }

    path_str = strdup(path_var);
    if (path_str == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    path_token = strtok(path_str, ":");
    while (path_token != NULL && i < MAX_PATHS - 1) {
        path[i++] = path_token;
        path_token = strtok(NULL, ":");
    }
    path[i] = NULL;
}

char *find_command(char *command) {
    char path_buffer[MAX_PATH_LENGTH];
    int i;
    for (i = 0; path[i] != NULL; i++) {
        snprintf(path_buffer, MAX_PATH_LENGTH, "%s/%s", path[i], command);
        if (access(path_buffer, X_OK) == 0) {
            return strdup(path_buffer); /* make str cpy to avoid modifying original */
        }
    }
    return NULL;
}

void parse_input(char *input, char *args[]) {
    int i = 0;
    char *token = NULL;

    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL; /* add a NULL pointer to mark the end of the array */
}

int main(void) {
    char input_buffer[1024];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;
    char *command;

    init_paths();

    while (1) {
        printf(":) ");
        fflush(stdout);

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            /* handle EOF or error */
            printf("\n");
            break;
        }

        input_buffer[strcspn(input_buffer, "\n")] = '\0'; /* remove trailing newline */

        parse_input(input_buffer, args);

        if (args[0] == NULL) {
            continue; /* empty input, prompt again */
        }

        command = find_command(args[0]);
        if (command == NULL) { /* Command doesn't exist, */
            printf("%s: command not found\n", args[0]);
            continue;
        }

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error: fork() failed\n");
            free(command);
            continue;
        } else if (pid == 0) {
            execv(command, args);
            fprintf(stderr, "Error: execv() failed\n");
            free(command);
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
            free(command);
        }
    }

    return 0;
}
