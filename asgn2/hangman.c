#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool all_letters_guessed(const char *secret, const char *guessed) {
    for (int i = 0; secret[i] != '\0'; ++i) {
        if (strchr(punctuation, secret[i]) == NULL
            && !string_contains_character(guessed, secret[i])) {
            return false;
        }
    }
    return true;
}

int compare_characters(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}

void print_game_state(const char *arts[], int gallows_state, const char *secret,
    const char *guessed_letters, const char *eliminated_letters) {

    printf("%s", CLEAR_SCREEN);
    printf("%s", arts[gallows_state]);
    printf("    Phrase: ");

    for (size_t i = 0; secret[i] != '\0'; ++i) {
        char current_char = secret[i];
        if (strchr(punctuation, current_char) != NULL
            || string_contains_character(guessed_letters, current_char) || current_char == ' ') {
            printf("%c", current_char);
        } else {
            printf("_");
        }
    }
    // printf("\n");

    // Create a non-const array for sorting
    char temp_eliminated_letters[MAX_LENGTH];
    strcpy(temp_eliminated_letters, eliminated_letters);

    qsort(
        temp_eliminated_letters, strlen(temp_eliminated_letters), sizeof(char), compare_characters);
    printf("Eliminated: %s\n", temp_eliminated_letters);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments\n");
        fprintf(stderr, "usage: ./hangman <secret word or phrase>\n");
        fprintf(stderr, "if the secret is multiple words, you must quote it\n");
        return 1;
    }
    const char *secret = argv[1];

    if (!validate_secret(secret)) {
        return 1;
    }

    int guesses = 0;
    char guessed_letters[MAX_LENGTH] = { '\0' };
    char eliminated_letters[MAX_LENGTH] = { '\0' };

    while (guesses < LOSING_MISTAKE && !all_letters_guessed(secret, guessed_letters)) {
        print_game_state(arts, guesses, secret, guessed_letters, eliminated_letters);

        char guess = read_letter();

        if (!is_lowercase_letter(guess)) {
            printf("Invalid input. Please enter a lowercase letter.\n");
            continue;
        } else {
            if (string_contains_character(guessed_letters, guess)) {
                printf("Letter already guessed. Guess again.\n");
                continue;
            }

            if (!string_contains_character(secret, guess)) {
                eliminated_letters[strlen(eliminated_letters)] = guess;
                eliminated_letters[strlen(eliminated_letters) + 1] = '\0';
                guesses++;
            }

            guessed_letters[strlen(guessed_letters)] = guess;
            guessed_letters[strlen(guessed_letters) + 1] = '\0';
        }
    }

    print_game_state(arts, guesses, secret, guessed_letters, eliminated_letters);

    if (all_letters_guessed(secret, guessed_letters)) {
        printf("\nYou win! The secret phrase was: %s\n", secret);
        return 0;
    } else {
        printf("\nYou lose! The secret phrase was: %s\n", secret);
        return 0;
    }
}
