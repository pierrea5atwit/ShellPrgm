CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
LDFLAGS = 

# Detect OS
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    SHELL_SRC = windows_shell.c
    MAIN_BIN = shell.exe
else
    DETECTED_OS := $(shell uname -s)
    SHELL_SRC = unix_shell.c
    MAIN_BIN = shell
endif

# Directories
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build

# Source files
MAIN_SRC = main.c
SRCS = $(MAIN_SRC) $(SHELL_SRC)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_SRCS))

# Main executable
MAIN_BIN_PATH = $(BUILD_DIR)/$(MAIN_BIN)

.PHONY: all clean test run dirs info

all: dirs info $(MAIN_BIN_PATH)

# Show build info
info:
	@echo "Building for: $(DETECTED_OS)"
	@echo "Shell implementation: $(SHELL_SRC)"
	@echo ""

# Create build directory
dirs:
	@mkdir -p $(BUILD_DIR)

# Build main shell program
$(MAIN_BIN_PATH): $(OBJS) | dirs
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
$(BUILD_DIR)/%.o: %.c | dirs
	$(CC) $(CFLAGS) -c -o $@ $<

# Build test executables
$(BUILD_DIR)/%: $(TEST_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Build and run all tests
test: dirs $(TEST_BINS)
	@echo "==================================="
	@echo "Running all tests..."
	@echo "==================================="
	@for test in $(TEST_BINS); do \
		echo ""; \
		./$$test || exit 1; \
	done
	@echo ""_PATH)
	./$(MAIN_BIN_PATH=============================="
	@echo "All test suites passed!"
	@echo "==================================="

# Run the main shell program
run: $(MAIN_BIN)
	./$(MAIN_BIN)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.exe *.out

# Help target
help:
	@echo "Available targets:"
	@echo "  make all    - Build the shell program"
	@echo "  make test   - Build and run all tests"
	@echo "  make run    - Build and run the shell program"
	@echo "  make clean  - Remove build artifacts"
