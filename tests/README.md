# Tests Directory

This directory contains unit and integration tests for the shell program.

## Test Files

- **test_shell.c** - Unit tests for core shell functionality (fork, execvp, waitpid, string parsing)
- **test_integration.c** - Integration tests that run actual shell commands

## Running Tests

### Using Make (Linux/WSL/macOS)

```bash
# Run all tests
make test

# Build only
make all

# Clean build artifacts
make clean
```

### Manual Compilation

```bash
# Compile a specific test
gcc -Wall -Wextra -g -std=c11 tests/test_shell.c -o test_shell

# Run the test
./test_shell
```

## Test Framework

The tests use a simple custom test framework with these macros:

- `TEST(name)` - Define a test function
- `RUN_TEST(test)` - Execute a test
- `ASSERT_EQ(expected, actual)` - Assert equality
- `ASSERT_TRUE(condition)` - Assert condition is true

## CI/CD

Tests are automatically run on every push and pull request via GitHub Actions. The workflow:

1. Builds the shell program on Ubuntu (latest and 20.04)
2. Tests with both GCC and Clang compilers
3. Runs all test suites
4. Performs memory leak detection with Valgrind
5. Runs static analysis with cppcheck

## Requirements

- GCC or Clang compiler
- POSIX-compliant system (Linux, macOS, WSL)
- Standard POSIX headers (`unistd.h`, `sys/wait.h`)

## Adding New Tests

1. Create a new test file in `tests/` directory
2. Include the necessary test macros
3. Write test functions using `TEST(name)` macro
4. Add `RUN_TEST()` calls in `main()`
5. The Makefile will automatically pick up new test files
