# Creates the example output
echo "2 3 +" > input.txt
echo 5 > expected_output.txt

# Runs the program
./calc < input.txt > output.txt

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code: $?"
    rm input.txt expected_output.txt output.txt
    exit 1
fi

# Ensures the output matches the expected output
diff output.txt expected_output.txt
if [ $? -ne 0 ]; then
    echo "Test failed: Output does not match expected output."
    rm input.txt expected_output.txt output.txt
    exit 1
fi

# Prints a message on success
echo "Test passed: Output matches expected output."

# Cleans up files created
rm input.txt expected_output.txt output.txt
exit 0
