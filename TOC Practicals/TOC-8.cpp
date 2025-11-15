#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Forward declaration for mutual recursion
bool state1_pop(const string& str, int i, stack<char>& pda_stack);

/**
 * @brief Represents state 0: Reading 'w' and pushing symbols.
 * This is the starting state.
 */
bool state0_push(const string& str, int i, stack<char>& pda_stack) {
    // Check if we are at the end of the string
    if (i >= str.length()) {
        // We finished before seeing the 'X' marker
        return false;
    }

    char c = str[i];

    if (c == 'a' || c == 'b') {
        // Push the character onto the stack
        pda_stack.push(c);
        // Stay in state 0, move to next character
        return state0_push(str, i + 1, pda_stack);
    } else if (c == 'X') {
        // On 'X', we transition to the popping state
        // Do not push 'X'
        // Move to state 1, move to next character
        return state1_pop(str, i + 1, pda_stack);
    } else {
        // Invalid character
        return false;
    }
}

/**
 * @brief Represents state 1: Reading 'w^r' and popping to match.
 */
bool state1_pop(const string& str, int i, stack<char>& pda_stack) {
    // Check if we are at the end of the string
    if (i >= str.length()) {
        // If we finish here, the string is accepted ONLY if the stack is empty
        // (meaning w and w^r were perfect matches)
        return pda_stack.empty();
    }

    char c = str[i];

    if (c == 'a' || c == 'b') {
        // We must have a matching symbol on the stack
        if (pda_stack.empty()) {
            // w^r is longer than w
            return false;
        }

        char top = pda_stack.top();
        pda_stack.pop();

        if (c != top) {
            // Mismatch (e.g., input 'a' but stack had 'b')
            return false;
        }

        // Match successful, stay in state 1, move to next character
        return state1_pop(str, i + 1, pda_stack);
    } else {
        // Invalid character (e.g., another 'X')
        return false;
    }
}

int main() {
    string input;
    cout << "--- PDA Simulator for {wXw^r | w in {a,b}*} (Recursive) ---" << endl;
    cout << "Enter a string: ";
    cin >> input;

    stack<char> s;
    // Start simulation in state 0 (pushing) at index 0
    bool result = state0_push(input, 0, s);

    if (result) {
        cout << "Result: Accepted" << endl;
    } else {
        cout << "Result: Rejected" << endl;
    }
    return 0;
}
