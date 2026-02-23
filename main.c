#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
    #include "windows_shell.h"
#else
    #include <unistd.h>
    #include "unix_shell.h"
#endif

/**
 * Driver program - directs user to proper shell implementation according to OS
 */
int main(void) {
    int exit_status;
    
    #if defined(_WIN32) || defined(_WIN64)
        printf("Starting Windows Shell...\n");
        exit_status = run_windows_shell();
    #else
        printf("Starting Unix Shell...\n");
        exit_status = run_unix_shell();
    #endif
    
    return exit_status;
}