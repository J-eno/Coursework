# File: tv_shows.py
# Author: Joel Okpara
# Date: 3/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: YOUR DESCRIPTION GOES HERE AND HERE
# YOUR DESCRIPTION CONTINUED SOME MORE

def main():
    shows = ["Daredevil", "Fargo","Limitless", "Elementary","Brooklyn 99", "Empire", "Supergirl"]

    for s in range(len(shows)):
        print( str(s+1)+ " - " + shows[s])
        
    print("You and your friends are voting on a show to watch.")
    print("Which show would you like to vote for?")
    userInput = 1000

    votes = [0] * len(shows)
    while userInput != 0:
        userInput = int(input("Enter '0' to stop voting: "))
        votes[userInput - 1] = votes[userInput - 1] + 1

    if userInput == 0:
        print("here are the final votes:")
        for s in range(len(shows)):
            print(shows[s] + " has\t" + str(votes[s])+ " votes")
main()
