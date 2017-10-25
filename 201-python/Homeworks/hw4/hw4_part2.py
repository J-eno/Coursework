# File: hw4_part2.py 
# Author: Joel Okpara
# Date:2/28/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program prints out every 3rd letter that the user
#              inputs

def main():
    print("Welcome to 3rd letter simulator 1.0")

    sentence = input("Please enter a sentence: ")
    print("Original sentence: ", sentence)
    
    print("Every third letter:")
    third = []
    for w in range(0,len(sentence),3):
        third.append(sentence[w])
        #print(sentence[w]) puts does not put it on the same line
        #so I appended a list. Not sure which is better.
    print(third)
    

main()
