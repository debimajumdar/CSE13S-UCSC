# Creates the example output
echo NOT ENOUGH INPUT > expected.txt

# Runs the program
./calc 3 > output.txt 

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Accepted only one input value!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test does not find that 3+4 = 8: PASS"

# Cleans up files created
rm output.txt 
rm expected.txt
exit 0
