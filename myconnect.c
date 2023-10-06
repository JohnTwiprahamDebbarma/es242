#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// #define ROWS 6
// #define COLS 7

// char board[ROWS][COLS];
// int availableRow[COLS];


// void initializeBoard() {
//     for (int row = 0; row < ROWS; row++) {
//         for (int col = 0; col < COLS; col++) {
//             board[row][col] = ' ';
//         }
//     }
// }

// void printBoard() {
//     for (int row = 0; row < ROWS; row++) {
//         for (int col = 0; col < COLS; col++) {
//             printf("| %c ", board[row][col]);
//         }
//         printf("|\n");
//     }
//     printf("-----------------------------\n");
// }

// bool isValidMove(int col) {
//     return col >= 0 && col < COLS && availableRow[col] >= 0;
// }

// bool makeMove(int col, char player) {
//     if (!isValidMove(col)) {
//         return false; // Invalid move
//     }
//     int row = availableRow[col];
//     board[row][col] = player;
//     availableRow[col]--;
//     return true;
// }

// bool isBoardFull() {
//     for (int col = 0; col < COLS; col++) {
//         if (availableRow[col] >= 0) {
//             return false; // Board is not full
//         }
//     }
//     return true; // Board is full (draw)
// }

// int getRandomMove() {
//     int validMoves[COLS];
//     int numValidMoves = 0;

//     for (int col = 0; col < COLS; col++) {
//         if (isValidMove(col)) {
//             validMoves[numValidMoves] = col;
//             numValidMoves++;
//         }
//     }

//     if (numValidMoves == 0) {
//         return -1; // No valid moves
//     }

//     int randomIndex = rand() % numValidMoves;
//     return validMoves[randomIndex];
// }

// int dropPiece(int col, char player) {
//     for (int row = ROWS - 1; row >= 0; row--) {
//         if (board[row][col] == ' ') {
//             board[row][col] = player;
//             return row;
//         }
//     }
//     return -1; // Column is full
// }

// int checkWin(int row, int col, char player) {
//     // Check horizontally
//     int count = 0;
//     for (int c = col - 3; c <= col + 3; c++) {
//         if (c >= 0 && c < COLS && board[row][c] == player) {
//             count++;
//             if (count == 4) return 1; // Player wins
//         } else {
//             count = 0;
//         }
//     }

//     // Check vertically
//     count = 0;
//     for (int r = row - 3; r <= row + 3; r++) {
//         if (r >= 0 && r < ROWS && board[r][col] == player) {
//             count++;
//             if (count == 4) return 1; // Player wins
//         } else {
//             count = 0;
//         }
//     }

//     // Check diagonally (left-top to right-bottom)
//     count = 0;
//     for (int i = -3; i <= 3; i++) {
//         int r = row + i;
//         int c = col + i;
//         if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
//             count++;
//             if (count == 4) return 1; // Player wins
//         } else {
//             count = 0;
//         }
//     }

//     // Check diagonally (right-top to left-bottom)
//     count = 0;
//     for (int i = -3; i <= 3; i++) {
//         int r = row + i;
//         int c = col - i;
//         if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
//             count++;
//             if (count == 4) return 1; // Player wins
//         } else {
//             count = 0;
//         }
//     }

//     return 0; // No winner yet
// }

// // int isBoardFull() {
// //     for (int row = 0; row < ROWS; row++) {
// //         for (int col = 0; col < COLS; col++) {
// //             if (board[row][col] == ' ') {
// //                 return 0; // Board is not full
// //             }
// //         }
// //     }
// //     return 1; // Board is full (draw)
// // }


// int main() {
//     char currentPlayer = 'X';
//     int gameWon = 0;
//     int col; // Column chosen by the player

//     initializeBoard();
//     srand(time(NULL)); // Seed the random number generator

//     while (!gameWon && !isBoardFull()) {
//         printBoard();

//         if (currentPlayer == 'X') {
//             // int col;
//             printf("Player %c, enter column (0-%d): ", currentPlayer, COLS - 1);
//             scanf("%d", &col);

//             if (!isValidMove(col)) {
//                 printf("Invalid move. Try again.\n");
//                 continue;
//             }
//             int row = dropPiece(col, currentPlayer);

//             if (!makeMove(col, currentPlayer)) {
//                 printf("Column is full. Try again.\n");
//                 continue;
//             }
//         } else {
//             printf("Computer (Player O) is thinking...\n");
//             int computerMove = getRandomMove();

//             if (computerMove == -1) {
//                 printf("Computer couldn't find a valid move. The game is a draw.\n");
//                 break;
//             }

//             makeMove(computerMove, currentPlayer);
//             printf("Computer chose column %d.\n", computerMove);
//         }

//         gameWon = checkWin(availableRow[col] + 1, col, currentPlayer);

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




// // int main() {
// //     char currentPlayer = 'X';
// //     int gameWon = 0;

// //     initializeBoard();

// //     while (!gameWon && !isBoardFull()) {
// //         printBoard();

// //         int col;
// //         printf("Player %c, enter column (0-6): ", currentPlayer);
// //         scanf("%d", &col);

// //         if (col < 0 || col >= COLS || board[0][col] != ' ') {
// //             printf("Invalid move. Try again.\n");
// //             continue;
// //         }

// //         int row = dropPiece(col, currentPlayer);

// //         gameWon = checkWin(row, col, currentPlayer);

// //         // Switch to the other player
// //         currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
// //     }

// //     printBoard();

// //     if (gameWon) {
// //         printf("Player %c wins!\n", currentPlayer);
// //     } else {
// //         printf("It's a draw!\n");
// //     }

// //     return 0;
// // }



#define ROWS 6
#define COLS 7
#define MAX_DEPTH 5

char board[ROWS][COLS];

// Function declarations
void initializeBoard();
int checkWin(char player);
int makeMove(int column, char player);
int checkDraw();
int depthFirstSearch(int depth, char player);
int getRowOfLastMove(int column);
int getBestMove();
void printBoard();
void playGame();

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}


// double max(double a, double b) {
//     return fmax(a, b);
// }

// double min(double a, double b) {
//     return fmin(a, b);
// }


void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

int checkWin(char player) {
    // Check for horizontal win
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for vertical win
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal win (top-left to bottom-right)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal win (top-right to bottom-left)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 3; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player) {
                return 1;
            }
        }
    }

    return 0;
}

int makeMove(int column, char player) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column] == ' ') {
            board[i][column] = player;
            return 1;
        }
    }
    return 0;
}

int checkDraw() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int depthFirstSearch(int depth, char player) {
    if (depth == 0 || checkWin('O') || checkWin('X') || checkDraw()) {
        // Base case: return the score
        if (checkWin('O')) {
            return -1;
        } else if (checkWin('X')) {
            return 1;
        } else {
            return 0;
        }
    }

    int bestScore;
    if (player == 'X') {
        bestScore = -1000;
        for (int col = 0; col < COLS; col++) {
            if (makeMove(col, player)) {
                int score = depthFirstSearch(depth - 1, 'O');
                bestScore = max(bestScore, score);
                board[getRowOfLastMove(col)][col] = ' ';
            }
        }
    } else {
        bestScore = 1000;
        for (int col = 0; col < COLS; col++) {
            if (makeMove(col, player)) {
                int score = depthFirstSearch(depth - 1, 'X');
                bestScore = min(bestScore, score);
                board[getRowOfLastMove(col)][col] = ' ';
            }
        }
    }

    return bestScore;
}

int getRowOfLastMove(int column) {
    for (int i = 0; i < ROWS; i++) {
        if (board[i][column] != ' ') {
            return i;
        }
    }
    return -1;
}

int getBestMove() {
    int bestScore = -1000;
    int bestMove = -1;

    for (int col = 0; col < COLS; col++) {
        if (makeMove(col, 'X')) {
            int score = depthFirstSearch(5, 'O');
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
            board[getRowOfLastMove(col)][col] = ' ';
        }
    }

    return bestMove;
}

void printBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------\n");
}

void playGame() {
    char currentPlayer = 'O';
    int gameOver = 0;

    initializeBoard();

    while (!gameOver) {
        if (currentPlayer == 'O') {
            // Human player's turn
            int column;
            printf("Enter the column number (0-6): ");
            scanf("%d", &column);

            if (makeMove(column, currentPlayer)) {
                currentPlayer = 'X';
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            // Computer player's turn
            int column = getBestMove();

            if (makeMove(column, currentPlayer)) {
                currentPlayer = 'O';
            }
        }

        // Check for win or draw
        if (checkWin('O')) {
            printf("Player O wins!\n");
            gameOver = 1;
        } else if (checkWin('X')) {
            printf("Player X wins!\n");
            gameOver = 1;
        } else if (checkDraw()) {
            printf("It's a draw!\n");
            gameOver = 1;
        }

        // Print the current board
        printBoard();
    }
}


int main() {
    playGame();
    return 0;
}
