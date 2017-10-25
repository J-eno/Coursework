# File: hw4_part4.py 
# Author: Joel Okpara
# Date: 2/28/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Determines how many  vowels are in the string that the user provides

def main():
    sentence = input( "Please enter a string: ")

    vowelCount = 0
    for c in sentence:
        if c.lower() == "a" or c.lower() == "e" or c.lower() == "i" or c.lower() == "o" or c.lower() == "u" or c.lower() == "y":
            vowelCount = vowelCount + 1
    print("There are",vowelCount,"vowels in the string:", sentence)

main()
