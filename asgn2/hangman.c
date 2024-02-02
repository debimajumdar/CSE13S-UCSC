// hangman.c

#include "hangman_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaration for the missing function
bool has_guessed_all(const char *secret, const char *guessed_letters);
void initialize_game(const char *secret, char *phrase);
bool is_game_over(const char *secret, const char *phrase, const char *eliminated, int incorrect_attempts);
void print_game_state(const char *arts[], int gallows_state, const char *phrase, const char *eliminated);
void update_phrase(const char *secret, char *phrase, char guess);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,
            "wrong number of arguments\nusage: %s <secret word or phrase>\nif the secret is "
            "multiple words, you must quote it\n",
            argv[0]);
        return 1;
    }

    const char *user_secret = argv[1];
    if (!validate_secret(user_secret)) {
        return 1;
    }

    char secret[MAX_LENGTH + 1] = { 0 };
    char phrase[MAX_LENGTH + 1] = { 0 };
    char eliminated[26] = { 0 };
    int eliminated_count = 0;
    int incorrect_attempts = 0;
    int gallows_state = 0;

    strncpy(secret, user_secret, MAX_LENGTH);
    initialize_game(secret, phrase);

    while (!is_game_over(secret, phrase, eliminated, incorrect_attempts)) {
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
                break;
            }
        }

        if (string_contains_character(secret, guess)) {
            update_phrase(secret, phrase, guess);
            if (has_guessed_all(secret, phrase)) {
                print_game_state(arts, gallows_state, phrase, eliminated);
                printf("You win! The secret phrase was: %s\n", secret);
                break;
            }
        } else {
            eliminated[eliminated_count++] = guess;
            incorrect_attempts++;
            gallows_state = incorrect_attempts;

            if (incorrect_attempts == LOSING_MISTAKE) {
                print_game_state(arts, gallows_state, phrase, eliminated);
                printf("You lose! The secret phrase was: %s\n", secret);
                break;
            }
        }
    }

    return 0;
}
