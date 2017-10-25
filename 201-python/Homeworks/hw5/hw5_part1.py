# File: hw5_part1.py
# Author: Joel Okpara
# Date:3/6/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program helps calculate the tip at a resaurant

def main():
    bill = float(input("What is the total bill?: "))
    print("What was the level of service?")
    service = input("(Please enter excellent, good, or bad): ")
    while (service.lower() != "excellent" and service.lower() != "good" and service.lower() != "bad"):
        service = input("(Please only enter excellent, good, or bad): ")


    #calculates tip based on the service rating
    tip = 0
    if service.lower() == "excellent":
        tip = bill * 0.25
    elif service.lower() == "good":
        tip = bill * 0.20
    elif service.lower() == "bad":
        tip = bill * 0.10
        
    if tip < 2:
        tip = 2
    total = bill + tip


    print("The bill was $" + str(bill))
    print("The service was",service)
    print("The tip is $" + str(tip))
    print("The grand total with the tip is $"+ str(total))
main()


