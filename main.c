#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_IN 1024
#define MAX_ARGS 64

// mock shell program, 1 file
int main( ){
    char input[ MAX_IN ];
    char* args[ MAX_ARGS ];

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
        if( strcmp( input, "exit") ){
            printf("Exiting...");
            return 2;
        }

        // tokenize the command & list of args, up to max limit
        char* token = strtok( input, " " );
        int j = 0;
        while( token != NULL && j < MAX_ARGS ){
            args[j++] = token;

            // strtok returns a ptr to the next separation if not called on a new var
            token = strtok( NULL, " " );
        }

        // everything after the first real char

        i++;
    }


    return 0;
}