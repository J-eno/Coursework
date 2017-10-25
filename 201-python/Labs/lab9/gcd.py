# File: 
# Author: Joel Okpara
# Date:
# Section: 04
# E-mail: joelo1@umbc.edu
# Description:


# Python program greatest common divisor (GCD) of two numbers.
# The GCD is the largest positive integer that perfectly
# divides the two given numbers.
def gcd(x, y):
    if x > y:
        smaller = y
    else:
        smaller = x
    gcd = 0
    for i in range(1,smaller+1):
        if((x % i == 0) and (y % i == 0)):
            gcd = i
    return gcd
#No errors below this line
def main():
    print("Should print: 15\nPrints: ",end="")
    print(gcd(30,15))
    print("Should print: 7\nPrints: ",end="")
    print(gcd(7, 49))
    print("Should print: 45\nPrints: ",end="")
    print(gcd(45,45))
main()
