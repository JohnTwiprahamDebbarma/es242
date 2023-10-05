#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];
int availableRow[COLS];


void initializeBoard() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = ' ';
        }
    }
}

void printBoard() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

bool isValidMove(int col) {
    return col >= 0 && col < COLS && availableRow[col] >= 0;
}

bool makeMove(int col, char player) {
    if (!isValidMove(col)) {
        return false; // Invalid move
    }
    int row = availableRow[col];
    board[row][col] = player;
    availableRow[col]--;
    return true;
}

bool isBoardFull() {
    for (int col = 0; col < COLS; col++) {
        if (availableRow[col] >= 0) {
            return false; // Board is not full
        }
    }
    return true; // Board is full (draw)
}

int getRandomMove() {
    int validMoves[COLS];
    int numValidMoves = 0;

    for (int col = 0; col < COLS; col++) {
        if (isValidMove(col)) {
            validMoves[numValidMoves] = col;
            numValidMoves++;
        }
    }

    if (numValidMoves == 0) {
        return -1; // No valid moves
    }

    int randomIndex = rand() % numValidMoves;
    return validMoves[randomIndex];
}

int dropPiece(int col, char player) {
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return row;
        }
    }
    return -1; // Column is full
}

int checkWin(int row, int col, char player) {
    // Check horizontally
    int count = 0;
    for (int c = col - 3; c <= col + 3; c++) {
        if (c >= 0 && c < COLS && board[row][c] == player) {
            count++;
            if (count == 4) return 1; // Player wins
        } else {
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int r = row - 3; r <= row + 3; r++) {
        if (r >= 0 && r < ROWS && board[r][col] == player) {
            count++;
            if (count == 4) return 1; // Player wins
        } else {
            count = 0;
        }
    }

    // Check diagonally (left-top to right-bottom)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1; // Player wins
        } else {
            count = 0;
        }
    }

    // Check diagonally (right-top to left-bottom)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col - i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1; // Player wins
        } else {
            count = 0;
        }
    }

    return 0; // No winner yet
}

// int isBoardFull() {
//     for (int row = 0; row < ROWS; row++) {
//         for (int col = 0; col < COLS; col++) {
//             if (board[row][col] == ' ') {
//                 return 0; // Board is not full
//             }
//         }
//     }
//     return 1; // Board is full (draw)
// }


int main() {
    char currentPlayer = 'X';
    int gameWon = 0;
    int col; // Column chosen by the player

    initializeBoard();
    srand(time(NULL)); // Seed the random number generator

    while (!gameWon && !isBoardFull()) {
        printBoard();

        if (currentPlayer == 'X') {
            // int col;
            printf("Player %c, enter column (0-%d): ", currentPlayer, COLS - 1);
            scanf("%d", &col);

            if (!isValidMove(col)) {
                printf("Invalid move. Try again.\n");
                continue;
            }
            int row = dropPiece(col, currentPlayer);
            
            if (!makeMove(col, currentPlayer)) {
                printf("Column is full. Try again.\n");
                continue;
            }
        } else {
            printf("Computer (Player O) is thinking...\n");
            int computerMove = getRandomMove();

            if (computerMove == -1) {
                printf("Computer couldn't find a valid move. The game is a draw.\n");
                break;
            }

            makeMove(computerMove, currentPlayer);
            printf("Computer chose column %d.\n", computerMove);
        }

        gameWon = checkWin(availableRow[col] + 1, col, currentPlayer);

        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard();

    if (gameWon) {
        printf("Player %c wins!\n", currentPlayer);
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}




// int main() {
//     char currentPlayer = 'X';
//     int gameWon = 0;

//     initializeBoard();

//     while (!gameWon && !isBoardFull()) {
//         printBoard();

//         int col;
//         printf("Player %c, enter column (0-6): ", currentPlayer);
//         scanf("%d", &col);

//         if (col < 0 || col >= COLS || board[0][col] != ' ') {
//             printf("Invalid move. Try again.\n");
//             continue;
//         }

//         int row = dropPiece(col, currentPlayer);

//         gameWon = checkWin(row, col, currentPlayer);

//         // Switch to the other player
//         currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
//     }

//     printBoard();

//     if (gameWon) {
//         printf("Player %c wins!\n", currentPlayer);
//     } else {
//         printf("It's a draw!\n");
//     }

//     return 0;
// }

