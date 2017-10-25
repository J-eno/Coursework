#File: speeding.py
#Author: Joel Okpara
#Date: 2/22/2016
#Section: 04
#E-mail: joelo1@umbc.edu
#Description: This program calculates the fine for driving over
#             the speed limit.

def main():

    speedLimit = int(input("What was the speed limit?"))
    userSpeed = float(input("At how many miles per hour were you driving?"))
    overSpeed = userSpeed - speedLimit
    print("You were over the speed limit by", overSpeed,"MPH")

    if overSpeed < 5:
        print ("You receive no ticket... this time.")
    elif overSpeed >= 5 and overSpeed < 15:
        print ("You receive a ticket for a $100 fine!")
    elif overSpeed >= 15 and overSpeed < 30:
        print("You receive a ticket for a $200 fine!")
    elif overSpeed >= 30:
        print("You receive a ticket for a $500 fine, and a mandatory court date!")

main()
