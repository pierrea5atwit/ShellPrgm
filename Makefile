CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
LDFLAGS = 

# Directories
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build

# Source files
MAIN_SRC = main.c
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_SRCS))

# Main executable
MAIN_BIN = $(BUILD_DIR)/shell

.PHONY: all clean test run dirs

all: dirs $(MAIN_BIN)

# Create build directory
dirs:
	@mkdir -p $(BUILD_DIR)

# Build main shell program
$(MAIN_BIN): $(MAIN_SRC) | dirs
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

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
	@echo ""
	@echo "==================================="
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
