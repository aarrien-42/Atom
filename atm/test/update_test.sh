#!/bin/bash

# Get the first parameter
test_type="$1"

# Get script directory
directory=$(dirname "$0")
chmod -R +x $directory

case "$test_type" in
    "lexer")
        echo "Updating lexer tests..."
    ;;
    "parser")
        echo "Updating parser tests..."
    ;;
    "code_gen")
        echo "Updating code_gen tests..."
    ;;
    *)
        echo "Invalid test type. Please use 'lexer', 'parser' or 'code_gen'."
    ;;
esac