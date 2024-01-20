# Creates the example output
echo TOO BIG > expected.txt

# Runs the program
./calc -420 -4 > output.txt 

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
    echo "Somehow, -420-420 doesn't equal -840!!"
    rm expected.txt
    rm output.txt
    exit 1
fi

# Prints a message on success
echo "Test does -420-420 = -840: PASS"

# Cleans up files created
rm expected.txt
rm output.txt
exit 0
