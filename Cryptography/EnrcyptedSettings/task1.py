from cryptography.fernet import Fernet
key = Fernet.generate_key()
f = Fernet(key)
message = b"Meet me at midnight"
token = f.encrypt(message)
print("Message: " + str(message))
print("Key: " + str(key))
print("Encrypted Text: " + str(token))
print("Decrypted Text: " + str(f.decrypt(token)))
input()