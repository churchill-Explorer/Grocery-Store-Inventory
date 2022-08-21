import re
import string

def getPurchases(filePath):
    #This function will open the text file and structure its contents.

    #Start an empty dict that will be returned.
    returnDict = {}
    
    #Using w/ open for best practices so it will auto close the file when done.
    with open(filePath, mode="r") as f:
        #For every line in the file perform this action:
        for line in f:
            if line.strip() in returnDict.keys():
                #If the item already exists in our dict add one to current value
                returnDict[line.strip()] = returnDict.get(line.strip()) + 1
            else:
                #If the item doesn't exists in our dict set value to one
                returnDict[line.strip()] = 1
    #Return dict
    return returnDict

def printItemsPurchasedInDay(filePath):
    #This function will print all items purchased in a given day.
    
    #Function call that returns the dict of all items in file.
    purchases = getPurchases(filePath)

    #Print header
    print("\nAll Items purchases in given day:")

    #This will cycle through purchases dict keys and print their values.
    for item in purchases:
        print(item + ": " + str(purchases.get(item)))

    #Clean up console.
    print("\n")
    
    #Return arb value.
    return -1

def getSpecificItemPurchaseCount(inputRec):
    #This function will print a specific item and how many purchases it has.
    
    #This splits the string by the deliminator to get filepath and name of item.
    item = inputRec.split("|")[1]
    filePath = inputRec.split("|")[0]
    
    #Function call to get all purchases.
    purchases = getPurchases(filePath)

    #Return arb value.
    return purchases.get(item, 0)

def createFreqDat(filePath):
    #This function will create the frequency.dat file requested.
    
    #Get Purchases.
    purchases = getPurchases(filePath)
    
    #Using best practice of 'with' to the file is auto closed upon completed work.
    #We're overwriting all current contents to ensure we don't add to an existing one.
    with open("frequency.dat", "w") as f:
        f.write("")

    #Using best practice of 'with' to the file is auto closed upon completed work.
    #We're appending to the file.
    with open("frequency.dat", "a") as f:
        for item in purchases.keys():
            tempString = item + "|" + str(purchases[item]) + "\n"
            f.write(tempString)
            
    #Return value isn't important.   
    return -1
