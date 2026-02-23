#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "windows_shell.h"

#define MAX_IN 1024
#define MAX_ARGS 64
#define MAX_CMD_LINE 2048

// Helper function to build command line from args
void build_command_line(const char* args[], char* cmd_line, size_t max_len) {
    cmd_line[0] = '\0';

    for (int i = 0; i < MAX_ARGS && args[i] != NULL; i++) {
        if (i > 0) {
            strcat_s(cmd_line, max_len, " ");
        }
        // Add quotes if argument contains spaces
        if (strchr(args[i], ' ') != NULL) {
            strcat_s(cmd_line, max_len, "\"");
            strcat_s(cmd_line, max_len, args[i]);
            strcat_s(cmd_line, max_len, "\"");
        } else {
            strcat_s(cmd_line, max_len, args[i]);
        }
    }
}

// Windows shell program using native APIs
int run_windows_shell( ){
    char input[ MAX_IN ];
    const char* args[ MAX_ARGS ];
    char cmd_line[ MAX_CMD_LINE ];

    // init input loop
    int i = 0;
    while(i < 60) {
        printf("FSH>");
        fflush( stdout ); // clear output buffer

        // take whole line as std in
        if( fgets( input, sizeof( input ), stdin ) == NULL ){
            perror("fgets failed");
            return 1;
        }
        
        input[ strcspn( input, "\n") ] = '\0';
        printf("%s\n", input);

        // exit cmd
        if( strcmp( input, "exit") == 0 ){
            printf("Exiting...\n");
            return 0;
        }

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // tokenize the command & list of args, up to max limit
        char* token = strtok( input, " " );
        int j = 0;
        while( token != NULL && j < MAX_ARGS - 1 ){
            args[j++] = token;

            // strtok returns a ptr to the next separation if not called on a new var
            token = strtok( NULL, " " );
        }
        args[j] = NULL; // Null-terminate the args array

        if (j == 0) {
            continue; // No command entered
        }

        // Build command line string for Windows
        build_command_line(args, cmd_line, MAX_CMD_LINE);

        // Windows process creation
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Create the child process
        if (!CreateProcess(
            NULL,           // No module name (use command line)
            cmd_line,       // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory
            &si,            // Pointer to STARTUPINFO structure
            &pi             // Pointer to PROCESS_INFORMATION structure
        )) {
            fprintf(stderr, "CreateProcess failed (%lu)\n", GetLastError());
        } else {
            // Wait for child process to complete
            WaitForSingleObject(pi.hProcess, INFINITE);
            
            // Get exit code
            DWORD exit_code;
            if (GetExitCodeProcess(pi.hProcess, &exit_code)) {
                printf("Exit status: %lu\n", exit_code);
            }
            
            // Close process and thread handles
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        i++;
    }


    return 0;
}