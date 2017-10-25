# File: proj1.py 
# Author: Joel Okpara
# Date: 4/18/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: A game of tic tac toe

# WARNING: This game contains many bugs
# ¯\_(ツ)_/¯

PLAY = 0
END = 1
# printBoard() takes the board list at outputs it as a grid
# Input: board list
# Output: board grid
def printBoard(boardList):
     boardCount = 0
     #if we're on space 3 or space 6 or space 9 and a newline after
     for n in boardList:
          if boardCount == 2 or boardCount == 5 or boardCount == 8:
               print(n)
          else:
               print(n, end = " | ")
          boardCount = boardCount + 1
     print()

# boardCheck() checks if there are any spaces left on the board
# Input: board list
# Output: board is full alert
def boardCheck(boardList, symDict, sym1, sym2, state):
     boardSpace = 0
     #if there's and X or O in a space add 1 to the counter
     for n in boardList:
          if n == symDict[sym1] or n == symDict[sym2]:
               boardSpace = boardSpace + 1
     #if counter gets to 9 the board is full
     if boardSpace == 9:
          print("Game is a draw!")
          return True # Returns True for if statement later in code 

# winCond() holds the win conditions aka 3 in a row, column, or diagonal
# Input: Values at all possible win locations
# Output: player has won alert
def winCond(boardList,p,symDict,sym):
     #  HORIZONTALS
        if boardList[0:3] == [symDict[sym],symDict[sym],symDict[sym]]:
             print("player",p,"has won!")
             return True
        if boardList[3:6] == [symDict[sym],symDict[sym],symDict[sym]]:
             print("player",p,"has won!")
             return True
        if boardList[6:9] == [symDict[sym],symDict[sym],symDict[sym]]:
             print("player",p,"has won!")
             return True
     #  VERTICALS
        if boardList[0] and boardList[3] and boardList[6] == symDict[sym]:
             print("player",p,"has won!")
             return True
        if boardList[1] and boardList[4] and boardList[7] == symDict[sym]:
             print("player",p,"has won!")
             return True
        if boardList[2] and boardList[5] and boardList[8] == symDict[sym]:
             print("player",p,"has won!")
             return True
     #DIAGONALS
        if boardList[0] and boardList[4] and boardList[8] == symDict[sym]:
             print("player",p,"has won!")
             return True
        if boardList[2] and boardList[4] and boardList[6] == symDict[sym]:
             print("player",p,"has won!")
             return True



# def play() oversees the player's moves
# Input: gamestate, players, player symbols
# Output: A winner or draw
def play(state,p1,p2,p1Sym,p2Sym):
    sym = {1:"X" , 2:"O"} # if a symbol randomizes to 1 it becomes X
    board = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    print("Player", p1, "will go first and will play with the", sym[p1Sym])
    printBoard(board)

    while state == PLAY:
         print("Player", p1, "what is your choice?: ")
         p1Choice = player(board,sym,p1Sym,p2Sym)
         if p1Choice == -1:
              #if the first player types -1, open a file and save the board
              saveFile = open("tic.txt", "w")
              for s in board:
                   saveFile.write(str(s))
              saveFile.close()
              print("File Saved!")
              return #exit out of the play function
         elif p1Choice == -2:
              # if player types -2 brings the saved board into the game
              print("Game Loaded")
              loadFile = open("tic.txt")
              boardString = loadFile.readline()
              #updates the current board based off of the opened file
              for c in range(len(boardString)):
                   board[c] = boardString[c]
              printBoard(board)
         
         #value at the position of their choice changes to their symbol
         board[p1Choice - 1] = sym[p1Sym]
         printBoard(board)                       #prints updated board
         boardCheck(board,sym,p1Sym,p2Sym,state) #checks if the board is full after turn
         winCond(board,p1,sym,p1Sym)             #checks if won after this turn

         if winCond(board,p1,sym,p1Sym)== True:  #if they won
              return                             #exit play function
         if boardCheck(board,sym,p1Sym,p2Sym,state) == True:
              return 

         print("Player", p2, "What is you choice?: ")
         p2Choice = player(board,sym,p1Sym,p2Sym)
         #Second player saves board; This coulda been a function but oh well
         if p2Choice == -1:
              saveFile = open("tic.txt", "w")
              for s in board:
                   saveFile.write(str(s))
              saveFile.close()
              print("File Saved!")
              return
         #adds second player's symbol to the board
         board[p2Choice - 1] = sym[p2Sym]
         printBoard(board)
         boardCheck(board,sym,p1Sym,p2Sym,state) #Checks if board is full after this turn
         winCond(board,p2,sym,p2Sym)             #Checks if won after this turn
         if winCond(board,p2,sym,p2Sym) == True:
              return
         if boardCheck(board,sym,p1Sym,p2Sym,state) == True:
              return

#player() handles each player's choices and verifies that it's legit
#Input: game board, symbols
#Output: player choice    
def player(boardList,symDict,sym1,sym2):
     choice = int(input("(1-9) or -1 to Save or -2 to Load: "))
     #while input is less than 1 or greater than 9 (excepting -1/-2) reprompt
     while choice < -2 or choice > 9 or choice == 0:
          choice = int(input("Number must be 1 - 9, pick again: "))
     #while input has already been given reprompt for new input
     while boardList[choice - 1] == (symDict[sym1] or symDict[sym2]):
              choice = int(input("ALready taken, pick again: "))
     return choice 
         

#randomize() randomly chooses the player that goes first and their symbol
#Input: players, player symbols
#Output: player order and symbol ownership        
def randomize(p1, p2, p1Sym, p2Sym):
    import random
    p1 = random.randint(1,2)
    p2 = 0
    p1Sym = random.randint(1,2)
    p2Sym = 0

    #This part ensures that the players can't be given the same move
    if(p1 == 1):
        p2 = 2
    elif(p1 == 2):
        p2 = 1
    #This part ensures that the players can't get the same symbol
    if(p1Sym == 1):
        p2Sym = 2
    elif(p1Sym == 2):
        p2Sym = 1

    return (p1,p2,p1Sym,p2Sym)

def main():
     #initializes the players and symbols to 0
    p1 = 0
    p2 = 0
    p1Sym = 0
    p2Sym = 0
    #reassigns variables based on the random generator
    p1,p2,p1Sym,p2Sym = randomize(p1, p2, p1Sym, p2Sym)
    gamestate = PLAY
    #print ( p1, p2, p1Sym, p2Sym)
    play(gamestate,p1,p2,p1Sym,p2Sym)
    #whenever the program exits play() gamestate will be END
    gamestate = END
    #if the game has ended ask if they would like to replay
    if gamestate == END:
         replay = input("Would you like to play again? y/n: ")
         while replay.lower() != "y" and replay.lower() != "n":
              replay = input(" Only type 'y' or 'n': ") #Only accepts y or n
         if replay.lower() == "n":
              print("Thank You for playing")
         #attempts to reset the game; does not necessarily succeed
         elif replay.lower() == "y":
              p1,p2,p1Sym,p2Sym = randomize(p1, p2, p1Sym, p2Sym)
              gamestate = PLAY
              play(gamestate,p1,p2,p1Sym,p2Sym)
    gamestate = END
main()
