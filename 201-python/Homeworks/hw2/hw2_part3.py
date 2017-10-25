#File: hw2_part3.py
#Author: Joel Okpara
#Date: 2/14/16
#Lab Section: 04
#Umbc email: joelo1@umbc.edu
#Description: This program extracts dollars and cents from a price

price = float(input("What is the price"))
dollar = price // 1
cents = price - dollar
print("The number of dollars is:",dollar)
print("The number of cents is:",cents)
