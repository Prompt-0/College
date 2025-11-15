import itertools
import string


def brute_force_cracker(target_password, charset, max_length):
    attempts = 0
    for length in range(1, max_length + 1):
        # Generate every possible combination of characters for the current length
        for guess_tuple in itertools.product(charset, repeat=length):
            attempts += 1
            guess = "".join(guess_tuple)

            # Check if the generated guess matches the target password
            if guess == target_password:
                print(f"Password cracked! The password is '{guess}'.")
                print(f"Attempts: {attempts}")
                return attempts, guess

    print(
        f"Password not found after {attempts} attempts (searched up to length {max_length})."
    )
    return attempts, None


# --- Configuration ---
# All ASCII letters (uppercase and lowercase) and digits
character_set = string.ascii_letters + string.digits + string.punctuation

# The password to be cracked (for this example, a simple one is used)
password_to_crack = "ab123"

# The maximum length to check
max_pass_length = 5

# --- Run the simulation ---
print(f"Starting brute-force attack on password '{password_to_crack}'...")
brute_force_cracker(password_to_crack, character_set, max_pass_length)
