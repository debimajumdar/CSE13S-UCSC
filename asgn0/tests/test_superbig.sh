# Creates the example output
echo 1022 > expected.txt

# Runs the program
./calc 511 511 > output.txt 

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
    echo "Somehow, 511+511 is not equal to 1022!!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "511+511 = 1022: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
