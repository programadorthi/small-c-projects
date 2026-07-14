#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DIGITS 3
#define MAX_GUESSES 10

void shuffle(char array[], int len);
void get_secret_num(char secretNum[]);
void get_clues(char guess[], char secretNum[], char clues[]);
bool invalid_guess(char guess[]);

int main(void) {
    printf("Bagels, a deductive logic game.\n");
    printf("By Al Sweigart al@inventwithpython.com\n");
    printf("\n");
    printf("I am thinking of a %d-digit number with no repeated digits.\n", NUM_DIGITS);
    printf("Try to guess what it is. Here are some clues:\n");
    printf("When I say:      That means:\n");
    printf("  Pico           One digit is correct but in the wrong position.\n");
    printf("  Fermi          One digit is correct and in the right position.\n");
    printf("  Bagels         No digit is correct.\n");
    printf("\n");
    printf("For example, if the secret number was 248 and your guess was 843, the\n");
    printf("clues would be Fermi Pico.\n");

    while (1) {
        // BUG01: Asking compiler to "alloc" NUM_DIGITS + 1 char address on stack.
        //  - 0x7fffffffdb38 -- null terminal
        //  - 0x7fffffffdb37
        //  - 0x7fffffffdb36
        //  - 0x7fffffffdb35
        char secretNum[NUM_DIGITS + 1] = {'\0'};
        get_secret_num(secretNum);
        printf("I have thought up a number.\n");
        printf(" You have %d guesses to get it.\n", MAX_GUESSES);

        // BUG01: Asking compiler to "alloc" NUM_DIGITS + 1 char address on stack.
        //  - 0x7fffffffdb34 -- null terminal
        //  - 0x7fffffffdb33
        //  - 0x7fffffffdb32
        //  - 0x7fffffffdb31
        char guess[NUM_DIGITS + 1] = {'\0'};
        int numGuesses = 1;
        while (numGuesses <= MAX_GUESSES) {
            while (invalid_guess(guess)) {
                printf("Guess #%d: ", numGuesses);
                // BUG01: Using scanf() without limits to read input and write memory address.
                //   So, if input length is > NUM_DIGITS it starts overwriting secretNum addresses. BOOM!!!
                //   Ex: 1234 as input scanf() read for characters plus null terminal and the result:
                //     - 0x7fffffffdb35 = \0  -- secretNum address :(
                //     - 0x7fffffffdb34 = 4
                //     - 0x7fffffffdb33 = 3
                //     - 0x7fffffffdb32 = 2
                //     - 0x7fffffffdb31 = 1
                //   Forcing a limit based on NUM_DIGITS to avoid this bug :D
                //scanf("%3s", guess);

                int reads = 0;
                while (1) {
                    char c = getchar();
                    if (c == EOF || c == '\n') {
                        break;
                    }
                    if (reads < NUM_DIGITS) {
                        guess[reads++] = c;
                    }
                }
            }

            char clues[128] = {'\0'};
            get_clues(guess, secretNum, clues);
            printf("%s\n", clues);
            numGuesses += 1;

            if (strcmp(guess, secretNum) == 0) {
                break;
            }
            if (numGuesses > MAX_GUESSES) {
                printf("You ran out of guesses.\n");
                printf("The answer was %s.\n", secretNum);
            }
            guess[0] = '\0';
        }

        printf("Do you want to play again? (yes or no)\n");
        int c = getchar();
        if (c != 'y' && c != 'Y') {
            break;
        }
    }

    printf("Thanks for playing!\n");
    return 0;
}


void shuffle(char array[], int len) {
    // Seeding random generator with a different time
    srand(time(NULL));

    for (int i = 0; i < len; i++) {
        int swap = rand() % len;
        char temp = array[i];
        array[i] = array[swap];
        array[swap] = temp;
    }
}

void get_secret_num(char secretNum[]) {
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    shuffle(numbers, sizeof numbers);

    int i = 0;
    for (; i < NUM_DIGITS; i++) {
        secretNum[i] = numbers[i];
    }
    secretNum[i] = '\0';
}

void get_clues(char guess[], char secretNum[], char clues[]) {
    if (strcmp(guess, secretNum) == 0) {
        strcpy(clues, "You got it!");
        return;
    }

    char *localClues[NUM_DIGITS];
    int cluesIndex = 0;

    int guessLen = strlen(guess);
    int secretNumLen = strlen(secretNum);
    for (int i = 0; i < guessLen; i++) {
        if (i < secretNumLen && guess[i] == secretNum[i]) {
            localClues[cluesIndex++] = "Fermi";
        } else {
            for (int j = 0; j < secretNumLen; j++) {
                if (guess[i] == secretNum[j]) {
                    localClues[cluesIndex++] = "Pico";
                    break;
                }
            }
        }
    }

    if (cluesIndex == 0) {
        strcpy(clues, "Bagels");
    } else {
        for (int i = 0; i < cluesIndex - 1; i++) {
            for (int j = i + 1; j < cluesIndex; j++) {
                char *left = localClues[i];
                char *right = localClues[j];
                if (left[0] > right[0]) {
                    char *temp = left;
                    localClues[i] = right;
                    localClues[j] = temp;
                }
            }
        }
        for (int i = 0; i < cluesIndex; i++) {
            strcat(clues, localClues[i]);
            strcat(clues, " ");
        }
    }
}

bool invalid_guess(char guess[]) {
    if (strlen(guess) != NUM_DIGITS) {
        return true;
    }

    for (size_t i = 0; i < strlen(guess); i++) {
        if (!isdigit(guess[i])) {
            return true;
        }
    }

    return false;
}
