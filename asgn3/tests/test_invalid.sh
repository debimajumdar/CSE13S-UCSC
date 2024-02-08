# Runs the program with an invalid file name
./xd invalid_file.txt 2> output.txt

# Ensures the exit code is non-zero (indicating failure)
if [ $? -eq 0 ]; then
    echo "Test failed: Exit code is zero"
    rm output.txt
    exit 1
fi

# Ensures stderr output is as expected
if ! grep -q "No such file or directory" output.txt; then
    echo "Test failed: Error message is not as expected"
    rm output.txt
    exit 1
fi

# Prints a message on success
echo "Test passed: Error message is as expected"

# Cleans up output file
rm output.txt
exit 0
