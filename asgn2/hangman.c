#include "hangman_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <secret_word_or_phrase>\n", argv[0]);
        return 1;
    }

    // Get the secret word or phrase from the command line
    const char *secret = argv[1];

    // Validate the secret
    if (!validate_secret(secret)) {
        fprintf(stderr, "Invalid secret. Exiting.\n");
        return 1;
    }

    // Initialize game state variables
    char guessedLetters[256] = ""; // Assuming the maximum length of guessed letters is 256
    int wrongAttempts = 0;

    // Implement the main game loop
    while (!is_game_over(secret, guessedLetters, wrongAttempts)) {
        // Print the current game state
        phrase(secret, guessedLetters);
        show_incorrect_guesses(guessedLetters);

        // Get a letter from the user
        char guess = read_letter();

        // Check if the guessed letter is correct
        if (string_contains_character(secret, guess)) {
            printf("Correct guess: %c\n", guess);
            // Update guessed letters
            if (!string_contains_character(guessedLetters, guess)) {
                strncat(guessedLetters, &guess, 1);
            }
            // Check for win condition
            if (has_guessed_all(secret, guessedLetters)) {
                phrase(secret, guessedLetters);
                printf("You win! The secret phrase was: %s\n", secret);
                return 0;
            }
        } else {
            printf("Incorrect guess: %c\n", guess);
            // Update guessed letters
            if (!string_contains_character(guessedLetters, guess)) {
                strncat(guessedLetters, &guess, 1);
            }
            wrongAttempts++;

            // Check for losing condition
            if (wrongAttempts == LOSING_MISTAKE) {
                phrase(secret, guessedLetters);
                show_incorrect_guesses(guessedLetters);
                printf("You lose! The secret phrase was: %s\n", secret);
                return 0;
            }
        }
    }

    return 0;
}
