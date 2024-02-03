#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return c >= 'a' && c <= 'z';
}

char read_letter(void) {
    char guess;

    do {
        guess = getchar();
    } while (guess == '\n');

    // Clear the input buffer
    while (getchar() != '\n' && getchar() != EOF)
        ;

    return guess;
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

bool validate_secret(const char *secret) {
    int secret_length = strlen(secret);

    if (secret_length > MAX_LENGTH) {
        fprintf(stdout, "the secret phrase is over 256 characters\n");
        exit(1);
    }

    for (int i = 0; i < secret_length; i++) {
        char c = secret[i];
        if (!is_lowercase_letter(c) && c != ' ' && c != '-' && c != '\'') {
            printf("invalid character: '%c'\n", c);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }

    return true;
}
void initialize_game(char *secret, char *phrase) {
    int secret_length = strlen(secret);
    for (int i = 0; i < secret_length; i++) {
        char c = secret[i];
        if (c == ' ' || c == '-' || c == '\'') {
            phrase[i] = c;
        } else {
            phrase[i] = '_';
        }
    }
    phrase[secret_length] = '\0';
}

void update_phrase(const char *secret, char *phrase, char guess) {
    int phrase_length = strlen(phrase);
    int secret_length = strlen(secret);
    int length = (phrase_length < secret_length) ? phrase_length : secret_length;

    for (int i = 0; i < length; i++) {
        if (secret[i] == guess) {
            phrase[i] = guess;
        }
    }
}

int compare_characters(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}

void print_game_state(
    const char *arts[], int gallows_state, const char *phrase, const char *eliminated) {
    char sorted_eliminated[26];
    strcpy(sorted_eliminated, eliminated);
    qsort(sorted_eliminated, strlen(sorted_eliminated), sizeof(char), compare_characters);

    printf(CLEAR_SCREEN);
    printf("%s\n\n", arts[gallows_state]);
    printf("    Phrase: %s\n", phrase);
    printf("Eliminated: %s\n", sorted_eliminated);
    printf("\n");
}
