# File: hw7_part1
# Author: Joel Okpara
# Date: 4/2/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Converts the letters in a phone number into numbers


# convertLetter() converts a letter into a number based on what letter it is
# Input:   A letter
# Output:  corresponding number
def convertLetter(letter):

    if letter.lower() == "a" or letter.lower() == "b" or letter.lower() == "c":
        letter = "2"
    if letter.lower() == "d" or letter.lower() == "e" or letter.lower() == "f":
        letter = "3"
    if letter.lower() == "g" or letter.lower() == "h" or letter.lower() == "i":
        letter = "4"
    if letter.lower() == "j" or letter.lower() == "k" or letter.lower() == "l":
        letter = "5"
    if letter.lower() == "m" or letter.lower() == "n" or letter.lower() == "o":
        letter = "6"
    if letter.lower() == "p" or letter.lower() == "q" or letter.lower() == "r" or letter.lower()== "s":
        letter = "7"
    if letter.lower() == "t" or letter.lower() == "u" or letter.lower() == "v":
        letter = "8"
    if letter.lower() == "w" or letter.lower() == "x" or letter.lower() == "y" or letter.lower()== "z":
        letter = "9"

    return letter
    
def main():
    print("Welcome to the Telephone Converter")
    phone = input("Enter the phone number: ")

    newPhone = ""
    
    for c in phone:
        #if c is a number, space, or hyphen add it to the newPhone string
        if c.isdigit():
            newPhone = newPhone + c
        elif c == "-":
            newPhone = newPhone + c
        elif c == " ":
            newPhone = newPhone + c
        #if c is a letter, run the convertLetter function
        else:
            newLetter = convertLetter(c)
            newPhone = newPhone + newLetter
    print(newPhone)

main()
