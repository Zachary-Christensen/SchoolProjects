import hashlib
import time

class CharGetter:

    def __init__(self):
        self.character = chr(0)
    
    def getChar(self):
        return self.character
        
    # returns true when has completed a cycle
    def advanceChar(self):
        self.character = chr(ord(self.character) + 1)
        if (ord(self.character) > 127):
            self.character = chr(0)
            return True
        return False
        
    @staticmethod
    def createList(size):
        lst = []
        for i in range(size):
            lst.append(CharGetter())
        return lst
        
# builds strings using charGetters and synchronously advances them
class StringGetter:
    
    def __init__(self, lstCharGetter):
        self.lstCharGetter = lstCharGetter

    def getString(self):
        string = ""
        # read current string
        for i in range(len(self.lstCharGetter)):
            string += self.lstCharGetter[i].getChar()
        return string
        
    # returns True when has advanced past the last string
    def advanceString(self):
        # advance charGetters
        for i in range(len(self.lstCharGetter))[::-1]:
            if (self.lstCharGetter[i].advanceChar()):
                if (i == 0):
                    return True
                # else continue
            else:
                break
        return False


numberOfChars = 5
stringGetter = StringGetter(CharGetter.createList(numberOfChars))
stringToMatch = "11201994"
continueLoop = True
startTime = time.time()
charTimes = { 0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0}
while continueLoop:
    charsFound = 0
    string = stringGetter.getString()
    strBytes = string.encode()
    hash = hashlib.sha256(strBytes)
    if (hash.hexdigest().startswith(stringToMatch)):
        charsFound = 6
        print("**** FOUND BIRTHDAY ****")
        continueLoop = False
    if (hash.hexdigest()[0] == stringToMatch[0]):
        charsFound = 1
        for i in range(1, len(stringToMatch)):
            if (hash.hexdigest()[i] == stringToMatch[i]):
                charsFound += 1
            else:
                break
        if (charsFound > 0):
            if (charTimes[charsFound] == 0):
                print("\nFound {0} chars\nOrdinances of input characters".format(str(charsFound)))
                for i in range(len(string)):
                    print(f"{ord(string[i])} ", end="")
                print("")
                # print("String: '{0}'".format(string))
                print("Hash: {0}".format(hash.hexdigest()))
                timeSinceStart = time.time() - startTime
                print("Time since start {0} seconds".format(str(timeSinceStart)))
                charTimes[charsFound] = timeSinceStart
    if (stringGetter.advanceString()):
        numberOfChars += 1
        stringGetter = StringGetter(CharGetter.createList(numberOfChars))
        print("Testing strings of size {0}".format(numberOfChars))
