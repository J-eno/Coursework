# File: hw4_part5 
# Author: Joel Okpara
# Date: 2/28/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Prints numbers 1 to 100 unless the number is divisible by 3,5, or 3 and 5
#              prints a quote instead

def main():

    numbers = range(1, 101)
    for n in numbers:
        if (n % 3 == 0) and (n % 5 == 0):
            print("In the future, everyone will be world famous for 15 minutes.")
        elif (n % 5 == 0):
            print("Where do you see yourself in five years?")
        elif (n % 3 == 0):
            print("Better three hours too soon than a minute too late.")
        else:
            print(n)

main()
