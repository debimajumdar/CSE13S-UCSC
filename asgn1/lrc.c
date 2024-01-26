#include "names.h" // Include header file containing player names

#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

int main(void) {
    int num_players;

    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    unsigned seed; // Variable for the random seed
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        seed = 4823;
    }
    srandom(seed);

    int chips[num_players];
    for (int i = 0; i < num_players; i++) {
        chips[i] = 3;
    }

    int currentPlayer = 0;
    while (1) {
        int diceToRoll = chips[currentPlayer] > 3 ? 3 : chips[currentPlayer];

        if (diceToRoll > 0) {
            printf("%s:", player_name[currentPlayer]); // Print the current player's name
        }

        for (int i = 0; i < diceToRoll; i++) {
            Position roll = die[random() % 6]; // Generate a random roll
            switch (roll) {
            case LEFT:
                chips[currentPlayer]--;
                chips[(currentPlayer + 1) % num_players]++;
                break;
            case CENTER: chips[currentPlayer]--; break;
            case RIGHT:
                chips[currentPlayer]--;
                chips[(currentPlayer - 1 + num_players) % num_players]++;
                break;
            default: break;
            }
        }

        if (diceToRoll > 0) {
            printf(" ends her turn with %d\n", chips[currentPlayer]);
        }

        int winners = 0, lastPlayerWithChips = 0;
        for (int i = 0; i < num_players; i++) {
            if (chips[i] > 0) {
                winners++;
                lastPlayerWithChips = i;
            }
        }

        if (winners == 1) {
            printf("%s won!\n", player_name[lastPlayerWithChips]);
            break;
        }

        currentPlayer = (currentPlayer + 1) % num_players;
    }
    return 0;
}
