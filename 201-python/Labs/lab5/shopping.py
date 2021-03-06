# File: shopping.py
# Author: Joel Okpara
# Date: 3/7/2016
# Section: 04
# E-mail: joelo1@umbc.edu
# Description: allows the user to create a shooping list and calculate
#              how much the shopping trip cost.

def main():

    shopping = ""
    shoppingList = []
    while shopping != "done":
        shopping = input("Add an item to your list(type 'done' when finished): ")
        shoppingList.append(shopping)
    shoppingList.remove("done")
    if shopping == "done":
        print("Your final shopping list: ",shoppingList)
        print()

    total = 0
    while len(shoppingList)> 0:
        itemPrice = float(input("How much did "+shoppingList[0]+" cost? "))
        total = total + itemPrice
        shoppingList.remove(shoppingList[0])

    print()
    print("Your shopping trip cost $"+str(total))
    print("Shopping list at end of trip: ",shoppingList)

main()
