#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool validate_secret(const char *secret) {
    if (secret != NULL) {
        size_t length = strlen(secret);

        if (length > 256) {
            printf("invalid secret: Phrase is over 256 characters.\n");
            return false;
        }

        for (size_t i = 0; i < length; ++i) {
            char current_character = secret[i];

            if (!((current_character >= 'a' && current_character <= 'z') || current_character == ' '
                    || current_character == '-' || current_character == '\''
                    || current_character == '\0')) {
                printf("invalid character: '%c'\n", current_character);
                return false;
            }
        }
        return true;
    } else {
        printf("invalid secret: NULL\n");
        return false;
    }
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
    printf("\nGuess a letter: ");
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
