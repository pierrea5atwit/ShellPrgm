#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#define TEST(name) void name()
#define RUN_TEST(test) do { \
    printf("Running %s...", #test); \
    test(); \
    printf(" PASSED\n"); \
    tests_passed++; \
} while(0)

#define ASSERT_EQ(expected, actual) \
    assert((expected) == (actual))

#define ASSERT_TRUE(condition) \
    assert(condition)

int tests_passed = 0;

// Test running echo command
TEST(test_echo_command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        char* args[] = {"echo", "hello", NULL};
        execvp(args[0], args);
        exit(1); // Should never reach here
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(0, WEXITSTATUS(status));
    }
}

// Test running ls command
TEST(test_ls_command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        char* args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(0, WEXITSTATUS(status));
    }
}

// Test running pwd command
TEST(test_pwd_command) {
    pid_t pid = fork();
    
    if (pid == 0) {
        char* args[] = {"pwd", NULL};
        execvp(args[0], args);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(0, WEXITSTATUS(status));
    }
}

// Test invalid command returns non-zero status
TEST(test_invalid_command_fails) {
    pid_t pid = fork();
    
    if (pid == 0) {
        char* args[] = {"nonexistent_command_12345", NULL};
        execvp(args[0], args);
        exit(127); // Command not found
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(127, WEXITSTATUS(status));
    }
}

int main() {
    printf("=== Running Integration Tests ===\n\n");
    
    RUN_TEST(test_echo_command);
    RUN_TEST(test_ls_command);
    RUN_TEST(test_pwd_command);
    RUN_TEST(test_invalid_command_fails);
    
    printf("\n=== All %d integration tests passed! ===\n", tests_passed);
    return 0;
}
