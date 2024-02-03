#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>

char read_letter(void);
bool string_contains_character(const char *s.char c);
bool validate_secret(const char *secret);
bool is_lowercase_letter(char c);

void test_read_letter() {
    printf("Testing read_letter:\n");
    printf("Test 1: Enter 'n'\n");
    fflush(stdin);
    char result = read_letter();
    printf("Results: %s\n", (result == 'n') ? "Pass" : "Fail");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    prinf("\n");
}

void test string_contain_character() {
    printf("Testing string_contains_character:\n");
    const char *test_string = "pug";
    printf("Test 1: %s\n", string_contains_character(test_string, 'u') ? "Pass" : "Fail");
    printf("Test 2: %s\n", string_contains_character(test_string, 'd') ? "Pass" : "Fail");
    printf("Test 3: %s\n", string_contains_character(test_string, '0') ? "Pass" : "Fail");
    printf("Test 4: %s\n", string_contains_character(test_string, '@') ? "Pass" : "Fail");
    const char *test_string = " ";
    printf("Test 5: %s\n", string_contains_character(test_string, 'd') ? "Pass" : "Fail");
}

void validate_secret(const char *secret);
printf("Testing validate_secret:\n");
const char *validsecret = "pugs are the cutest";
printf("Test 1: %s\n", validate_secret(validsecret) ? "Pass" : "Fail");
const char *validsecret
    = "pugs are the cutest and it should be mandatory for everyone to get one if not you go to "
      "jail. Pugs are very friendly and have a lot of personality. They are lap dogs and will love "
      "children and everyone that takes care of them. I am going to get a pug once I graduate "
      "college and have my own place. Although if you don't get a pug every family should get an "
      "animal whether its a dog, cat, rabbit, etc.";
printf("Test 2: %s\n", validate_secret(validsecret) ? "Pass" : "Fail");
}

void test_is_lowercase_letter() {
    printf("Testing is_lowercase_letter:\n");
    printf("Test 1: %s\n", is_lowercase_letter('a') ? "Pass" : "Fail");
    printf("Test 2: %s\n", is_lowercase_letter('A') ? "Pass" : "Fail");
    printf("Test 3: %s\n", is_lowercase_letter('w') ? "Pass" : "Fail");
    printf("Test 4: %s\n", is_lowercase_letter('W') ? "Pass" : "Fail");
}
int main() {
    test_is_lowercase_letter();
    test_validate_secret();
    test_string_contains_character();
    test_read_letter();
    return 0;
}