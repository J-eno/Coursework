# File: hw3_part1.py
# Author: Joel Okpara
# Date: 2/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description:
# This program recieves a float from the user and prints out whether
# it is positive, negative, or equal to zero
# 
def main():
    userFloat = float(input("Enter a number!"))
    if userFloat > 0:
        print ("Your number is positive!")
    if userFloat < 0:
        print ("Your number is negative!")
    if userFloat == 0:
        print ("Your number is zero!")
    
main()
