# File: hw5_part2.py
# Author: Joel Okpara
# Date:3/6/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program calculates the cost of making copies at the UMBC copy center

FIRST = 100
FIRST_100 = 0.08
SECOND = 900
NXT_900 = 0.06
THIRD = 9000
NXT_9K = 0.05
OVER_10K = 0.04
def main():

    copies = float(input("How many copies would you like? "))
    while copies % 1 != 0:
        copies = int(input("Only whole numbers please!: "))
    total = 0
    if copies <= 100:
        total =  copies * FIRST_100

    #idk how to explain this mess
    elif copies > 100 and copies <= 1000:
        cpTotal1 = FIRST * FIRST_100
        cp2 = copies - FIRST
        cpTotal2 = cp2 * NXT_900
        total = cpTotal1 + cpTotal2

    elif copies > 1000 and copies <= 10000:
        cpTotal1 = FIRST * FIRST_100
        cp2 = copies - FIRST
        cpTotal2 = cp2 * NXT_900
        cp3 = copies - SECOND - FIRST
        cpTotal3 = cp3 * NXT_9K
        total = cpTotal1 + cpTotal2 + cpTotal3

    elif copies > 10000:
        cpTotal1 = FIRST * FIRST_100
        cp2 = copies - FIRST
        cpTotal2 = cp2 * NXT_900
        cp3 = copies - SECOND - FIRST
        cpTotal3 = cp3 * NXT_9K
        cp4 = copies - THIRD - SECOND - FIRST
        cpTotal4 = cp4 * OVER_10K
        total = cpTotal1 + cpTotal2 + cpTotal3+cpTotal4

    
    print("The total cost for",copies,"copies is $"+ str(total))

main()
