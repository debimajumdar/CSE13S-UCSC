#include "names.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } DiceResult;

const DiceResult dice[6] = {DOT, DOT, DOT, LEFT, CENTER, RIGHT};

int main(void) {
  int totalPlayers;

  printf("Number of players (3 to 10)? ");
  int scanfResult = scanf("%d", &totalPlayers);

  if (scanfResult < 1 || totalPlayers < 3 || totalPlayers > 10) {
    fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
    totalPlayers = 3;
  }

  unsigned randomSeed;
  printf("Random-number seed? ");
  scanfResult = scanf("%u", &randomSeed);

  if (scanfResult < 1) {
    fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    randomSeed = 4823;
  }
  srandom(randomSeed);

  int playerChips[totalPlayers];
  for (int i = 0; i < totalPlayers; i++) {
    playerChips[i] = 3;
  }

  int currentPlayerIndex = 0;
  while (1) {
    int rolls = playerChips[currentPlayerIndex] > 3
                    ? 3
                    : playerChips[currentPlayerIndex];

    if (rolls > 0) {
      printf("%s:", player_name[currentPlayerIndex]);
    }

    for (int i = 0; i < rolls; i++) {
      DiceResult roll = dice[random() % 6];
      switch (roll) {
      case LEFT:
        playerChips[currentPlayerIndex]--;
        playerChips[(currentPlayerIndex + 1) % totalPlayers]++;
        break;
      case CENTER:
        playerChips[currentPlayerIndex]--;
        break;
      case RIGHT:
        playerChips[currentPlayerIndex]--;
        playerChips[(currentPlayerIndex - 1 + totalPlayers) % totalPlayers]++;
        break;
      default:
        break;
      }
    }

    if (rolls > 0) {
      printf(" ends her turn with %d\n", playerChips[currentPlayerIndex]);
    }

    int winnersCount = 0, lastWinnerIndex = 0;
    for (int i = 0; i < totalPlayers; i++) {
      if (playerChips[i] > 0) {
        winnersCount++;
        lastWinnerIndex = i;
      }
    }

    if (winnersCount == 1) {
      printf("%s won!\n", player_name[lastWinnerIndex]);
      break;
    }

    currentPlayerIndex = (currentPlayerIndex + 1) % totalPlayers;
  }
  return 0;
}
