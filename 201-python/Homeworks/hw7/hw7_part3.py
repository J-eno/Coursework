# File: hw7_part3
# Author: Joel Okpara
# Date: 4/2/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: blah blahs the blah blah

def main():

    #Gets file from user, opens file and stores it all in a string
    theFile = input("Please enter the name of the file to open: ")
    while theFile[-3:] != "txt" and theFile[-3:] != "dat":
        print("The file must end in .txt or .dat to be valid")
        theFile = input("Please enter the name of the file to open: ")
    ourFile = open(theFile)
    wholeThing = ourFile.read()

    #Splits our string on it's whitespace into a list, count's the number of tokens in list
    # each token is a word
    words = wholeThing.split()
    numOfWords = len(words)
    print("\tThe file", theFile, "has", numOfWords, "words in it")
    
    #for each word in our list, counts the letters in our word and adds it to totalChars
    #divides totalChars by the amount of words in our list
    totalChars = 0
    for w in words:
        totalChars = totalChars + len(w)

    avgLength = totalChars / numOfWords

    #limits outcome to one decimal point
    avgLength = format(avgLength, ".1f")
    print("\tThe average length of each word is", avgLength, "letters long")

    #splits our big string on it's periods. Each token made is a sentence
    sentence = wholeThing.split(".")
    numOfSent = len(sentence)
    print("\tThere are", numOfSent, "sentences in this file")
main()
