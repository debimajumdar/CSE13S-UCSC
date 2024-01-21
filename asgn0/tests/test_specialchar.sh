# Creates the example output
echo BAD INPUT > output.txt

# Runs the program
./calc 3 @> expected.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "failed badinput" $?
    rm expected.txt
    rm output.txt
    exit 1
fi

# Ensures differences *are* found
diff expected.txt output.txt
if [ $? -ne 0 ]; then
    echo "Somehow, a special character is accepted in the second slot!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test does not accept special characters in second slot : FAIL"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
