# Creates the example output
echo TOO BIG > expected.txt

# Runs the program
./calc 534 9 > output.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the numbers are tooooo big!!!!"
    rm expected.txt
    rm output.txt
    exit 1
fi

# Prints a message on success
echo "Test does not go over 512 limit: PASS"

# Cleans up files created
rm expected.txt
rm output.txt
exit 0
