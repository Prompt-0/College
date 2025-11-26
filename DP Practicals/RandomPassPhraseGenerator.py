#!/usr/bin/env python3
import string
import secrets 

def generate_random_passphrase(length):
    # Define the character set (Letters, Digits, Punctuation)
    charset = string.ascii_letters + string.digits + string.punctuation
    
    # Generate the random string using crypto-secure random source
    password = ''.join(secrets.choice(charset) for _ in range(length))
    
    return password

# --- Script Start ---
print("--- Secure Random Passphrase Generator ---")

while True:
    try:
        user_input = input("Enter the desired length (e.g., 16): ")
        length = int(user_input)
        
        if length > 0:
            break
        print("Length must be a positive number.")
        
    except ValueError:
        print("Invalid input. Please enter a number.")

# Output the result
result = generate_random_passphrase(length)
print(f"\nGenerated Passphrase: {result}")
