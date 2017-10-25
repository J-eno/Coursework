# File: hw4_part1.py 
# Author: Joel Okpara
# Date: 2/28/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program creates a multiplication table for
#              any number the user wants

def main():

    #Get's numbers from user
    base = int(input("What number do you want a multiplication chart for? "))
    maxNum = int(input("How far do you want the chart to go? "))

    for n in range(maxNum):#Creates a list the size of the user's input or something
        chart = base * n
        print(str(base) + "*" + str(n) + "=" +str(chart) )

main()
