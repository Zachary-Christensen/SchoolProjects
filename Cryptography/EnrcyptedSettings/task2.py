from cryptography.fernet import Fernet
from os.path import exists
from os import remove

def stripString(string):
    return string.strip("b'").strip("'")
    
class MySettings:

    key : str
    scale : float
    value : int
    
    def __init__(self, key, scale, value):
        key = str(key)
        scale = float(scale)
        value = int(value)
        
        self.setKey(key)
        self.scale = scale
        self.value = value
    
    def setKey(self, string):
        if (string.__contains__("~")):
            print("Key cannot contain ~. Removing instances of ~ from key")
            string = string.replace("~", "")
        self.key = string
    
    def __str__(self):
        return "{0}~{1}~{2}".format(self.key, self.scale, self.value)
        
    @staticmethod
    def strToObject(string):
        string = string.split("~")
        return MySettings(string[0], string[1], string[2])


response = input("Enter 1, 2, 3 to select one of the following options\n\t(1) Read settings from the file\n\t(2) Modify settings in the file\n\t(3) Clear files\n")

keyPath = "key.txt"
encryptedFilepath = "config.txt"

if (response == "1" or response == "2"):
    myKey = ""
    if (exists(keyPath)):
        keyFile = open(keyPath, "r")
        myKey = keyFile.read()
        keyFile.close()
    else:
        myKey = Fernet.generate_key()
        keyFile = open(keyPath, "w")
        keyFile.write(stripString(str(myKey)))
        keyFile.close()

    f = Fernet(myKey)

    if (not exists(encryptedFilepath)):
        cipherTextFile = open(encryptedFilepath, "w")
        cipherTextFile.write(stripString(str(f.encrypt(bytes(str(MySettings(1, 2, 3)), 'utf-8')))))
        cipherTextFile.close()

    cipherTextFile = open(encryptedFilepath, "r")
    cipherText = bytes(cipherTextFile.read(), 'utf-8')
    cipherTextFile.close()

    plainText = stripString(str(f.decrypt(cipherText)))

    settings = MySettings.strToObject(plainText)
    
    if (response == "1"):
        print("Current values are \n\tKey:   {0}\n\tScale: {1}\n\tValue: {2}".format(settings.key, settings.scale, settings.value))
    elif (response == "2"):
        if (input("Would you like to update the key? (y/n)\n").lower() == 'y'):
            settings.setKey(str(input("Enter a new string for the key:\n")))
                
        if (input("Would you like to update the scale? (y/n)\n").lower() == 'y'):
            settings.scale = float(input("Enter a new float for the scale:\n"))
            
        if (input("Would you like to update the value? (y/n)\n").lower() == 'y'):
            settings.value = int(input("Enter a new integer for the value:\n"))     

        cipherText = stripString(str(f.encrypt(bytes(str(settings), 'utf-8'))))
        cipherTextFile = open(encryptedFilepath, "w")
        cipherTextFile.write(cipherText)
        cipherTextFile.close()
        
elif (response == "3"):
    if (exists(keyPath)):
        remove(keyPath)
    if (exists(encryptedFilepath)):
        remove(encryptedFilepath)
    
else:
    print("Invalid option")
        
print("Bye")