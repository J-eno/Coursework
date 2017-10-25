# File: palindrome.py
# Author: Joel Okpara
# Date: 4/11/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description:


#tests whether myString is a palindrome
def isPalindrome(myString):
    tempString = myString
    length = len(tempString)
    half = length/2
    isPalindrome=True
    for i in range(int(half)+1):
        if myString[i] != myString[(length-1)-i]:
            isPalindrome = False
    print(isPalindrome)
#no errors below this line
def main():
   # print(len("oozyratinasanitaryzoo"))
    print("Should print: True\nPrints: ",end="")
    isPalindrome("oozyratinasanitaryzoo")
    print("Should print: False\nPrints:", end="")
    isPalindrome("18101181")
main()
