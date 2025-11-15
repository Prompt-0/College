import hashlib

def create_hash_256(password_string):
    password_in_bytes = password_string.encode('UTF-8')
    print(password_in_bytes)
    hash_object = hashlib.sha256(password_in_bytes)
    print(hash_object)
    hashed_password = hash_object.hexdigest()
    hashed_password = hashed_password.upper()
    return hashed_password

password = 'this_IS_my_password'
result = create_hash_256(password)
print(result)


# def create_hash_256_by_me(password_string):