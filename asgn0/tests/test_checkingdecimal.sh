# Creates the example output
echo BAD INPUT > expected.txt

# Runs the program
./calc 3.5 4.4 > output.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "do decimals work" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff expected.txt output.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the decimals are adding?!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test does not accpet decimals: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
