# File: hw6_part1.py 
# Author: Joel Okpara
# Date: 3/26/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Reads in numbers from the user and adds them to a list
#              if not in list already


def main():

    numList = []
    while len(numList) < 8:
        userNum = int(input("Please enter a whole number: "))
        for n in numList:
            if n == userNum:
                print("The number",userNum, "is already in the list")
                numList.remove(n)
        numList.append(userNum)

    if len(numList) == 8:
        print("\nThe contents of this list are:")
        for idk in numList:
            print(idk)


main()
