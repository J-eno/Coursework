# File: hw8_part2.py
# Author: Joel Okpara
# Date:
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: prints a hollow square based on the user's specifications


#hollowSquare() print's out a square based on what it gets from the user
#Input: Square specifications and a counter
#Output: a hollow square
def hollowSquare(sqHeight,sqSym,count):
    #learned that the hollow of the square is always 2 spaces less than the height of the square
    hollow = sqHeight -2
    #if we're not on the final row, print the hollow spaces
    if count < sqHeight -1:
        if count == 0: #unless we are on the first row
            print(sqSym * sqHeight)
        else:
            print((sqSym) + (" " * hollow) + (sqSym))
        hollowSquare(sqHeight,sqSym,count+1)
    else:
        print(sqSym * sqHeight) #we are on the final row here
    
def main():
    height = int(input("Please enter the height of your square: "))
    while height <= 0:
        height = int(input("Please enter the height of your square (greater than 0): "))
    
    sym = input("What character would you like your square to be made of: ")
    counter = 0
    ourSquare = hollowSquare(height,sym,counter)
    print(ourSquare)
main()
