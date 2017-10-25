# File: hw6_part2.py
# Author: Joel Okpara
# Date: 3/26/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: Outputs all the prime numbers from 2 to 500
#              

def main():

    prime = list(range(2,501))
    others = list(range(2,26))
    for o in others:
        for n in prime:
            if (n != o) and (n % o == 0):
                prime.remove(n)
    
    for n in prime:
        print(n, end = " ")

main()
