# Creates the example output
echo -2 > expected.txt

# Runs the program
./calc -6 4 > output.txt 

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "did not work" $?
    rm expected.txt
    rm output.txt
    exit 1
fi

# Ensures differences *are* found
diff expected.txt output.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the output does not say -6 +4 = -2!!"
    rm expected.txt
    rm output.txt
    exit 1
fi

# Prints a message on success
echo "Test does -6 + 4 = -2: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
