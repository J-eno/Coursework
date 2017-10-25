# File: hw7_part2
# Author: Joel Okpara
# Date: 4/2/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Converts Bucks to Bux

BUCK = 8
BUX = 0.125

#buckToBux() turns USD to Retriever Bux
#Input: Amount to convert in Dollars
#Output: Amount in Bux
def buckToBux(number):
    money = number * BUCK
    money = format(money, ".2f")
    return money

#buxToBuck() turns Bux into USD
#Input: Amount to convert in Bux
#Output: Amount in USD
def buxToBuck(number):
    money = number * BUX
    money = format(money, ".2f")
    return money

#bye() prints the goodbye text
#Input: none
#Output: goodbye text
def bye():
    print("Good bye, and thank you for using Currency Converter")

def main():
    
    print(""" What would you like to do?
1. Convert US Dollars to Retriever Bux
2. Convert Retriever Bux to US Dollars
3. exit""")
    #User needs to pick a number from the menu above
    menu = int(input("Enter your choice: "))

    #If they don't pick 1-3 reprompt them to
    while menu != 1 and menu!=2 and menu != 3:
        print(" That is an invalid choice")
        menu = int(input("Enter a valid choice: "))
    
    if menu == 1:
        amount = float(input("How many Dollars do you want to convert? "))
        final = buckToBux(amount)
        print( amount, "US Dollars equates to", final, "Retriever Bux")
        bye()

    if menu == 2:
        amount = float(input("How many Retriever Bux do you want to convert? "))
        final = buxToBuck(amount)
        print(amount, "Retriever Bux equates to", final, "US Dollars")
        bye()

    if menu == 3:
        bye()
main()
