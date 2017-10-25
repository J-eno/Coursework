# File: hw3_part4.py 
# Author: Joel Okpara
# Date: 2/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program takes a tempurature from the user
# and calculates the state of water at that temperature

def main():
# The Freezing point in celsius is 0 degrees
# The Boiling point in celcius is 100 degrees

# The Freezing point in Farenheit is 32 degrees
# The Boiling piong in Farenheit is 212 degrees

    temperature = float(input("Please enter the temperature"))
    scale = input("Please enter 'c' for Celcius, or 'f' for Farenheit")
    if scale != "c" and scale != "f":
        print("Your input must be 'C' or 'F'!")
    
#Does celsius calculations
    if scale == "c":
        if temperature <= 0:
            print("At this temperature, water is a solid")
        elif temperature > 0 and temperature < 100:
            print("At this temperature, water is a liquid")
        else:
            print("At this temperature, water is a gas")
#does farenheit calculations
    elif scale == "f":
        if temperature <= 32:
            print("At this temperature, water is a solid")
        elif temperature > 32 and temperature < 212:
            print("At this temperature, water is a liquid")
        else:
            print("At this temperature, water is a gas")
main()
