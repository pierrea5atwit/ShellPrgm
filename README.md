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

The project includes comprehensive unit and integration tests:

```bash
make test
```

See [tests/TESTING.md](tests/TESTING.md) for more.

## CI/CD

GitHub Actions will be able to:
- Build on Ubuntu with GCC and Clang
- Run all tests
- Check for memory leaks with Valgrind
- Perform static analysis with cppcheck

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

- Exit cmd behavior needs fixing (currently uses inequality check)
- Input limited to 60 iterations for safety
- No built-in command support (cd, etc.)

## License

Educational project - free to use and modify.
