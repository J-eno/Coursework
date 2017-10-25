#File: milesPerWeek.py
#Author: Joel Okpara
#Date: 2/17/2016
#Section: 04
#Email: joelo1@umbc.edu
#Description: This program calculates how many miles
#             the user drives per week, and how many
#             hours they spend in a car
MPH =65
def main():
    print("Welcome to Miles per week calculator 1.0!")
    distance = float(input("How many miles away is your trip(One way)"))
    daysAWeek = int(input("How many days a week do you go to work?"))
    milesAWeek = distance * 2 * daysAWeek
    hoursInCar = milesAWeek / MPH

    print("In a typical week, you drive", milesAWeek,"miles a week!")
    print("That means that at 65 mph  you spend", hoursInCar, "hours in a car each week!")

main()
