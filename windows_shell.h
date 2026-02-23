#ifndef WINDOWS_SHELL_H
#define WINDOWS_SHELL_H

#include <windows.h>

// Helper function to build command line from arguments
void build_command_line(char* args[], char* cmd_line, size_t max_len);

#endif // WINDOWS_SHELL_H
