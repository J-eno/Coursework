# File: 
# Author: Joel Okpara
# Date: 4/11/16
# Section: 04
# E-mail: joelo1@umbc.edu
# Description:

#letterCount should take a letter and word,
#and count the number of times letter appears
#in the word
def letterCount(letter,myString):
    count = 0
    for i in myString:
        if i == letter:
            count = count+1
    print(count)
#no errors below this line
def main():
 print("Should print: 3\nPrints: ",end="")
 letterCount("a","aardvark")
main()
