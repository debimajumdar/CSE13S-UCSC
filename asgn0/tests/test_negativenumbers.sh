# Creates the example output
echo -1 > negative.txt

# Runs the program
./calc 3 -4 > 3.4.txt 

# Ensures differences *are* found
diff 3.4.txt negative.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the output of -2 + 1 is not equal to -1!"
    rm 3.4.txt
    rm negative.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that -2+1 = -1: PASS"

# Cleans up files created
rm 3.4.txt
rm negative.txt
exit 0