# Creates the example output
echo TOO BIG > expected.txt

# Runs the program
./calc -511 -5 > output.txt 

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
    echo "Somehow, -511-511 doesn't equal -1022!!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test does -511-511 = -1022: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
