# Runs the program with addition operation
./calc 3 4 > result.txt

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code: $?"
    rm result.txt
    exit 1
fi

# Ensures the result is correct
if ! grep -q "7" result.txt; then
    echo "Addition operation failed"
    rm result.txt
    exit 1
fi

# Prints a message on success
echo "Addition operation test: PASS"

# Cleans up files created
rm result.txt
exit 0
