# File: palindrome.py
# Author: Joel Okpara
# Date: 2/29/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Determines whether or not the word that the user provides
#              is a palindrome

def main():
    pali = input("Please enter a word: ")
    newString = ""
   
    for c in range((len(pali)-1),-1,-1):
        newString = newString + pali[c]
        
   
    if newString.lower() == pali.lower():
        print("This word is a palindrome!")
    else:
        print("This word is NOT a palindrome")
main()
