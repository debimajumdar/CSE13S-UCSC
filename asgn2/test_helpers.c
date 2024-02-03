#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>

void test_is_lowercase_letter() {
    printf("Testing is_lowercase_letter:\n");
    printf("Test 1: %s\n", is_lowercase_letter('a') ? "Pass" : "Fail");
    printf("Test 2: %s\n", is_lowercase_letter('z') ? "Pass" : "Fail");
    printf("Test 3: %s\n", !is_lowercase_letter('A') ? "Pass" : "Fail");
    printf("Test 4: %s\n", !is_lowercase_letter('Z') ? "Pass" : "Fail");
    printf("Test 5: %s\n", !is_lowercase_letter('1') ? "Pass" : "Fail");
    printf("\n");
}

void test_validate_secret() {
    printf("Testing validate_secret:\n");
    const char *validSecret = "hangman is fun";
    printf("Test 1: %s\n", validate_secret(validSecret) ? "Pass" : "Fail");
    const char *invalidSecret
        = "a very long secret phrase that exceeds the limit of 256 characters";
    printf("Test 2: %s\n", !validate_secret(invalidSecret) ? "Pass" : "Fail");
    printf("\n");
}

void test_string_contains_character() {
    printf("Testing string_contains_character:\n");
    const char *testString = "hangman";
    printf("Test 1: %s\n", string_contains_character(testString, 'a') ? "Pass" : "Fail");
    printf("Test 2: %s\n", !string_contains_character(testString, 'z') ? "Pass" : "Fail");
    const char *emptyString = " ";
    printf("Test 3: %s\n", !string_contains_character(emptyString, 'a') ? "Pass" : "Fail");
    printf("\n");
}
void test_read_letter() {
    printf("Testing read_letter:\n");
    printf("Test 1: Enter 'a' and press Enter\n");
    // Flush the input buffer before reading a character
    fflush(stdin);
    char result1 = read_letter();
    printf("Result: %s\n", (result1 == 'a') ? "Pass" : "Fail");
    // Consume any additional characters in the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    printf("\n");
}

int main() {
    test_is_lowercase_letter();
    test_validate_secret();
    test_string_contains_character();
    test_read_letter();
    return 0;
}
