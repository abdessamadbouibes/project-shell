
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "shell.h"

int main(void) {
    char *line;
    char *args[MAX_ARGS];
    int status = 1;

    signal(SIGINT, handle_sigint);

    while (status) {
        printf("shell> ");
        fflush(stdout);

        line = read_line();
        if (!line) break;

        int argc = parse_line(line, args);
        if (argc > 0) {
            status = execute_command(args);
        }
        free(line);
    }
    return 0;
}
