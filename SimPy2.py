# Function to print the Tic Tac Toe board
def print_board(board):
    print("---------")
    for i in range(15):
        print(board[i], end="")
    print("\n")


dic = {0:(1,2), 1:(1,3), 2:(1,4), 3:(1,5), 4:(1,6), 5:(2,3), 6:(2,4), 7:(2,5), 8:(2,6), 9:(3,4), 10:(3,5), 11:(3,6), 12:(4,5), 13:(4,6), 14:(5,6)}
computeredges=[]
playeredges=[]

def is_board_full(board):
    for move in board:
        if move == 0:
            return False
    return True

def has_lost(board, player):
    if ((board[0]==player) and (board[1]==player) and (board[5]==player)) or ((board[0]==player) and (board[2]==player) and (board[6]==player)) or ((board[0]==player) and (board[3]==player) and (board[7]==player)) or ((board[0]==player) and (board[4]==player) and (board[8]==player)) or ((board[1]==player) and (board[2]==player) and (board[9]==player)) or ((board[1]==player) and (board[3]==player) and (board[10]==player)) or ((board[1]==player) and (board[4]==player) and (board[11]==player)) or ((board[2]==player) and (board[3]==player) and (board[12]==player)) or ((board[2]==player) and (board[4]==player) and (board[13]==player)) or ((board[3]==player) and (board[4]==player) and (board[14]==player)) or ((board[5]==player) and (board[6]==player) and (board[9]==player)) or ((board[5]==player) and (board[7]==player) and (board[10]==player)) or ((board[5]==player) and (board[8]==player) and (board[11]==player)) or ((board[6]==player) and (board[7]==player) and (board[12]==player)) or ((board[6]==player) and (board[8]==player) and (board[13]==player)) or ((board[7]==player) and (board[8]==player) and (board[14]==player)) or ((board[9]==player) and (board[10]==player) and (board[12]==player)) or ((board[9]==player) and (board[13]==player) and (board[11]==player)) or ((board[10]==player) and (board[11]==player) and (board[14]==player)) or ((board[12]==player) and (board[13]==player) and (board[14]==player)):
        return True
    return False

def otherplayer(player):
    if player == 1:
        return 2
    else:
        return 1
    

# Function to check if a player has won
def check_win(board, player):
    if has_lost(board, otherplayer(player)):
        return True
    else:
        return False
    
def have_a_common_vertex(e1, e2):
    a1 = e1[0]
    b1 = e1[1]
    a2 = e2[0]
    b2 = e2[1]
    if a1==a2:
        return True
    elif a1==b2:
        return True
    elif b1==a2:
        return True
    elif b1==b2:
        return True
    else:
        return True

# Function to get the best move for the computer
def get_best_move(board, player):
    for i in range(15):
        if board[i]==0:
            e1=dic[i]
            shareedgewithcomp=False
            shareedgewithplayer=False
            sharededgewithcompplayerandnew=False
            computercommonedges=[]
            for j in range(len(computeredges)):
                e2 = computeredges[j]
                if have_a_common_vertex(e1, e2):
                    shareedgewithcomp=True
                    computercommonedges.append(e2)
            playercommonedges=[]
            for k in range(len(playeredges)):
                e3=playeredges[k]
                if have_a_common_vertex(e1, e3):
                    shareedgewithplayer=True
                    playercommonedges.append(e3)
            for l1 in range(len(playercommonedges)):
                for l2 in range(len(computercommonedges)):
                    if have_a_common_vertex(playercommonedges[l1], computercommonedges[l2]):
                        sharededgewithcompplayerandnew=True
                        return i
        if board[i]==0:
            e1=dic[i]
            shareedgewithcomp=False
            shareedgewithplayer=False
            sharededgewithcompplayerandnew=False
            computercommonedges=[]
            for j in range(len(computeredges)):
                e2 = computeredges[j]
                if have_a_common_vertex(e1, e2):
                    shareedgewithcomp=True
                    computercommonedges.append(e2)
            playercommonedges=[]
            for k in range(len(playeredges)):
                e3=playeredges[k]
                if have_a_common_vertex(e1, e3):
                    shareedgewithplayer=True
                    playercommonedges.append(e3)
            if shareedgewithplayer == True and shareedgewithcomp == False:
                return i
            
        if board[i]==0:
            e1=dic[i]
            shareedgewithcomp=False
            shareedgewithplayer=False
            sharededgewithcompplayerandnew=False
            computercommonedges=[]
            for j in range(len(computeredges)):
                e2 = computeredges[j]
                if have_a_common_vertex(e1, e2):
                    shareedgewithcomp=True
                    computercommonedges.append(e2)
            playercommonedges=[]
            for k in range(len(playeredges)):
                e3=playeredges[k]
                if have_a_common_vertex(e1, e3):
                    shareedgewithplayer=True
                    playercommonedges.append(e3)
            if shareedgewithplayer == False and shareedgewithcomp == True:
                return i
            
        if board[i]==0:
            e1=dic[i]
            shareedgewithcomp=False
            shareedgewithplayer=False
            sharededgewithcompplayerandnew=False
            computercommonedges=[]
            for j in range(len(computeredges)):
                e2 = computeredges[j]
                if have_a_common_vertex(e1, e2):
                    shareedgewithcomp=True
                    computercommonedges.append(e2)
            playercommonedges=[]
            for k in range(len(playeredges)):
                e3=playeredges[k]
                if have_a_common_vertex(e1, e3):
                    shareedgewithplayer=True
                    playercommonedges.append(e3)
            if shareedgewithplayer == True and shareedgewithcomp == False:
                if len(playercommonedges>=2):
                    return i
        
        if board[i]==0:
            e1=dic[i]
            board[i]=player
            if not has_lost(board, player):
                board[i]=0
                return e1
            board[i]=0
            
        if board[i]==0:
            e1=dic[i]
            print("I Lost")
            return i               
                

            
            
            


# Function to play the game
def play_game():
    board = [0]*15
    print("Welcome to Game of Sim!")

    position=int(input("Enter Your Colour, If you want to start, press 1, else, press 2: "))
    if position == 2:
        board[0]=1
        print_board(board)

        while True:
            # Player's turn
            move = int(input("Enter the move (0-14): "))
            if board[move] != 0:
                print("Invalid move. Try again.")
                continue
            board[move] = 2
            playeredges.append(dic[move])
            print_board(board)
            if check_win(board, 2):
                print("Congratulations! You win!")
                break
            if is_board_full(board):
                print("It's a tie!")
                break

            # Computer's turn
            print("Computer's turn...")
            best_move = get_best_move(board, 1)
            board[best_move] = 1
            computeredges.append(dic[move])
            print_board(board)
            if check_win(board, 1):
                print("Sorry, you lose!")
                break
            if is_board_full(board):
                print("It's a tie!")
                break

    else:
        print_board(board)

        while True:
            # Player's turn
            move = int(input("Enter the move (0-14): "))
            if board[move] != 0:
                print("Invalid move. Try again.")
                continue
            board[move] = 1
            playeredges.append(dic[move])
            print_board(board)
            if check_win(board, 1):
                print("Congratulations! You win!")
                break
            if is_board_full(board):
                print("It's a tie!")
                break

            # Computer's turn
            print("Computer's turn...")
            best_move = get_best_move(board, 2)
            board[best_move] = 2
            computeredges.append(dic[move])
            print_board(board)
            if check_win(board, 2):
                print("Sorry, you lose!")
                break
            if is_board_full(board):
                print("It's a tie!")
                break

# Start the game
play_game()
