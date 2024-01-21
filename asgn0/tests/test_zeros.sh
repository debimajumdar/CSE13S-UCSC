# Creates the example output
echo 8 > output.txt

# Runs the program
./calc 8 0 > expected.txt 

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "no zeros" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the output of 8+0 is 8!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that 8+0 = 8: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
