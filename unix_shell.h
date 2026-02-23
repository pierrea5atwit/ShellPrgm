#ifndef UNIX_SHELL_H
#define UNIX_SHELL_H

#include <sys/types.h>

// Function declarations
void run_shell(void);
pid_t execute_command(char* args[]);
int parse_input(char* input, char* args[], int max_args);

#endif // UNIX_SHELL_H
