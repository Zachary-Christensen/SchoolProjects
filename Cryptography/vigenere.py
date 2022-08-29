

def removeNonAlphaAndSetLowercase(string):
    tempString = ""
    for i in range(len(string)):
        if (ord(string[i]) >= ord('a') and ord(string[i]) <= ord('z') or ord(string[i]) >= ord('A') and ord(string[i]) <= ord('Z')):
            tempString += string[i]
    return tempString.lower()
    
def encryptVigenere(plainText, key):
    cipherText = ""
    for i in range(len(plainText)):
        newOrd = ord(plainText[i]) + ord(key[i % len(key)]) - ord('a')
        if (newOrd > ord('z')):
            newOrd -= 26
        cipherText += chr(newOrd)
    return cipherText
    
def decryptVigenere(cipherText, key):
    plainText = ""
    for i in range(len(cipherText)):
        newOrd = ord(cipherText[i]) - ord(key[i % len(key)]) + ord('a')
        if (newOrd < ord('a')):
            newOrd += 26
        plainText += chr(newOrd)
    return plainText

def task1():
    print("Non-alpha characters will be removed, and uppercase characters will be converted to lowercase")
    print("Enter a message to encrypt")
    userMessage = removeNonAlphaAndSetLowercase(input())
    print("Enter a key")
    key = removeNonAlphaAndSetLowercase(input())
    
    cipherText = encryptVigenere(userMessage, key)
    plainText = decryptVigenere(cipherText, key)

    print("Encrypted Message: " + cipherText)
    print("Decrypted Message: " + plainText)
    

class CharGetter:

    def __init__(self):
        self.character = 'a'
    
    def getChar(self):
        return self.character
        
    # returns true when has completed a cycle
    def advanceChar(self):
        self.character = chr(ord(self.character) + 1)
        if (ord(self.character) > ord('z')):
            self.character = 'a'
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

def task2():
    print("Enter the cipher text to be decoded")
    cipherText = input()
    print("Enter a substring known to be in the plaintext")
    subString = input()
    print("Enter a maximum key size from 1 to 10")
    keySize = int(input())
    
    for i in range(keySize + 1)[1:]:
        stringGetter = StringGetter(CharGetter.createList(i))
        
        while True:
            possibleKey = stringGetter.getString()
            
            plainText = decryptVigenere(cipherText, possibleKey)
            if (subString in plainText):
                print("Decoded '" + plainText + "' using key: " + possibleKey)
                print("Do you wish to continue? (y/n)")
                if (input()[0].lower() != 'y'):
                    return
            
            if (stringGetter.advanceString()):
                break
        
        if (i < keySize):
            print("Finished testing keys of size " + str(i) + ".")
            print("Do you want to test keys of size " + str(i + 1) + "? (y/n)")
            if (input()[0].lower() != 'y'):
                return
    
def main():
    while True:
        print("Would you like to run task 1 or task 2? (enter 1, 2, or q to quit)")
        option = input()
        if (option == '1'):
            task1()
            print("\nEND OF TASK 1\n")
        elif (option == '2'):
            task2()
            print("\nEND OF TASK 2\n")
        elif (option == 'q'):
            print("Bye")
            break

if __name__ == "__main__":
    main()
