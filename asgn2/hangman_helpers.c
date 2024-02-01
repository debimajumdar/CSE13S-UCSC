#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>

bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool validate_secret(const char *secret) {
    int length = 0;
    if (secret == NULL) {
        printf("Invalid secret: NULL\n");
        return false;
    }
    while (secret[length] != '\0') {
        length++;
    }
    if (length > 256) {
        printf("Invalid secret: Phrase is over 256 characters.\n");
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (!is_lowercase_letter(secret[i]) && secret[i] != ' ' && secret[i] != '\''
            && secret[i] != '-') {
            printf("Invalid character: '%c'\n", secret[i]);
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    int c;
    printf("Guess a letter: ");
    c = getchar();
    while (1) {
        if (c == '\n') {
            continue;
        }
        while (getchar() != '\n') {
        }
        return (char) c;
    }
}
