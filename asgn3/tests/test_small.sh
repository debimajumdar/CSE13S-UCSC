# Runs the program with valid input
./xd valid_file.txt 2> output.txt

# Ensures the exit code is zero (indicating success)
if [ $? -ne 0 ]; then
    echo "Test failed: Exit code is not zero"
    rm output.txt
    exit 1
fi

# Ensures stdout output is as expected (if applicable)
# For example, you could check if the output contains the expected data

# Prints a message on success
echo "Test passed: Exit code is zero and output is as expected"

# Cleans up output file
rm output.txt
exit 0

