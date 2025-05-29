#ifndef SHELL_H
#define SHELL_H

#define MAX_LINE 1024
#define MAX_ARGS 64

void handle_sigint(int sig);
char *read_line(void);
int parse_line(char *line, char **args);
int execute_command(char **args);

#endif // SHELL_H
