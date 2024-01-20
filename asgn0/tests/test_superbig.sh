# Creates the example output
echo 1234 > expected.txt

# Runs the program
./calc 617 617 > output.txt 

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Somehow, 617+617 is not equal to 1234!!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "617+617 = 1234: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
