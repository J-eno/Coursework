#File: manners.py
#Author: Joel Okpara
#Date: 2/22/2016
#Section: 04
#E-mail: joelo1@umbc.edu
#Description: This program checks the manners of the user

def main():

    word = input("Please enter a word  ")
    if word == "please" or word == "thank you" or word == "excuse me":
        print("Your manners are impeccable!")
    else:
        print("How rude!")


main()
