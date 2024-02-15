//Filename: calc.c
//Author name: Debi Majumdar

#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int choice;
    bool use_advanced_math = true;

    // Parsing command line options
    while ((choice = getopt(argc, argv, "hm")) != -1) {
        switch (choice) {
        case 'm': use_advanced_math = false; break; // Disable advanced math functions
        case 'h': printf(USAGE, "./calc"); return 0; // Display help message
        case '?': break; // Handle unknown options
        }
    }

    // Main loop for processing expressions
    while (1) {
        char expression[1024];
        char *token_pointer;
        bool has_error = false;
        double storage;

        // Prompting user for input
        fprintf(stderr, "> ");
        if (fgets(expression, sizeof(expression), stdin) != NULL) {
            size_t expression_length = strlen(expression);

            if (expression_length > 0 && expression[expression_length - 1] == '\n') {
                expression[expression_length - 1] = '\0';
            }
        } else {
            return 0; // End program if no input is provided
        }

        // Tokenizing input expression
        const char *current_token = strtok_r(expression, " ", &token_pointer);

        while (current_token != NULL && !has_error) {
            int is_binary = 0, is_unary = 0;
            int token_length = (int) strlen(current_token);

            // Checking if token is a binary operator
            for (int i = 0; i < 256; i++) {
                if (binary_operators[i] != NULL && i == *current_token && token_length == 1) {
                    is_binary = 1;
                    break;
                }
            }
            // Checking if token is a unary operator
            for (int i = 0; i < 256; i++) {
                if (my_unary_operators[i] != NULL && i == *current_token && token_length == 1) {
                    is_unary = 1;
                    break;
                }
            }

            // Parsing numeric value or handling invalid token
            if (!parse_double(current_token, &storage) && is_binary == 0 && is_unary == 0) {
                if (strlen(current_token) == 1) {
                    fprintf(stderr, ERROR_BAD_CHAR, current_token[0]);
                    has_error = true;
                } else {
                    fprintf(stderr, ERROR_BAD_STRING, current_token);
                    has_error = true;
                }
            }
            if (parse_double(current_token, &storage)) {
                if (!stack_push(storage)) {
                    has_error = true;
                }
            }

            // Applying binary operator if applicable
            if (is_binary == 1) {
                switch (current_token[0]) {
                case '+':
                    if (!apply_binary_operator(operator_add)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case '-':
                    if (!apply_binary_operator(operator_sub)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case '*':
                    if (!apply_binary_operator(operator_mul)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case '/':
                    if (!apply_binary_operator(operator_div)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case '%':
                    if (!apply_binary_operator(fmod)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                }
            }
            // Applying unary operator if applicable (using advanced math functions)
            if (is_unary == 1 && use_advanced_math == true) {
                switch (current_token[0]) {
                case 's':
                    if (!apply_unary_operator(Sin)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'c':
                    if (!apply_unary_operator(Cos)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 't':
                    if (!apply_unary_operator(Tan)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'a':
                    if (!apply_unary_operator(Abs)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'r':
                    if (!apply_unary_operator(Sqrt)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                }
            }
            // Applying unary operator if applicable (using standard math functions)
            if (is_unary == 1 && use_advanced_math == false) {
                switch (current_token[0]) {
                case 's':
                    if (!apply_unary_operator(sin)) {

                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'c':
                    if (!apply_unary_operator(cos)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 't':
                    if (!apply_unary_operator(tan)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'a':
                    if (!apply_unary_operator(fabs)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                case 'r':
                    if (!apply_unary_operator(sqrt)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        has_error = true;
                    }
                    break;
                }
            }
            current_token = strtok_r(NULL, " ", &token_pointer);
        }

        // Printing result or error message
        if (!has_error) {
            stack_print();
            printf("%c", '\n');
        }

        // Clearing the stack for the next expression
        stack_clear();
    }

    return 0;
}
