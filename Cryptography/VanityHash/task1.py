import hashlib
import time


def createSmallFile(fileName):
    file = open(fileName, "w")
    file.write("<256bits")
    file.close()


def createLargeFile(fileName):
    file = open(fileName, "w")
    for i in range(1100):
        file.write(str(i % 10))
    file.close()

def getHashTime(inputFileName):
    file = open(inputFileName, "r")
    string = file.read()
    strBytes = string.encode()
    startTime = time.time()
    numberOfIterations = 1 << 17
    inputHash = "2f4f9e4b5437b866d415e946dd3115378437f056261c19e109c7447af21ea56d"
    # for i in range(numberOfIterations):
    counter = 0
    while ((time.time() - startTime) < 1.0):
        counter += 1
        hash = hashlib.sha256(strBytes)
        if (hash.hexdigest() == inputHash):
            print("Found hash on iteration {0}".format(str(i)))
    totalTime = (time.time() - startTime)
    print("=== Results ===")
    print("String used: {0}".format(string))
    print(f"Time to check {counter:,d} hashes: {totalTime} seconds")
    # print(f"Estimated time to check 2 ^ 255 hashes {(1 << 255) * totalTime / numberOfIterations}")


createSmallFile("smallFile.txt")
createLargeFile("largeFile.txt")

getHashTime("smallFile.txt")
getHashTime("largeFile.txt")

