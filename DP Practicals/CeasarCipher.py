def encrypt_caesar(plaintext: str, shift: int) -> str:
    ciphertext = []
    for ch in plaintext:
        if 'A' <= ch <= 'Z':
            idx = ord(ch) - ord('A')
            c = chr((idx + shift) % 26 + ord('A'))
            ciphertext.append(c)
        elif 'a' <= ch <= 'z':
            idx = ord(ch) - ord('a')
            c = chr((idx + shift) % 26 + ord('a'))
            ciphertext.append(c)
        else:
            ciphertext.append(ch)
    return ''.join(ciphertext)


def decrypt_caesar(ciphertext: str, shift: int) -> str:
    return encrypt_caesar(ciphertext, -shift)



text = "Hello, World!"
key = 3

encrypted = encrypt_caesar(text, key)
print("Encrypted:", encrypted)   # Khoor, Zruog!

decrypted = decrypt_caesar(encrypted, key)
print("Decrypted:", decrypted)   # Hello, World!