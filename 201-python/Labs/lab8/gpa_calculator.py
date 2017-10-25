# File: gpa_calculator.py
# Author: Joel Okpara
# Date: 4/4/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: YOUR DESCRIPTION GOES HERE AND HERE
# YOUR DESCRIPTION CONTINUED SOME MORE

CLASSES = 3

def convertLetter(letter):
    if letter == "A":
        return 4
    elif letter == "B":
        return 3
    elif letter == "C":
        return 2
    elif letter == "D":
        return 1
    else:
        return 0

def main():
    gradesFile = open("grades.txt")
    gpaFile = open("results.txt","w")
    for l in gradesFile:
        fName, lName, g1, g2, g3 = l.strip().split(";")
        g1 = convertLetter(g1)
        g2 = convertLetter(g2)
        g3 = convertLetter(g3)
        gpa = (g1 + g2 + g3)/CLASSES
        gpa = format(gpa, ".2f")
        print(fName, lName+"'s", "GPA is:", gpa)
        gpaFile.write(fName+" "+lName+"'s GPA is: "+str(gpa)+"\n")

    gpaFile.close()
main()
