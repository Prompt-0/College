/**
 * Question 3 (Revised Compact Version):
 * Design a Finite Automata (FA) that accepts language L1, over Σ={a,b},
 * comprising of all strings (of length 4 or more) having first two characters
 * same as the last two.
 *
 * This version uses a standard simulation loop instead of one function per state,
 * making the code much more concise and readable.
 */
#include <iostream>
#include <string>
#include <vector>
#include <set>

// Enumerate all the states required for the FA for better readability.
enum State {
    // Initial states to read the prefix
    Q_START, Q_FIRST_A, Q_FIRST_B,

    // States after reading the two-character prefix.
    // These are the starting points for checking the suffix.
    Q_PREFIX_AA, Q_PREFIX_AB, Q_PREFIX_BA, Q_PREFIX_BB,

    // States within each prefix branch to track the suffix
    Q_AA_SEEN_A, Q_AB_SEEN_A, Q_BA_SEEN_B, Q_BB_SEEN_B,

    // Final (accepting) states
    Q_FINAL_AA, Q_FINAL_AB, Q_FINAL_BA, Q_FINAL_BB,

    // A state for invalid input
    Q_REJECT
};

// Function to simulate the FA
void simulate_fa(const std::string& w) {
    State current_state = Q_START;
    std::string prefix = "";

    // 1. Determine the two-character prefix and set the starting state for the main loop
    if (w.length() < 2) {
        current_state = Q_REJECT;
    } else {
        prefix = w.substr(0, 2);
        if (prefix == "aa") current_state = Q_PREFIX_AA;
        else if (prefix == "ab") current_state = Q_PREFIX_AB;
        else if (prefix == "ba") current_state = Q_PREFIX_BA;
        else if (prefix == "bb") current_state = Q_PREFIX_BB;
    }

    // 2. Loop through the rest of the string (from the 3rd character)
    for (int i = 2; i < w.length(); ++i) {
        char current_char = w[i];
        switch (current_state) {
            // --- Branch for prefix "aa" ---
            case Q_PREFIX_AA:
                if (current_char == 'a') current_state = Q_AA_SEEN_A;
                break;
            case Q_AA_SEEN_A:
                if (current_char == 'a') current_state = Q_FINAL_AA;
                else current_state = Q_PREFIX_AA; // Not "aa", reset
                break;
            case Q_FINAL_AA:
                if (current_char == 'b') current_state = Q_PREFIX_AA;
                break;

            // --- Branch for prefix "ab" ---
            case Q_PREFIX_AB:
                if (current_char == 'a') current_state = Q_AB_SEEN_A;
                break;
            case Q_AB_SEEN_A:
                if (current_char == 'b') current_state = Q_FINAL_AB;
                // if 'a', we stay in Q_AB_SEEN_A
                break;
            case Q_FINAL_AB:
                if (current_char == 'a') current_state = Q_AB_SEEN_A;
                else current_state = Q_PREFIX_AB;
                break;

            // --- Branch for prefix "ba" ---
            case Q_PREFIX_BA:
                if (current_char == 'b') current_state = Q_BA_SEEN_B;
                break;
            case Q_BA_SEEN_B:
                if (current_char == 'a') current_state = Q_FINAL_BA;
                // if 'b', we stay in Q_BA_SEEN_B
                break;
            case Q_FINAL_BA:
                if (current_char == 'b') current_state = Q_BA_SEEN_B;
                else current_state = Q_PREFIX_BA;
                break;

            // --- Branch for prefix "bb" ---
            case Q_PREFIX_BB:
                if (current_char == 'b') current_state = Q_BB_SEEN_B;
                break;
            case Q_BB_SEEN_B:
                if (current_char == 'b') current_state = Q_FINAL_BB;
                else current_state = Q_PREFIX_BB;
                break;
            case Q_FINAL_BB:
                if (current_char == 'a') current_state = Q_PREFIX_BB;
                break;
        }
    }

    // 3. Check if the final state is an accepting state
    std::set<State> final_states = {Q_FINAL_AA, Q_FINAL_AB, Q_FINAL_BA, Q_FINAL_BB};
    if (final_states.count(current_state)) {
        std::cout << "\n[Accepted]" << std::endl;
    } else {
        std::cout << "\n[Rejected]" << std::endl;
    }
}


int main() {
    std::string input_string;
    std::cout << "--- Q3 (Revised): FA for L1 (first two chars == last two chars) ---" << std::endl;
    std::cout << "Enter a string over {a, b} of length 4 or more: ";
    std::cin >> input_string;

    // Initial validation check
    if (input_string.length() < 4) {
        std::cout << "\n[Rejected]: Length must be 4 or more." << std::endl;
        return 0;
    }

    simulate_fa(input_string);

    return 0;
}