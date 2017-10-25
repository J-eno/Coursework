# File: proj2.py 
# Author: Joel Okpara
# Date: 5/9/16
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Finds words on a word search using the puzzle and word list given

REFERENCE = [-1,0,1] #values used in a dictionary reference system

#inputVal() validates that the user is inputting a .txt file
#Input: A file chosen by the user
#Output: Whether or not it's a .txt file
def inputVal(aFile):
    if (aFile[-4:] != ".txt"):
        return False
    else:
        return True

#printFile() prints the contents of the file given to the screen
#This function is mainly just to let the user see the puzzle and word list
#Input: A file
#Output: Contents printed to screen
def printFile(aFile):
    for l in aFile:
        print(l.strip())

#make2D() makes the unseen 2D list that we will search through for words
#Input: The puzzle file chosen by the user
#Output: a 2D list of the puzzle
def make2D(aFile):
    aList = []
    for l in aFile:
        aList.append(l.strip().split())
    return aList

#findFirst() finds the first letter of the word in the puzzle file
#then searches in every direction in order to find the rest of the word
#Input: The word, the puzzle grid, the current row and column, and the row and column directions to look in
#Output: Whether or not the whole word is found
def findWord(word, list2D, row, col, rowDir, colDir):
    #would normally be len(word) == 0, but I never stripped the whitespace so len(word) will never be 0
    if (len(word) == 1):
        return True
    #Makes sure that the "cursor" stays within the grids boundaries
    if (row < 0 or row > len(list2D) - 1) or (col < 0 or col > len(list2D[row]) - 1):
        return False
    #If the first letter of given word is in the 2d list
    if (word[0] == list2D[row][col]):
        #call the function again starting at the next letter, add the direction numbers in order to search in
        #all 8 directions
        return findWord(word[1:], list2D, row + rowDir, col + colDir, rowDir, colDir)

    return False
#directionCheck() checks figures out which direction the word went in based on what numbers we added or
#subtracted to the rows and columns in order to find the word
#Input: the word and 2D list
#Output: Whether the word was found, the key to the direction diictionary, and the row/ column coordinates
def directionCheck(word, list2D):
    for r in range(0,len(list2D)):        #for each row coordinate
        for c in range(0,len(list2D[r])): #for each column coordinate
            for clmDir in REFERENCE:      #for each column direction(left a column, stay in same column ,right a column)
                for rwDir in REFERENCE:   #for each row direction(up a row, stay in same row, down a row)
                    if findWord(word, list2D, r, c, rwDir, clmDir) == True: #if we found the word
                        #put the numbers we used to find the word together to make the keys for a dictionary
                        dirKey = "{row}{col}".format(row = rwDir, col = clmDir)
                        #return (wordFound, Key for the dictionary, row/colum coordinates
                        return True, dirKey, r, c
    else:
        return False, None, None, None


def main():

    #Input the puzzle you want to find from
    puzzInput = input("What puzzlefile would you like to use? ")
    while inputVal(puzzInput) != True:
        puzzInput = input("invalid file name, try again: ")

    #Input the word list that you want to find
    wordInput = input("What word list file would you like to use? ")
    while inputVal(wordInput) != True:
            wordInput = input("invalid file name, try again: ")

    #File I/O
    puzzFile = open(puzzInput)
    wordFile = open(wordInput)
    puzzList = puzzFile.readlines()
    wordList = wordFile.readlines()
    
    #Print puzzle and word list to screen
    print("\nHere is the word search")
    printFile(puzzList)
    print()
    print("Here is the word list")
    printFile(wordList)
    print()

    # assign 2D list to puzz2D
    puzz2D =  make2D(puzzList)

    #dictionary for directional phrases
    wordDirections = {"-1-1": "Diagonally Up and Left", "-10":"Up", "-11": "Diagonally Up and Right", "0-1":"Backwards and Left", "01": "Right", "1-1": "Diagonally Down and Left", "10": "Down", "11": "Diagonally Down and Right"}

#################### DICTIONARY LOGIC ####################################################################
#look up a row = -1
#same row = 0
#look down a row = 1

#look left a column = -1
#same column = 0
#look right a column = 1

# So for example if I found a word by adding -1 to the row coordinates and -1 to the column coordinates
# that means the word was going Diagonally Up and Left

#######################################################################################################
    
    for string in wordList: #for each word in my list of words
        #assigning the values that I returned from directionCheck() to these variables
        wordFound, direction, r, c = directionCheck(string,puzz2D)
        if wordFound == True:
            print("The word", string.strip(), "starts in", r, ",",c, "and goes", wordDirections[direction])
        else:
            print("The word", string.strip(), "does not appear in this puzzle")
main()
