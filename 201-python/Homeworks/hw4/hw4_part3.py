# File: hw4_part3.py 
# Author: Joel Okpara
# Date: 2/28/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Figures out how much money user made for charity
#              based on the amount of pledges and plunges

def main():
    pledges = int(input("How many pledges did you get? "))
    value = 0
    fkThis = range(1, (pledges + 1))
    for n in fkThis:
        value = float(input("What was the value of donation "+ str(n)+": "))
        totalValue = value + value
    
    plunge = int(input("How many plunges did you do? "))
    earned = totalValue * plunge
    
    print("Based on your",plunge,"plunges, you earned:","$"+str(earned),"for charity")
main()
