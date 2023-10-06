#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h> 

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
// enum {
//     EMPTY = 0,
//     RED,
//     BLUE,
// };

typedef struct {
    int col;
    int score;
} move_t;

typedef char board_t[4][5];
typedef char player_t;

#define MAX_ORD (3486784401)


uint8_t *computed_moves;  

void initialize_computed_moves() {
    computed_moves = malloc(MAX_ORD * sizeof(uint8_t));
    if (computed_moves == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(computed_moves, 0, MAX_ORD * sizeof(uint8_t));
}

void cleanup_computed_moves() {
    free(computed_moves);
}


uint8_t encode_move(move_t m)
{
    uint8_t b = 0;

    assert(0 <= m.col && m.col <= 4);
    b |= m.col;

    switch (m.score) {
    case -1: b |= 1 << 4; break;
    case 0: b |= 1 << 3; break;
    case 1: b |= 1 << 2; break;
    }

    return b;
}

move_t decode_move(uint8_t b)
{
    move_t m;

    m.col = (b & 0x3);
    if (b & 0x4) m.score = 1;
    if (b & 0x8) m.score = 0;
    if (b & 0x10) m.score = -1;
    return m;
}


int ord(board_t board)
{
    int p = 1;
    int i = 0;
    int d;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            switch (board[row][col]) {
            case 'X': d = 1; break;
            case 'O': d = 2; break;
            case '.': d = 0; break;
            }
            i += d * p;
            p *= 3;
        }
    }

    return i;
}

int has_won(board_t board, player_t player){
    int count = 0;
    for (int i=0;i<5;i++){
        for (int j=0;j<4;j++){
            if (board[j][i]==player){
                count++;
                if (count==4){
                    return 1;
                }
            }
            else{
                count=0;
            }
        }
    }

    count=0;
    for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            if (board[i][j]==player){
                count++;
                if (count==4){
                    return 1;
                }
            }
            else{
                count=0;
            }
        }
    }

    count =0;
    for (int i=0;i<=3;i++){
        if (board[i][i]==player){
            count++;
            if (count==4){
                return 1;
            }
        }
        else{
            count=0;
        }
        
    }
    count =0;
    int k = 1;
    for (int i=0;i<=3;i++){
        if (board[i][k]==player){
            count++;
            if (count==4){
                return 1;
            }
        }
        else{
            count=0;
        }
        k++;
        
    }
    count =0;
    k = 3;
    for (int i=0;i<=3;i++){
        if (board[i][k]==player){
            count++;
            if (count==4){
                return 1;
            }
        }
        else{
            count=0;
        }
        k--;
        
    }
    count =0;
    k = 4;
    for (int i=0;i<=3;i++){
        if (board[i][k]==player){
            count++;
            if (count==4){
                return 1;
            }
        }
        else{
            count=0;
        }
        k--;
        
    }

    return 0;
}

int is_full(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (board[row][col] == '.') { return 0; }
        }
    }
    return 1;
}

void init_board(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            board[row][col] = '.';
        }
    }
}
player_t other_player(player_t player)
{
    if (player=='R'){
        player_t other = 'B';
        return other;
    }
    else{
        player_t other = 'R';
        return other;
    }
}



move_t best_move(board_t board, player_t player){
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));

    int o = ord(board);

    if (computed_moves[o]) {
        return decode_move(computed_moves[o]);
    }

    for (int col = 0; col < 5; col++) {
        for (int row = 3; row > -1; row--) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                if (has_won(board, player)) {
                    board[row][col] = '.';
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .col = col,
                        .score = 1
                        });
                    return candidate;
                }
                board[row][col] = '.';
            }
        }
    }

    for (int col = 0; col < 5; col++) {
        for (int row = 3; row > -1; row--) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                if (is_full(board)) {
                    board[row][col] = '.';
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .col = col,
                        .score = 0
                        });
                    return candidate;
                }
                response = best_move(board, other_player(player));
                board[row][col] = '.';
                if (response.score == -1) {
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .col = col,
                        .score = 1
                        });
                    return candidate;
                } else if (response.score == 0) {
                    candidate = (move_t) {
                        .col = col,
                        .score = 0
                    };
                    no_candidate=0;
                  
                } else { 
                    if (no_candidate){
                        candidate = (move_t) {
                            .col = col,
                            .score = -1
                        };
                        no_candidate=0;
        
                        
                    }
                }
            }
        }
    }
    computed_moves[o] = encode_move(candidate);
    return candidate;
}



void print_board(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            printf("%3c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}
void play_move(board_t board, player_t player, int move) {
    bool full = true;
    if (move < 0 || move > 4) {
        printf("Invalid column number. Please enter a number between 0 and 4: ");
        scanf("%d", &move);
    }
    for (int i = 3; i >= 0; i--) {
        if (board[i][move] == '.') {
            board[i][move] = player;
            full = false;
            break;
        }
    }
    if (full) {
        printf("Column is full. Select a different column: ");
        scanf("%d", &move);
        play_move(board, player, move);
    }
}


int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    initialize_computed_moves();
    board_t board;
    int move;
    int move_op;
    init_board(board);
    player_t player;
    printf("Enter R/B: ");
    scanf(" %c",&player);
    printf("You have selected %c \n",player);
    print_board(board);
    player_t current = player;
    while (1){
        if (current==player){
            printf("Enter move as column number (0-4): ");
            scanf("%d",&move);
            assert(move<=4);
            play_move(board,player,move);
            print_board(board);
        }
        else{
            move_t opp_move = best_move(board,other_player(player));
            play_move(board,other_player(player),opp_move.col);
            print_board(board);
        }
        if (has_won(board,current)){
            if (current==player){
                printf("Game Over, You win!");
                break;
            }else{
                printf("Game Over, PC wins!");
                break;
            }
            
        }else if (is_full(board))
        {
            printf("Draw!");
            break;
        }
        
        current = other_player(current);
        
        
    }
    cleanup_computed_moves();
    return 0;
}

