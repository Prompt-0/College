import hashlib
import sys

import requests

# The HIBP Pwned Passwords API endpoint
HIBP_API_URL = "https://api.pwnedpasswords.com/range/"


def check_password_pwned(password):
    """
    Checks a password against the HIBP Pwned Passwords API using k-Anonymity.
    Returns the number of times it was pwned, or 0 if not found.
    """
    if not password:
        return 0  # Skip empty passwords

    # 1. Hash the password using SHA-1
    sha1_hash = hashlib.sha1(password.encode("utf-8")).hexdigest().upper()

    # 2. Split the hash into prefix (first 5 chars) and suffix (the rest)
    hash_prefix = sha1_hash[:5]
    hash_suffix = sha1_hash[5:]

    try:
        # 3. Send only the prefix to the API
        response = requests.get(f"{HIBP_API_URL}{hash_prefix}")
        response.raise_for_status()  # Raise an exception for bad status codes

        # 4. Check the returned suffixes against our suffix
        # The API returns suffixes in the format: SUFFIX:COUNT
        pwned_suffixes = response.text.splitlines()

        for line in pwned_suffixes:
            suffix, count_str = line.split(":")
            if suffix == hash_suffix:
                # We found a match!
                return int(count_str)

        # 5. If we loop through and find no match, the password is safe
        return 0

    except requests.exceptions.ConnectionError:
        print(
            "Error: Could not connect to HIBP API. Check your internet connection.",
            file=sys.stderr,
        )
        return -1  # Use -1 to indicate an error
    except requests.exceptions.HTTPError as e:
        print(
            f"Error: API request failed with status {e.response.status_code}",
            file=sys.stderr,
        )
        return -1
    except Exception as e:
        print(f"An unexpected error occurred: {e}", file=sys.stderr)
        return -1


def main():
    """
    Main function to read the credentials file and check each password.
    """
    filename = "credentials.txt"

    print(f"Starting password check for users in '{filename}'...\n")

    try:
        with open(filename, "r") as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line:
                    continue  # Skip empty lines

                # Use split(',', 1) to only split on the first comma
                # This handles cases where the password might contain a comma
                parts = line.split(",", 1)
                if len(parts) != 2:
                    print(f"Warning: Skipping malformed line {line_num}: '{line}'")
                    continue

                username, password = parts

                if not password:
                    print(f"[ ] User '{username}' has an EMPTY password.")
                    continue

                pwned_count = check_password_pwned(password)

                if pwned_count > 0:
                    print(
                        f"[!] PWNED: User '{username}'s password was found {pwned_count:,} times."
                    )
                elif pwned_count == 0:
                    print(f"[+] SAFE: User '{username}'s password was NOT found.")
                else:
                    # This handles the -1 error case
                    print(f"[?] ERROR: Could not check password for user '{username}'.")

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.", file=sys.stderr)
    except Exception as e:
        print(f"An error occurred while reading the file: {e}", file=sys.stderr)


if __name__ == "__main__":
    main()
