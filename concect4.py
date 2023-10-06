# -*- coding: utf-8 -*-
"""
Created on Thu Oct  5 21:27:24 2023

@author: jaide
"""

import numpy as np

# Create the game board
board = np.zeros((6, 7))

def print_grid():
    print(np.flip(board, 1))

# Function to check if a move is valid
def is_valid_move(board, col):
    return board[5][col] == 0

# Function to make a move
def make_move(board, col, player):
    for row in range(6):
        if board[row][col] == 0:
            board[row][col] = player
            break

# Function to check if a player has won
def check_win(board, player):
    # Check rows
    for row in range(6):
        for col in range(4):
            if board[row][col] == player and board[row][col+1] == player and board[row][col+2] == player and board[row][col+3] == player:
                return True

    # Check columns
    for col in range(7):
        for row in range(3):
            if board[row][col] == player and board[row+1][col] == player and board[row+2][col] == player and board[row+3][col] == player:
                return True

    # Check diagonals
    for row in range(3):
        for col in range(4):
            if board[row][col] == player and board[row+1][col+1] == player and board[row+2][col+2] == player and board[row+3][col+3] == player:
                return True
            if board[row][col+3] == player and board[row+1][col+2] == player and board[row+2][col+1] == player and board[row+3][col] == player:
                return True

    return False

# Function to get the optimal move for the computer player
def get_optimal_move(board, player):
    best_score = -float('inf')
    best_move = None

    for col in range(7):
        if is_valid_move(board, col):
            temp_board = board.copy()
            make_move(temp_board, col, player)
            score = minimax(temp_board, 5, False, player)
            if score > best_score:
                best_score = score
                best_move = col

    return best_move

# Minimax algorithm with alpha-beta pruning
def minimax(board, depth, maximizing_player, player, alpha=float('-inf'), beta=float('inf')):
    if depth == 0 or check_win(board, player) or check_win(board, 3 - player):
        return evaluate(board, player)

    if maximizing_player:
        max_eval = -float('inf')
        for col in range(7):
            if is_valid_move(board, col):
                temp_board = board.copy()
                make_move(temp_board, col, player)
                eval = minimax(temp_board, depth - 1, False, player, alpha, beta)
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
        return max_eval
    else:
        min_eval = float('inf')
        for col in range(7):
            if is_valid_move(board, col):
                temp_board = board.copy()
                make_move(temp_board, col, 3 - player)
                eval = minimax(temp_board, depth - 1, True, player, alpha, beta)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
        return min_eval

# Evaluation function to determine the score of a board state
def evaluate(board, player):
    score = 0

    # Check rows
    for row in range(6):
        for col in range(4):
            window = board[row][col:col+4]
            score += evaluate_window(window, player)

    # Check columns
    for col in range(7):
        for row in range(3):
            window = board[row:row+4, col]
            score += evaluate_window(window, player)

    # Check diagonals
    for row in range(3):
        for col in range(4):
            window = board[row:row+4, col:col+4].diagonal()
            score += evaluate_window(window, player)
            window = np.fliplr(board[row:row+4, col:col+4]).diagonal()
            score += evaluate_window(window, player)

    return score

# Helper function to evaluate a window of 4 cells
def evaluate_window(window, player):
    score = 0
    opponent = 3 - player

    if np.count_nonzero(window == player) == 4:
        score += 100
    elif np.count_nonzero(window == player) == 3 and np.count_nonzero(window == 0) == 1:
        score += 5
    elif np.count_nonzero(window == player) == 2 and np.count_nonzero(window == 0) == 2:
        score += 2

    if np.count_nonzero(window == opponent) == 3 and np.count_nonzero(window == 0) == 1:
        score -= 4

    return score

# Main game loop
def play_game():
    player = 1
    game_over = False

    while not game_over:
        if player == 1:
            col = int(input("Player 1's turn. Enter column (0-6): "))
            if is_valid_move(board, col):
                make_move(board, col, player)
                if check_win(board, player):
                    print("Player 1 wins!")
                    game_over = True
                player = 3 - player
            else:
                print("Invalid move. Try again.")
        else:
            col = get_optimal_move(board, player)
            make_move(board, col, player)
            if check_win(board, player):
                print("Computer wins!")
                game_over = True
            player = 3 - player

        print(board)

# Start the game
print_grid()
play_game()
