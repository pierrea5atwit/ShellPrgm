# Shell Program

A simple POSIX-compliant shell implementation in C.

## Features

- Command-line interface with `FSH>` prompt, good for executing UNIX cmds
- Process forking and execution using `fork()` and `execvp()`
- Command parsing and tokenization
- Process status monitoring with `waitpid()`

## Platform Support

**Program does not require a POSIX-compliant system:**
- ✅ Linux
- ✅ macOS
- ✅ WSL (Windows Subsystem for Linux)
- ✅ Windows Translation (for MinGW/MSYS2) - `fork()` is not supported natively

### Why Windows requires change

Windows doesn't support POSIX system calls like `fork()`, `execvp()`, and `waitpid()`. These are Unix-specific APIs.

## Building

### Using Make

```bash
make all          # Build the shell program
make test         # Build and run tests
make run          # Build and run the shell
make clean        # Clean build artifacts
```

### Manual Compilation

```bash
gcc -Wall -Wextra -g -std=c11 main.c -o shell
./shell
```

## Usage

```bash
$ ./build/shell
FSH> ls
# Lists files in current directory

FSH> pwd
# Shows current directory

FSH> echo hello world
# Prints "hello world"

FSH> exit
# Exits the shell
```

## Testing

The project includes comprehensive unit and integration tests for Unix/Linux/macOS platforms.

### Run Tests Locally

```bash
# Build and run all tests
make test

# Or use the test runner
chmod +x tests/run_tests.sh
./tests/run_tests.sh
```

**Note:** Tests require POSIX APIs and cannot run on native Windows. Use WSL or see test results in GitHub Actions.

### Test Coverage

- **Unit Tests**: fork(), execvp(), waitpid(), string parsing
- **Integration Tests**: Real command execution (ls, pwd, echo)
- **Memory Checks**: Valgrind leak detection (CI only)

See [tests/TESTING.md](tests/TESTING.md) for detailed testing documentation.

## CI/CD

GitHub Actions automatically tests every push and pull request:

| Platform | Compiler | Tests | Memory Check |
|----------|----------|-------|--------------|
| Ubuntu Latest | GCC | ✓ | ✓ Valgrind |
| Ubuntu Latest | Clang | ✓ | - |
| Ubuntu 20.04 | GCC | ✓ | ✓ Valgrind |
| Ubuntu 20.04 | Clang | ✓ | - |
| macOS Latest | Clang | ✓ | - |
| Windows Latest | GCC | Build Only | - |

**Additional Checks:**
- Static analysis with cppcheck
- Code formatting checks
- Build artifact uploads

## Development

### Requirements

- GCC or Clang compiler
- Make
- POSIX-compliant operating system

### Project Structure

```
.
├── main.c                      # Platform detection & driver
├── unix_shell.c/h              # Unix/POSIX shell implementation  
├── windows_shell.c/h           # Windows native shell implementation
├── tests/                      # Test directory
│   ├── test_shell.c            # Unit tests
│   ├── test_integration.c      # Integration tests
│   ├── run_tests.sh            # Test runner script
│   └── TESTING.md              # Test documentation
├── Makefile                    # Cross-platform build config
├── .gitignore                  # Git ignore rules
└── .github/
    └── workflows/
        └── ci.yml              # GitHub Actions CI/CD
```

## Known Issues

- Exit cmd behavior needs fixing (currently uses inequality check)
- Input limited to 60 iterations for safety
- No built-in command support (cd, etc.)

## License

Educational project - free to use and modify.
