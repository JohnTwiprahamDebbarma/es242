#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LINES 9

char board[NUM_LINES]; // '0' for uncolored, '1' for player, '2' for computer

// Function to display the current board state
void displayBoard() {
    printf("\nCurrent Board:\n");
    printf(" 1---2---3\n");
    printf("| %c | %c | %c |\n", board[0], board[1], board[2]);
    printf("4---5---6\n");
    printf("| %c | %c | %c |\n", board[3], board[4], board[5]);
    printf("7---8---9\n\n");
}

// Function to check if a player has formed a triangle of their color
int checkForTriangle(int player) {
    // Check all possible triangles
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
        return 1;
    return 0;
}

// Function to make a player move
void makeMove(int player) {
    int line;
    do {
        printf("Enter the line number to color (1-9): ");
        scanf("%d", &line);
    } while (line < 1 || line > 9 || board[line - 1] != '0');

    board[line - 1] = (player == 1) ? '1' : '2';
}

// Function for the computer's move (random)
void computerMove(int player) {
    int line;
    do {
        line = rand() % NUM_LINES;
    } while (board[line] != '0');

    board[line] = (player == 1) ? '1' : '2';
    printf("Computer colors line %d\n", line + 1);
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_LINES; i++) {
        board[i] = '0';
    }

    int currentPlayer = 1; // 1 for player, 2 for computer

    printf("Welcome to the Game of Sim!\n");
    displayBoard();

    while (1) {
        if (currentPlayer == 1) {
            makeMove(currentPlayer);
        } else {
            computerMove(currentPlayer);
        }

        displayBoard();

        if (checkForTriangle(currentPlayer)) {
            if (currentPlayer == 1) {
                printf("Congratulations! You formed a triangle. You win!\n");
            } else {
                printf("Oops! Computer formed a triangle. You lose!\n");
            }
            break;
        }

        currentPlayer = 3 - currentPlayer; // Switch players (1 -> 2 or 2 -> 1)
    }

    return 0;
}
