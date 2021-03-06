#File:        hw2_part1.py
#Author:      Joel Okpara
#Date:        2/14/2016
#Lab Section: 04
#UMBC Email:  joelo1@umbc.edu
#Description: This program contains HW2 problems 1-10


#Question 1
#Expected Output: 55
num1 = (7 + 4) * 5
print("Num1 evaluates to:",num1)
#Actual Output: 55
#Explanation: Parentheses first (11), then multiply by 5 = 55


#Question 2
#Expected Output: 1
num2 =(15 % 7)
print("Num2 evaluates to:",num2)
#Actual Output: 1
#Explanation: 15 / 7 = 2 remainder 1 so 15 % 7 = 1


#Question 3 
#Expected Output: 32
num3 = (32 % 36)
print("Num3 evaluates to:",num3)
#Actual Output: 32
#Explanation: 36 cannot go into 32


#Question 4
#Expected Output: 12
num4 = (5 - 3) + (10 - 5) * (8 % 3)
print("Num4 evaluates to:",num4)
#Actual Output: 12
#Explanation: Doing parentheses first will give us
#             (2) + (5) * (2) [because 8 % 3 = 2]
#             Multiplication next = 2 + 10
#             = 12



#Question 5
#Expected Output: 4.5
num5 = 21 / 7 / 4 * (3 + 3)
print("Num5 evaluates to:", num5)
#Actual Output: 4.5
#Explanation: Parentheses first = 21 / 7 / 4 * 6
#             All of these are equal operations so go left to right
#             21 / 7 / 4 * 6
#             = 3 / 4 * 6
#             = 0.75 *6
#             = 4.5



#Question 6
#Expected Output: 14
num6 = 9 / 3 + 21 - 5 * 2
print("Num6 evaluates to:",num6)
#Actual Output: 14.0
#Explanation: Division and Miltiplication first will give us
#             3 + 21 - 10
#             = 14

#Question 7
#Expected Output: 14
num7 = 7 % 5 + 6 * 2
print("Num7 evaluates to:",num7)
#Actual Output: 14
#Explanation: Mod and Multiplacation first will give us
#             2 + 12
#             = 14


#Question 8
#Expected Output: 17.3
num8 = 35.2 / 2.3 + (332 % 33)
print ("Num8 evaluates to:",num8)
#Actual Output: 17.30434782608696
#Explanation: Parentheses first gives us
#             35.2 / 2.3 + 2
#             15.3 + 2
#             = 17.3
# I stopped at one decimal point


#Question 9
#Given Equation:  55 / 10 + 45 / 0.2
#Solved Equation: 55 / (10 + 45)/ 0.2
#Target Number: 5.0
num9 = 55 / (10 + 45) / 0.2
print("Num9 evaluates to:",num9, "and should be", 5.0)


#Question 10
#Given Equation: 65 // 20 + 10 - 4 % 4
#Solved Equation: 65 // (20 + 10) - 4 % 4
#Target Number: 2
num10 = 65 // (20 + 10) - 4 % 4
print ("Num10 evaluates to:", num10, "and should be", 2)

