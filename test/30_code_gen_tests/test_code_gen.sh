#!/bin/bash

# Get script directory
directory=$(dirname "$0")

# Count the number of test files in the directory
file_count=$(ls $directory/31_code_examples/test_*.atm 2>/dev/null | wc -l)

# Check if there are any test files
if [ "$file_count" -eq 0 ]; then
    echo "No test files found."
    exit 1
fi

# Loop through the test files based on the count
for i in $(seq 1 $file_count)
do
    # Format the number to be two digits
    num=$(printf "%02d" $i)
    test_file="$directory/31_code_examples/test_${num}.atm"
    
    # Check if the test file exists
    if [ -f "$test_file" ]; then
        echo "Running $test_file..."
        ./bin/atom $test_file > $directory/33_actual_results/test_$num.log
    else
        echo "$test_file not found."
    fi
done