#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"

void handle_sigint(int sig) {
    (void)sig;
}

char *read_line(void) {
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }
    return line;
}

int parse_line(char *line, char **args) {
    int count = 0;
    char *saveptr;
    char *token = strtok_r(line, " \t\r\n", &saveptr);
    while (token && count < MAX_ARGS - 1) {
        args[count++] = token;
        token = strtok_r(NULL, " \t\r\n", &saveptr);
    }
    args[count] = NULL;
    return count;
}

int execute_command(char **args) {
    if (args[0] == NULL) return 1;
    if (strcmp(args[0], "exit") == 0) return 0;
    if (strcmp(args[0], "cd") == 0) {
        if (args[1]) {
            if (chdir(args[1]) != 0) perror("cd");
        } else {
            fprintf(stderr, "cd: missing argument\n");
        }
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}
