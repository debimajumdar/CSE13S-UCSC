#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void arrange_uncovered_phrase(const char *secret, const char *guessed_list) {
    printf("    Phrase: ");
    for (int i = 0; secret[i] != '\0'; i += 1) {
        if (string_contains_character(guessed_list, secret[i]))
            printf("%c", secret[i]);
        else if (secret[i] == ' ' || secret[i] == '-' || secret[i] == '\'')
            printf("%c", secret[i]);
        else
            printf("_");
    }
    printf("\n");
}

bool phrase_guessed(const char *secret, const char *guessed_list) {
    for (int i = 0; secret[i] != '\0'; i += 1) {
        if (string_contains_character(guessed_list, secret[i]) == false
            && is_lowercase_letter(secret[i]))
            return false;
    }
    return true;
}

bool game_over(const char *secret, const char *guessed_list, int false_guesses) {
    if (false_guesses >= LOSING_MISTAKE)
        return true;
    else if (phrase_guessed(secret, guessed_list) == true)
        return true;
    else
        return false;
}

void print_guessed_incorrectly_list(char *guessed_list) {
    printf("Eliminated: ");

    int letter_count = (int) strlen(guessed_list);
    for (int i = 0; i < letter_count; i += 1) {
        for (int x = 0; x < letter_count - 1 - i; x += 1) {
            if (guessed_list[x] > guessed_list[x + 1]) {
                char throwaway = guessed_list[x];
                guessed_list[x] = guessed_list[x + 1];
                guessed_list[x + 1] = throwaway;
            }
        }
    }

    for (int l = 0; guessed_list[l] != '\0'; l += 1)
        printf("%c", guessed_list[l]);
    printf("\n");
}

int main(int argc, char **argv) {
    //game information
    int incorrect_guesses = 0;
    char already_guessed[26];
    char wrong_letters[26];
    char secret[strlen(argv[1]) + 1];
    if (argc != 2) {
        fprintf(stderr, "if the secret is multiple words, you must quote it");
        exit(1);
    }
    if (validate_secret(argv[1]) == false)
        exit(1);
    strcpy(secret, argv[1]);

    //game loop

    while (game_over(secret, already_guessed, incorrect_guesses) == false) {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[incorrect_guesses]);
        arrange_uncovered_phrase(secret, already_guessed);
        print_guessed_incorrectly_list(wrong_letters);
        printf("\n");

        char current_guess = read_letter();

        while (is_lowercase_letter(current_guess) == false
               || string_contains_character(already_guessed, current_guess))
            current_guess = read_letter();

        strncat(already_guessed, &current_guess, 1);

        if (string_contains_character(secret, current_guess) == false) {
            incorrect_guesses += 1;
            strncat(wrong_letters, &current_guess, 1);
        }
    }

    if (phrase_guessed(secret, already_guessed) == true) {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[incorrect_guesses]);
        arrange_uncovered_phrase(secret, already_guessed);
        print_guessed_incorrectly_list(wrong_letters);
        printf("\n");
        printf("You win! The secret phrase was: %s\n", secret);

    } else if (incorrect_guesses == LOSING_MISTAKE) {
        printf(CLEAR_SCREEN);
        printf("%s\n\n", arts[LOSING_MISTAKE]);
        arrange_uncovered_phrase(secret, already_guessed);
        print_guessed_incorrectly_list(wrong_letters);
        printf("\n");
        printf("You lose! The secret phrase was: %s\n", secret);
    }
}
