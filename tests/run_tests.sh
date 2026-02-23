#!/bin/bash
# Test runner script for Unix/Linux systems

set -e  # Exit on error

echo "======================================="
echo "Running Test Suite"
echo "Platform: $(uname -s)"
echo "======================================="
echo ""

# Track test results
TESTS_RUN=0
TESTS_PASSED=0
TESTS_FAILED=0

# Find all test binaries
TEST_BINARIES=$(find build -name 'test_*' -type f 2>/dev/null || true)

if [ -z "$TEST_BINARIES" ]; then
    echo "No test binaries found. Building tests..."
    make test
    TEST_BINARIES=$(find build -name 'test_*' -type f)
fi

# Run each test
for test in $TEST_BINARIES; do
    if [ -x "$test" ]; then
        TESTS_RUN=$((TESTS_RUN + 1))
        echo ""
        echo "---------------------------------------"
        echo "Running: $(basename $test)"
        echo "---------------------------------------"
        
        if $test; then
            TESTS_PASSED=$((TESTS_PASSED + 1))
            echo "✓ PASSED: $(basename $test)"
        else
            TESTS_FAILED=$((TESTS_FAILED + 1))
            echo "✗ FAILED: $(basename $test)"
            exit 1
        fi
    fi
done

echo ""
echo "======================================="
echo "Test Results"
echo "======================================="
echo "Total:  $TESTS_RUN"
echo "Passed: $TESTS_PASSED"
echo "Failed: $TESTS_FAILED"
echo "======================================="

if [ $TESTS_FAILED -eq 0 ]; then
    echo "✓ All tests passed!"
    exit 0
else
    echo "✗ Some tests failed!"
    exit 1
fi
