# Runs the program with invalid input
./calc 10 a > result.txt

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "Invalid input test failed: Program should not exit successfully"
    rm result.txt
    exit 1
fi

# Ensures the error message is displayed
if ! grep -q "Invalid input" result.txt; then
    echo "Invalid input test failed: Error message not found"
    rm result.txt
    exit 1
fi

# Prints a message on success
echo "Invalid input test: PASS"

# Cleans up files created
rm result.txt
exit 0
