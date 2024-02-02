#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,
            "wrong number of arguments\nusage: %s <secret word or phrase>\nif the secret is "
            "multiple words, you must quote it\n",
            argv[0]);
        return 1;
    }
    const char *user_secret = argv[1]; // The secret word is the second argument
    if (!(validate_secret(user_secret))) {
        return 1;
    }
    char secret[MAX_LENGTH + 1] = { 0 };
    char phrase[MAX_LENGTH + 1] = { 0 };
    char eliminated[26] = { 0 }; // An array to store eliminated letters
    int eliminated_count = 0;
    int incorrect_attempts = 0;
    bool game_over = false;
    int gallows_state = 0;
    strncpy(secret, user_secret, MAX_LENGTH);

    initialize_game(secret, phrase);

    while (!game_over) {
        char guess;
        print_game_state(arts, gallows_state, phrase, eliminated);
        while (1) {
            printf("Guess a letter: ");
            guess = read_letter();

            if (!is_lowercase_letter(guess)) {
                continue;
            } else if (string_contains_character(eliminated, guess)
                       || string_contains_character(phrase, guess)) {
                continue;
            } else {
                break; // Valid letter entered
            }
        }
        if (string_contains_character(secret, guess)) {
            update_phrase(secret, phrase, guess);
            if (strcmp(user_secret, phrase) == 0) {
                print_game_state(arts, gallows_state, phrase, eliminated);

                printf("You win! The secret phrase was: %s\n", secret);
                game_over = true;
            }
        } else {
            eliminated[eliminated_count++] = guess;
            incorrect_attempts++;
            gallows_state = incorrect_attempts;

            if (incorrect_attempts == LOSING_MISTAKE) {
                print_game_state(arts, gallows_state, phrase, eliminated);

                printf("You lose! The secret phrase was: %s\n", secret);
                game_over = true;
            }
        }
    }
    return 0;
}
