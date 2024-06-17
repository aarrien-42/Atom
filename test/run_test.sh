#!/bin/bash

# Get the first parameter
test_type="$1"

# Get script directory
directory=$(dirname "$0")
chmod -R +x $directory

case "$test_type" in
    "lexer")
        echo "Running lexer tests..."
        ./$directory/10_lexer_tests/test_lexer.sh
    ;;
    "parser")
        echo "Running parser tests..."
        ./$directory/20_parser_tests/test_parser.sh
    ;;
    "code_gen")
        echo "Running code_gen tests..."
        ./$directory/30_code_gen_tests/test_code_gen.sh
    ;;
    "clean")
        echo "Cleaning tests..."
        
    ;;
    *)
        echo "Invalid test type. Please use 'lexer', 'parser' or 'code_gen'."
    ;;
esac
