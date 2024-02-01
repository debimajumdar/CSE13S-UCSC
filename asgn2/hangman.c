#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void play_game(const char *secret) {
    char guessed_letters[27] = { 0 }; // array for ALL guessed letters
    char incorrect_chars[27] = { 0 }; // array for ONLY WRONG character inputs
    int mistakes = 0; // increments

    while (!is_game_over(secret, guessed_letters, mistakes)) {
        printf(CLEAR_SCREEN);

        printf("%s", arts[mistakes]);
        phrase(secret, guessed_letters);
        show_incorrect_guesses(incorrect_chars);
        printf("\n");

        char guess = read_letter();
        while (string_contains_character(guessed_letters, guess) || !is_lowercase_letter(guess)) {
            guess = read_letter(); // prompt user until a valid guess is received
        }

        strncat(guessed_letters, &guess, 1); // append guess to guessed letters

        if (!string_contains_character(secret, guess)) {
            if (is_lowercase_letter(guess)) {
                strncat(incorrect_chars, &guess, 1);
            }
            mistakes++;
        }
    }

    if (mistakes == LOSING_MISTAKE) {
        printf(CLEAR_SCREEN);
        printf("%s", arts[mistakes]);
        phrase(secret, guessed_letters);
        show_incorrect_guesses(incorrect_chars);
        printf("\n");
        printf("You lose! The secret phrase was: %s\n", secret);
    } else if (has_guessed_all(secret, guessed_letters)) {
        printf(CLEAR_SCREEN);
        printf("%s", arts[mistakes]);
        phrase(secret, guessed_letters);
        show_incorrect_guesses(incorrect_chars);
        printf("\n");
        printf("You win! The secret phrase was: %s\n", secret);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,
            "wrong number of arguments\nusage: ./hangman <secret word or phrase>\nif the secret "
            "is multiple words, you must quote it\n");
        exit(1);
    }

    if (!validate_secret(argv[1])) {
        exit(1);
    }

    play_game(argv[1]);
    return 0;
}
