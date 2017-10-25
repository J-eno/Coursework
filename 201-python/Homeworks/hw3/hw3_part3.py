# File: hw3_part3.py
# Author: Joel Okpara
# Date: 2/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program guesses what character the user is thinking of

def main():
#This segment checks if the character is a woman
    woman = input("Is your character a woman?(y/n)")
    if woman == "y":
        blueEyes = input("Does your character have blue eyes?(y/n)")
        if blueEyes == "y":
            print("Your character is Jane!")
        else:
            print("Your character is Marni!")
    elif woman == "n":
#If the character is not a woman, checks for glasses
        glasses = input("Does your character wear glasses?(y/n)")
        if glasses == "y":
            print("Your character is Adrian!")
        elif glasses == "n":
#if the character does not wear glasses, checks for beard
            beard = input("Does your character have a beard?(y/n)")
            if beard == "n":
                print("Your character is Zhang!")
            else:
                print ("Your character is Peder!")

main()

