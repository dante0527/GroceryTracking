import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v


def listQty():
    grocery_data = {}

    # Open text file
    with open("groceries.txt", "r") as fin:
        # Read the whole file separated by line
        groceries = fin.readlines()

        # For each line, add or update its dictionary entry
        for item in groceries:
            item = item.strip()
            if item in grocery_data.keys():
                grocery_data[item] += 1
            else:
                grocery_data[item] = 1

    # Print each item and its quantity
    for item, qty in grocery_data.items():
        print(f"{item} {qty}")

    return 0

def getItemQty(selection):
    # Normalize case of input
    selection = selection.title()
    grocery_data = {}

    # Open text file
    with open("groceries.txt", "r") as fin:
        groceries = fin.readlines()

        # Add or update item in dictionary
        for item in groceries:
            item = item.strip()
            if item in grocery_data.keys():
                grocery_data[item] += 1
            else:
                grocery_data[item] = 1

    # Input validation for item
    try:
        print(f"{grocery_data[selection]} units of {selection} sold today.")
    except:
        print("Invalid Item")

    return 0

def getHistogramData():
    grocery_data = {}

    # Open text file
    with open("groceries.txt", "r") as fin:
        groceries = fin.readlines()

        # Create dictionary from data
        for item in groceries:
            item = item.strip()
            if item in grocery_data.keys():
                grocery_data[item] += 1
            else:
                grocery_data[item] = 1

    # Write each item to dat file with number
    with open("frequencies.dat", "w") as fout:
        for item, qty in grocery_data.items():
            fout.write(f"{item} {qty}\n")

    return 0