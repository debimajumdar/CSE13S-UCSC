#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>

bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool validate_secret(const char *secret) {
    if (secret == NULL) {
        printf("Invalid secret: NULL\n");
        return false;
    }

    int length = 0;
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

    do {
        printf("Guess a letter: ");
        c = getchar();
        while (getchar() != '\n')
            ;
    } while (c == '\n');

    return (char) c;
}
