# Shell Program

A simple POSIX-compliant shell implementation in C.

## Features

- Command-line interface with `FSH>` prompt
- Process forking and execution using `fork()` and `execvp()`
- Command parsing and tokenization
- Process status monitoring with `waitpid()`

## Platform Support

⚠️ **This program requires a POSIX-compliant system:**
- ✅ Linux
- ✅ macOS
- ✅ WSL (Windows Subsystem for Linux)
- ❌ Native Windows (MinGW/MSYS2) - `fork()` is not supported

### Why it doesn't work on Windows

Windows doesn't support POSIX system calls like `fork()`, `execvp()`, and `waitpid()`. These are Unix-specific APIs. To run this program on Windows, use **WSL (Windows Subsystem for Linux)**.

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

The project includes comprehensive unit and integration tests:

```bash
make test
```

See [tests/README.md](tests/README.md) for more details.

## CI/CD

GitHub Actions automatically:
- Builds on Ubuntu with GCC and Clang
- Runs all tests
- Checks for memory leaks with Valgrind
- Performs static analysis with cppcheck

## Development

### Requirements

- GCC or Clang compiler
- Make
- POSIX-compliant operating system

### Project Structure

```
.
├── main.c                   # Main shell program
├── tests/                   # Test directory
│   ├── test_shell.c         # Unit tests
│   ├── test_integration.c   # Integration tests
│   └── README.md            # Test documentation
├── Makefile                 # Build configuration
└── .github/
    └── workflows/
        └── ci.yml           # GitHub Actions workflow
```

## Known Issues

- Exit command behavior needs fixing (currently uses inequality check)
- Input limited to 60 iterations for safety
- No built-in command support (cd, etc.)

## License

Educational project - free to use and modify.
