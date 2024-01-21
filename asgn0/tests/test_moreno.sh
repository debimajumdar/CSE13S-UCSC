# Creates the example output
echo NOT ENOUGH INPUT > output.txt

# Runs the program
./calc 8 0 2 > expected.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "no zeros" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the output of 8+0+2 is not 10!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that 8+0+2=10 : PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
