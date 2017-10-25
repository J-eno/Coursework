# File: hw8_part3.py 
# Author: Joel Okpara
# Date:
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Prints a list of all unique characters in a file

FILE = "input.txt"

#newChar() builds a list of unique characters in a file
#Input: big string of text
#Output: big list of unique chars
def newChar(text,uList):
    #if there's only one character and that character is not in the list yet, add it
    if len(text) == 1:
        if text[0] not in uList:
            uList.append(text[0])
        
    else:
        #we shorten our string by one and check the first character
        newChar(text[1:],uList)
        if text[0] not in uList:
            uList.append(text[0])
    #uList.sort()    
    return uList
    

def main():
    #file I/O
    myFile = open(FILE)
    chunk = myFile.read()
    myFile.close()

    unique = []
    newChar(chunk,unique)
    print(unique)

main()
