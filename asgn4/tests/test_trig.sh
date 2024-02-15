# Runs the program with trigonometric function
./calc -m 0 > result.txt

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code: $?"
    rm result.txt
    exit 1
fi

# Ensures the result is correct
if ! grep -q "0" result.txt; then
    echo "Trigonometric function test failed"
    rm result.txt
    exit 1
fi

# Prints a message on success
echo "Trigonometric function test: PASS"

# Cleans up files created
rm result.txt
exit 0
