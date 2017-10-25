#File: hw2_part2.py
#Author: Joel Okpara
#Date: 2/14/16
#Lab Section: 04
#UMBC email: joelo1@umbc.edu
#Description: This program calculates the total price after buying a book

TAX = 0.065
SHIPPING = 1.95

bookPrice = float(input("What is the price of the book?"))
bookQuantity = int(input("How many copies of this book would you like?"))
cost = bookPrice * bookQuantity
currentTax = cost * TAX
shippingCharge = bookQuantity * SHIPPING
totalCost = cost + currentTax + shippingCharge
print("Base Price:",cost)
print("Tax: +",currentTax)
print("Shipping: +",shippingCharge)
print("Total:",totalCost)
