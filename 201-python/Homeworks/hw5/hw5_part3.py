# File: hw5_part3.py
# Author: Joel Okpara
# Date:3/6/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Rewrites phone number given by user in standard form

def main():

    number = input("Please enter a phone number: ")
    first = ""
    sec = ""
    third = ""
    if len(number) == 13:
        first = number[1:4]
        sec = number[5:8]
        third = number[9:]
    
    elif len(number) == 12:
        first = number[0:3]
        sec = number[4:7]
        third = number[8:]

    elif len(number) == 10:
        first = number[0:3]
        sec = number[3:6]
        third = number[6:]
    print("Your number in standard form is:")
    print("("+first+")",sec+"-"+third)

main()
