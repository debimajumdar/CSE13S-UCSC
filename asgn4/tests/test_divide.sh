# Runs the program with division operation
./calc 10 2 > result.txt

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code: $?"
    rm result.txt
    exit 1
fi

# Ensures the result is correct
if ! grep -q "5" result.txt; then
    echo "Division operation failed"
    rm result.txt
    exit 1
fi

# Prints a message on success
echo "Division operation test: PASS"

# Cleans up files created
rm result.txt
exit 0
