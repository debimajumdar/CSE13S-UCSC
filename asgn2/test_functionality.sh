#!/bin/bash

# Test script for hangman.c functionality

# Function to run the hangman binary with a given secret phrase
function run_hangman() {
    ./hangman.c "$1"
}

# Test Case 1: Correct usage with a single-word secret
echo "Test Case 1: Single-word secret"
run_hangman "apple"

# Test Case 2: Correct usage with a multi-word secret (quoted)
echo "Test Case 2: Multi-word secret"
run_hangman "open ai"

# Test Case 3: Incorrect usage - Missing command-line argument
echo "Test Case 3: Incorrect usage - Missing argument"
./hangman.c

# Test Case 4: Incorrect usage - Too many command-line arguments
echo "Test Case 4: Incorrect usage - Too many arguments"
./hangman.c "apple" "extra_argument"

# Test Case 5: Valid guess leading to win
echo "Test Case 5: Valid guess leading to win"
run_hangman "hangman"


echo "All test cases executed successfully."
