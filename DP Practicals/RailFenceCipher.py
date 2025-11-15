def encrypt_rail_fence(plaintext: str, rails: int) -> str:
    if rails <= 1 or rails >= len(plaintext):
        return plaintext

    fence = [''] * rails
    rail = 0
    direction = 1  # 1 = down, -1 = up

    for ch in plaintext:
        fence[rail] += ch
        rail += direction
        if rail == 0 or rail == rails - 1:
            direction *= -1

    return ''.join(fence)


def decrypt_rail_fence(ciphertext: str, rails: int) -> str:
    if rails <= 1 or rails >= len(ciphertext):
        return ciphertext

    n = len(ciphertext)
    pattern = [[''] * n for _ in range(rails)]
    rail = 0
    direction = 1

    for i in range(n):
        pattern[rail][i] = '*'
        rail += direction
        if rail == 0 or rail == rails - 1:
            direction *= -1

    idx = 0
    for r in range(rails):
        for c in range(n):
            if pattern[r][c] == '*' and idx < n:
                pattern[r][c] = ciphertext[idx]
                idx += 1

    result = []
    rail = 0
    direction = 1
    for i in range(n):
        result.append(pattern[rail][i])
        rail += direction
        if rail == 0 or rail == rails - 1:
            direction *= -1

    return ''.join(result)

msg = "HELLORAILFENCECIPHER"
r = 3

enc = encrypt_rail_fence(msg, r)
print("Encrypted:", enc)   # HORELCLNHIEERILFPC

dec = decrypt_rail_fence(enc, r)
print("Decrypted:", dec)   # HELLORAILFENCECIPHER