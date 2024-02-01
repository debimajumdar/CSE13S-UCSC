#!/ bin / bash

#Define colors for better output
GREEN = '\033[0;32m' RED = '\033[0;31m' NC = '\033[0m' #No Color

#Function to run a test case
    run_test() {
    test_name = $1 expected_output = $2 input = $3

#Run the program with input and capture the output
        actual_output
        = $(echo - e "$input" |./ hangman)

#Compare the actual output with the expected output
            if["$actual_output" = "$expected_output"];
    then echo - e "${GREEN}Test $test_name Passed${NC}" else echo
        - e "${RED}Test $test_name Failed${NC}" echo "Expected Output:" echo "$expected_output" echo
            "Actual Output:" echo "$actual_output" fi
}

#Test Case 1 : Add more test cases as needed
run_test "Test Case 1"
         "Expected Output for Test Case 1"
         "Input for Test Case 1" run_test "Test Case 2"
         "Expected Output for Test Case 2"
         "Input for Test Case 2" run_test "Test Case 3"
         "Expected Output for Test Case 3"
         "Input for Test Case 3"

#Add more test cases as needed

#Cleanup(if necessary)
#rm any_generated_files

#Exit with status based on test results
#If any test fails, the script will exit with a non - zero status
#This is useful when integrating with CI / CD systems
    exit 0
