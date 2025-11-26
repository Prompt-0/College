import secrets
import sys

# --- Configuration ---
WORDLIST_FILENAME = "words.txt"
NUMBER_OF_WORDS = 4  # How many words to combine
SEPARATOR = "-"  # Character to join the words
MIN_WORD_LENGTH = 4  # Ignore very short words from the list
# ---------------------


def load_word_list(filename, min_length):
    """
    Loads a word list from a file, cleans it, and filters by length.
    """
    try:
        with open(filename, "r") as f:
            words = f.readlines()

        # Clean up the words:
        # 1. Strip whitespace (like the newline '\n' at the end)
        # 2. Convert to lowercase
        # 3. Filter out any lines that are too short
        cleaned_words = [
            word.strip().lower() for word in words if len(word.strip()) >= min_length
        ]

        if not cleaned_words:
            print(
                f"Error: No words found in '{filename}' that meet the minimum length of {min_length}.",
                file=sys.stderr,
            )
            return None

        return cleaned_words

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.", file=sys.stderr)
        return None
    except Exception as e:
        print(f"An error occurred while reading the file: {e}", file=sys.stderr)
        return None


def generate_passphrase(word_list, num_words, separator):
    """
    Generates a secure passphrase using the 'secrets' module.
    """
    # Use secrets.choice() to securely and randomly pick from the list
    chosen_words = [secrets.choice(word_list) for _ in range(num_words)]

    # Join the chosen words with the separator
    return separator.join(chosen_words)


def main():
    """
    Main function to load words and generate the passphrase.
    """
    print(f"Loading words from '{WORDLIST_FILENAME}'...")
    word_list = load_word_list(WORDLIST_FILENAME, MIN_WORD_LENGTH)

    if word_list:
        print(f"Word list loaded successfully ({len(word_list)} words).")

        # Generate the passphrase
        passphrase = generate_passphrase(word_list, NUMBER_OF_WORDS, SEPARATOR)

        print("\n--- Your Secure Passphrase ---")
        print(f"     {passphrase}")
        print("--------------------------------")


if __name__ == "__main__":
    main()
