CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
LDFLAGS = 

# Detect OS
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    SHELL_SRC = windows_shell.c
    RM = del /Q
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    EXE_EXT = .exe
else
    DETECTED_OS := $(shell uname -s)
    SHELL_SRC = unix_shell.c
    RM = rm -f
    MKDIR = mkdir -p $(BUILD_DIR)
    EXE_EXT = 
endif

# Directories
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build

# Source files
MAIN_SRC = main.c
SRCS = $(MAIN_SRC) $(SHELL_SRC)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test files (only POSIX tests on Unix systems)
ifeq ($(DETECTED_OS),Windows)
    TEST_SRCS = 
    TEST_BINS = 
else
    TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
    TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%$(EXE_EXT),$(TEST_SRCS))
endif

# Main executable
MAIN_BIN = $(BUILD_DIR)/shell$(EXE_EXT)

.PHONY: all clean test run dirs info

all: dirs info $(MAIN_BIN)

# Show build info
info:
	@echo "======================================="
	@echo "Building for: $(DETECTED_OS)"
	@echo "Shell implementation: $(SHELL_SRC)"
	@echo "Compiler: $(CC)"
	@echo "======================================="
	@echo ""

# Create build directory
dirs:
	@$(MKDIR)

# Build main shell program
$(MAIN_BIN): $(OBJS) | dirs
	@echo "Linking $(MAIN_BIN)..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete!"

# Compile object files
$(BUILD_DIR)/%.o: %.c | dirs
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

# Build test executables (Unix only)
$(BUILD_DIR)/%$(EXE_EXT): $(TEST_DIR)/%.c | dirs
	@echo "Building test: $@..."
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Build and run all tests
ifeq ($(DETECTED_OS),Windows)
test:
	@echo "======================================="
	@echo "Tests are not available on Windows"
	@echo "POSIX tests require fork/exec support"
	@echo "Use WSL or Linux to run tests"
	@echo "======================================="
else
test: dirs $(TEST_BINS)
	@echo "======================================="
	@echo "Running all tests on $(DETECTED_OS)..."
	@echo "======================================="
	@for test in $(TEST_BINS); do \
		echo ""; \
		$$test || exit 1; \
	done
	@echo ""
	@echo "======================================="
	@echo "All test suites passed!"
	@echo "======================================="
endif

# Run the main shell program
run: $(MAIN_BIN)
	@echo "Starting shell..."
	@./$(MAIN_BIN)

# Clean build artifacts
ifeq ($(DETECTED_OS),Windows)
clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@$(RM) *.exe *.o 2>nul || true
else
clean:
	@rm -rf $(BUILD_DIR)
	@rm -f *.exe *.out *.o
endif
	@echo "Clean complete!"

# Help target
help:
	@echo "Available targets:"
	@echo "  make all    - Build the shell program"
	@echo "  make test   - Build and run all tests (Unix/Linux only)"
	@echo "  make run    - Build and run the shell program"
	@echo "  make clean  - Remove build artifacts"
	@echo "  make info   - Show build configuration"
