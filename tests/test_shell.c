#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

// Simple test framework macros
#define TEST(name) void name()
#define RUN_TEST(test) do { \
    printf("Running %s...", #test); \
    test(); \
    printf(" PASSED\n"); \
    tests_passed++; \
} while(0)

#define ASSERT_EQ(expected, actual) \
    assert((expected) == (actual))

#define ASSERT_NEQ(expected, actual) \
    assert((expected) != (actual))

#define ASSERT_TRUE(condition) \
    assert(condition)

int tests_passed = 0;

// Test fork() functionality
TEST(test_fork_creates_child_process) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        exit(42);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(42, WEXITSTATUS(status));
    } else {
        // Fork failed
        ASSERT_TRUE(0); // This should never happen in tests
    }
}

// Test execvp() with a simple command
TEST(test_execvp_runs_command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - run 'true' command
        char* args[] = {"true", NULL};
        execvp("true", args);
        // If we get here, execvp failed
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(0, WEXITSTATUS(status));
    }
}

// Test waitpid() functionality
TEST(test_waitpid_retrieves_status) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child exits with specific code
        exit(123);
    } else if (pid > 0) {
        int status;
        pid_t result = waitpid(pid, &status, 0);
        ASSERT_EQ(pid, result);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(123, WEXITSTATUS(status));
    }
}

// Test string tokenization (strtok)
TEST(test_string_tokenization) {
    char input[] = "ls -la /tmp";
    char* args[4];
    
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < 4) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    
    ASSERT_EQ(3, i);
    ASSERT_EQ(0, strcmp("ls", args[0]));
    ASSERT_EQ(0, strcmp("-la", args[1]));
    ASSERT_EQ(0, strcmp("/tmp", args[2]));
}

// Test newline stripping
TEST(test_newline_stripping) {
    char input[] = "test command\n";
    input[strcspn(input, "\n")] = '\0';
    
    ASSERT_EQ(0, strcmp("test command", input));
    ASSERT_EQ(12, strlen(input));
}

// Test multiple forks
TEST(test_multiple_forks) {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {
            exit(i);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            ASSERT_TRUE(WIFEXITED(status));
            ASSERT_EQ(i, WEXITSTATUS(status));
        }
    }
}

int main() {
    printf("=== Running Shell Program Tests ===\n\n");
    
    RUN_TEST(test_fork_creates_child_process);
    RUN_TEST(test_execvp_runs_command);
    RUN_TEST(test_waitpid_retrieves_status);
    RUN_TEST(test_string_tokenization);
    RUN_TEST(test_newline_stripping);
    RUN_TEST(test_multiple_forks);
    
    printf("\n=== All %d tests passed! ===\n", tests_passed);
    return 0;
}
