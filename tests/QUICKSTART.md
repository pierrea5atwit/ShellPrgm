# Quick Testing Guide

## Local Testing

### Build and Test (Unix/Linux/macOS)
```bash
make test
```

### Build Only (Windows)
```bash
make all
```

### Run Individual Tests
```bash
# Build a specific test
gcc -Wall -Wextra -g tests/test_shell.c -o test_shell

# Run it
./test_shell
```

## GitHub Actions

Tests run automatically on:
- Every push to `main`, `master`, or `develop` branches
- Every pull request to these branches

View results at: `https://github.com/YOUR_USERNAME/ShellPrgm/actions`

## Test Commands Reference

| Command | Description |
|---------|-------------|
| `make all` | Build shell program for current platform |
| `make test` | Build and run all tests (Unix only) |
| `make run` | Build and run the shell interactively |
| `make clean` | Remove all build artifacts |
| `make info` | Show current build configuration |
| `make help` | Display available make targets |

## Manual Test Execution

```bash
# Make test runner executable
chmod +x tests/run_tests.sh

# Run all tests with verbose output
./tests/run_tests.sh
```

## Memory Leak Testing (Linux)

```bash
# Install Valgrind
sudo apt-get install valgrind

# Run tests with Valgrind
valgrind --leak-check=full ./build/test_shell
valgrind --leak-check=full ./build/test_integration
```

## Expected Output

### Successful Test Run
```
=======================================
Running all tests on Linux...
=======================================

Running test_shell... PASSED
Running test_integration... PASSED

=======================================
All test suites passed!
=======================================
```

### On Windows
```
=======================================
Tests are not available on Windows
POSIX tests require fork/exec support
Use WSL or Linux to run tests
=======================================
```

## Debugging Failed Tests

1. **Build with debug symbols** (already enabled with `-g`)
2. **Run test manually** to see detailed output
3. **Use GDB** for debugging:
   ```bash
   gdb ./build/test_shell
   (gdb) run
   (gdb) backtrace
   ```

## Adding Your Own Tests

See [TESTING.md](TESTING.md) for detailed instructions on writing and adding new tests.
