#!/bin/bash

# Description: Copies actual_results into expected_results

# Get the first parameter
test_type="$1"

# Get script directory
directory=$(dirname "$0")
chmod -R +x $directory
cd $directory

echo $(pwd)

case "$test_type" in
    "lexer")
        echo "Updating lexer tests..."
        rm -rf 10_lexer_tests/12_expected_results/*
        cp -r 10_lexer_tests/13_actual_results/* 10_lexer_tests/12_expected_results
    ;;
    "parser")
        echo "Updating parser tests..."
        rm -rf 20_parser_tests/22_expected_results/*
        cp -r 20_parser_tests/23_actual_results/* 20_parser_tests/22_expected_results
    ;;
    "code_gen")
        echo "Updating code_gen tests..."
        rm -rf 30_code_gen_tests/32_expected_results/*
        cp -r 30_code_gen_tests/33_actual_results/* 30_code_gen_tests/32_expected_results
    ;;
    *)
        echo "Invalid test type. Please use 'lexer', 'parser' or 'code_gen'."
    ;;
esac