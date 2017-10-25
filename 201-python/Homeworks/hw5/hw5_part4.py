# File: hw5_part4.py
# Author: Joel Okpara
# Date:3/6/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: This program helps calculate the tip at a resaurant

#I GIVE UP
def left(num):
    print("There are",num,"points left")

def main():

    points = int(input("How many points will you compete for?(13pts - 21pts) "))
    while points < 13 or points > 21:
        points = int(input("You can only compete for 13 to 21 points "))
    
    player1 = 0
    player2 = 0

    print("Player 2 starts!")
    while points > 0:
        p2 = int(input("Player 2, How many points will you take?(1-3pts): "))
        while p2 > 3 or p2 < 1:
            p2 = int(input("Player 2, you can only pick 1-3pts!"))
        player2 = player2 + p2
        points = points - p2
        print()
        if points == 0:
            print("Player 1 took",player1,"points")
            print("Player 2 took",player2,"points")
            if player1 > player2:
                print("Congrats!! Player 1 wins!!!")
            elif player2 > player1:
                print("Congrats!! Player 2 win!!!")
            else:
                print("tie")

        left(points)
        p1 = int(input("Player 1, How many points will you take?(1-3pts) "))
        while p1 > 3 or p1 < 1:
            p1 = int(input("Player 1, you can only pick 1-3pts!"))
        player1 = player1 + p1
        points = points - p1
        print()
        left(points)

        #SOME OF THE WORST CODE I'VE WRITTEN
        
        while points == 2:
            p2 = int(input("Player 2, How many points will you take?(1-2pts) "))
            while p2 > 2 or p2 < 1:
                p2 = int(input("Player 2, you can only take between 1-2pts "))
            player2 = player2 + p2
            points = points - p2
            print()
            if points == 0:
                print("Player 1 took",player1,"points")
                print("Player 2 took",player2,"points")
                if player1 > player2:
                    print("Congrats!! Player 1 wins!!!")
                elif player2 > player1:
                    print("Congrats!! Player 2 win!!!")
                else:
                    print("tie")

            left(points)
            p1 = int(input("Player 1, How many points will you take?(1-2pts) "))
            while p1 > 2 or p1 < 1:
                p1 = int(input("Player 1, you can only take between 1-2pts "))
            player1 = player1 + p1
            points = points - p1
            print()
            left(points)

            #IT DOESN'T EVEN WORK WELL

        while points == 1:
            p2 = int(input("Player 2, How many points will you take?(1pts) "))
            while p2 > 1 or p2 < 1:
                p2 = int(input("Player 2, you can only take 1pts "))
            player2 = player2 + p2
            points = points - p2
            print()
            if points == 0:
                print("Player 1 took",player1,"points")
                print("Player 2 took",player2,"points")
                if player1 > player2:
                    print("Congrats!! Player 1 wins!!!")
                elif player2 > player1:
                    print("Congrats!! Player 2 win!!!")
                else:
                    print("tie")

            left(points)
            p1 = int(input("Player 1, How many points will you take?(1pts) "))
            while p1 > 1 or p1 < 1:
                p1 = int(input("Player 1, you can only take 1pts "))
            player1 = player1 + p1
            points = points - p1
            print()
            left(points)
            
        if points == 0:
            print("Player 1 took",player1,"points")
            print("Player 2 took",player2,"points")
            if player1 > player2:
                print("Congrats!! Player 1 wins!!!")
            elif player2 > player1:
                print("Congrats!! Player 2 win!!!")
            else:
                print("tie")



            


main()
