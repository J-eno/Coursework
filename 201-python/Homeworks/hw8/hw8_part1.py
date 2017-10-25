# File: hw8_part1.py 
# Author: Joel Okpara
# Date: 4/24/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Finds the max number in a list, recursively

STOP = -1

#maxInt() finds the largest integer in the list given
#Input: List of numbers
#Output: largest number
def maxInt(numList):
    #if there is only one number on the list, that number is the max
    if len(numList) == 1:
        return numList[0]
    else:
        #we iterate through the list, ignoring the first value, and find the largest number
        largest = maxInt(numList[1:])
        #if the largest number is greater than the first value in the list, return largest
        if largest > numList[0]:
            return largest
        else:
            return numList[0]
    
def main():
    
    myList = []
    userNum = 0
    #Allows user to keep inputting numbers to the list until they don't want to anymore
    while userNum != STOP:
        userNum = int(input("Enter a number to add to the list, or '-1' to stop: "))          
        myList.append(userNum)
    if userNum == STOP:
        myList.remove(STOP)#removes -1 from list of numbers
        print()

    maxNum = maxInt(myList)
    print("The list you gave us is:",myList)
    print("The maximum value in this list is:",maxNum)
main()
