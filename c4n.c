#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#define ROWS 4
#define COLS 5
#define MAX_DEPTH 20

typedef char board_t[4][5];
typedef char player_t;

enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef struct {
    int col;
    int score;
} move_t;

// Function declarations
void initialize_board(board_t board);
int has_won(board_t board, player_t player);
int put_coin(board_t board, int column, player_t player);
int is_full(board_t board);
int dfs(int depth, player_t player, board_t board,player_t comp);
int get_topmost(int column, board_t board);
move_t getBestMove(board_t board,player_t player);
void print_board(board_t board);
void playGame();

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

player_t other_player(player_t player){
    player_t other;
    if (player=='R'){
        other = 'B';
    }
    else{
        other = 'R';
    }
    return other;
}

void initialize_board(board_t board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

int has_won(board_t board, player_t player) {
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

int is_full(board_t board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void print_board(board_t board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------\n");
}

int put_coin(board_t board, int column, player_t player) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column] == ' ') {
            board[i][column] = player;
            return 1;
        }
    }
    return 0;
}

int get_topmost(int column, board_t board) {
    for (int i = 0; i < ROWS; i++) {
        if (board[i][column] != ' ') {
            return i;
        }
    }
    return -1;
}

int dfs(int depth, player_t player, board_t board,player_t comp) {
    if (depth == 0 || has_won(board, other_player(player)) || has_won(board, player) || is_full(board)) {
        // Base case: return the score
        if (has_won(board, other_player(comp))) {
            return -1;
        } else if (has_won(board, comp)) {
            return 1;
        } else {
            return 0;
        }
    }
    move_t best_move;
    int best_score = best_move.score;
    if (player == comp) {
        best_score = -1000;
        for (int col = 0; col < COLS; col++) {
            if (put_coin(board, col, player)) {
                int score = dfs(depth - 1, other_player(comp), board,comp);
                best_score = max(best_score, score);
                board[get_topmost(col, board)][col] = ' ';
            }
        }
    } else {
        best_score = 1000;
        for (int col = 0; col < COLS; col++) {
            if (put_coin(board, col, player)) {
                int score = dfs(depth - 1, comp, board,comp);
                best_score = min(best_score, score);
                board[get_topmost(col, board)][col] = ' ';
            }
        }
    }
    return best_score;
}

move_t getBestMove(board_t board,player_t player) {
    int best_score = -1000;
    int best_col = -1;

    for (int col = 0; col < COLS; col++) {
        if (put_coin(board, col, player)) {
            int score = dfs(5, other_player(player), board,player);
            if (score > best_score) {
                best_score = score;
                best_col = col;
            }
            board[get_topmost(col, board)][col] = ' ';
        }
    }
    move_t best_move;
    best_move.col = best_col;  
    best_move.score = best_score;
    return best_move;
}

int main() {
    player_t player;
    printf("Select R/B\nIf you want to play as First as Red, enter R\nIf you want to play as Second as Blue, enter B\n");
    scanf("%c",&player);
    printf("You have selected %c\n",player);

    if (player=='B'){
    int gameOver = 0;
    board_t board;
    initialize_board(board);
    player_t player = 'R';
    board[3][0] = player;
    print_board(board);

    player_t currentPlayer = other_player(player);
    player = other_player(player);
    while (!gameOver) {
        if (currentPlayer == player) {
            // Human player's turn
            int column;
            printf("Enter the column number (0-4): ");
            scanf("%d", &column);

            if (put_coin(board, column, currentPlayer)) {
                currentPlayer = other_player(currentPlayer);
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            // Computer player's turn
            move_t best_move = getBestMove(board,currentPlayer);
            int column = best_move.col;

            if (put_coin(board, column, currentPlayer)) {
                currentPlayer = other_player(currentPlayer);
            }
        }

        // Check for win or draw
        if (has_won(board, currentPlayer)) {
            printf("Player %c wins!\n",currentPlayer);
            gameOver = 1;
        } else if (has_won(board,other_player(currentPlayer))) {
            printf("Player %c wins!\n",other_player(currentPlayer));
            gameOver = 1;
        }
        else if (is_full(board)) {
            printf("It's a draw!\n");
            gameOver = 1;
        }

        // Print the current board
        print_board(board);
    }}
    else{
    int gameOver = 0;
    board_t board;
    initialize_board(board);
    print_board(board);

    player_t currentPlayer = player;
    while (!gameOver) {
        if (currentPlayer == player) {
            // Human player's turn
            int column;
            printf("Enter the column number (0-4): ");
            scanf("%d", &column);

            if (put_coin(board, column, currentPlayer)) {
                currentPlayer = other_player(currentPlayer);
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            // Computer player's turn
            move_t best_move = getBestMove(board,currentPlayer);
            int column = best_move.col;

            if (put_coin(board, column, currentPlayer)) {
                currentPlayer = other_player(currentPlayer);
            }
        }

        // Check for win or draw
        if (has_won(board, currentPlayer)) {
            printf("Player %c wins!\n",currentPlayer);
            gameOver = 1;
        } else if (has_won(board,other_player(currentPlayer))) {
            printf("Player %c wins!\n",other_player(currentPlayer));
            gameOver = 1;
        }
        else if (is_full(board)) {
            printf("It's a draw!\n");
            gameOver = 1;
        }

        // Print the current board
        print_board(board);
    }}
}