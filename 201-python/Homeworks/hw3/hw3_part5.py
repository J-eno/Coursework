# File: hw3_part5.py
# Author: Joel Okpara
# Date: 2/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program tells you what day it is
# based on what day of the month it is

def main():

#Input
    dom = int(input("Please enter the day of the month (1-31): "))

#Error message    
    if dom < 1 or dom > 31:
        print("Day is invalid, must be between 1 and 31")

#Main Process
    if dom == 1 or dom == 8 or dom == 15 or dom == 22 or dom == 29:
        print("Today is Monday")
    elif dom == 2 or dom == 9 or dom == 16 or dom == 23 or dom == 30:
        print("Today is Tuesday!")
    elif dom == 3 or dom == 10 or dom == 17 or dom == 24 or dom == 31:
        print("Today is Wednesday!")
    elif dom == 4 or dom == 11 or dom == 18 or dom == 25:
        print("Today is Thursday!")
    elif dom == 5 or dom == 12 or dom == 19 or dom == 26:
        print("Today is Friday!")
    elif dom == 6 or dom == 13 or dom == 20 or dom == 27:
        print("Today is Saturday!")
    elif dom == 7 or dom == 14 or dom == 21 or dom == 28:
        print("Today is Sunday!")

#THIS LOOKS SO INEFFICIENT BUT I DON'T KNOW HOW ELSE TO DO IT!!!
main()
