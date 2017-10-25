# File: hw3_part2.py
# Author: Joel Okpara
# Date: 2/21/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description:
# This program calculates your weighted total and letter grade
# 
def main():
#this segment calculates the weighted total
   homeworkWeight = float(input("Please enter the homework weight"))
   homeworkGrade = float(input("Please enter your homework grade"))
   examWeight = float(input("Please enter the exam weight"))
   examGrade = float(input("Please enter your exam grade"))
   disWeight = float(input("Please enter the discussion weight"))
   disGrade = float(input("Please enter your discussion grade"))

   weightedTotal = (homeworkWeight * homeworkGrade) + (examWeight *examGrade) + (disWeight * disGrade)
#This segment assigns the weighted total to a letter grade
   letterGrade = "A"
   if weightedTotal > 90:
      letterGrade =" A"
   elif weightedTotal >80 and weightedTotal <90:
      letterGrade =" B"
   elif weightedTotal >70 and weightedTotal <80:
      letterGrade = "C"
   elif weightedTotal >60 and weightedTotal <70:
      letterGrade = "D"
   elif weightedTotal <60:
      letterGrade = "F"


   print("Your total grade is:",weightedTotal)
   print("Your letter grade is:",letterGrade)
main()
