#!/bin/bash

# Get script directory
dir=$(realpath $(dirname $0))
echo "dir " $dir

# Count the number of test files in the directory
file_count=$(ls $dir/31_code_examples/*.atm 2>/dev/null | wc -l)
files=$(ls $dir/31_code_examples/*.atm 2>/dev/null)

# Check if there are any test files
if [ "$file_count" -eq 0 ]; then
    echo "No test files found."
    exit 0
fi

# Delete previous test results
echo "Clean posible previous results"
rm -rf $dir/33_actual_results/*

# Loop through the test files
for test_file in $files; do
    # Substitute .atm with .log
    just_test_file=$(basename "$test_file")
    echo $just_test_file
    just_log_file="${just_test_file%.atm}.log"
    log_file_expect=$dir/32_expected_results/$just_log_file
    log_file_actual=$dir/33_actual_results/$just_log_file

    # Check if the test file exists
    if [ -f "$test_file" ]; then
        echo "Running $test_file..."
        ./bin/atom $test_file f:dl > $log_file_actual

        # Compare each actual result with the expected result
        echo "Comparing $log_file_actual and $log_file_expect contents"
        if cmp -s $log_file_actual $log_file_expect; then
            echo "Success"
        else
            echo "Failed"
            diff $log_file_actual $log_file_expect
        fi
    else
        echo "$test_file not found."
    fi
done
