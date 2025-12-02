#include <iostream>
#include <string>

using namespace std;

// --- State Definitions ---
// q0: Start/Scan state. Skips 'X', searches for 'a'.
//     If 'a' found -> mark 'X', go to q1.
//     If end reached -> Accept (string was all X's).
//     If 'b' or 'c' found -> Reject.
// q1: Search for 'b'. Skips 'a', 'X'.
//     If 'b' found -> mark 'X', go to q2.
//     If 'c' or end -> Reject.
// q2: Search for 'c'. Skips 'b', 'X'.
//     If 'c' found -> mark 'X', go to q3.
//     If 'a' or end -> Reject.
// q3: Return to start (extreme left).
//     Moves head left until 0, then back to q0.

bool q0(string& tape, int head);
bool q1(string& tape, int head);
bool q2(string& tape, int head);
bool q3(string& tape, int head);

// --- State Implementations ---

bool q0(string& tape, int head) {
    // Logic: Scan for the next 'a' to process
    if (head >= tape.length()) {
        return true; // All characters processed (all turned to X)
    }

    if (tape[head] == 'X') {
        return q0(tape, head + 1); // Skip processed chars
    }
    else if (tape[head] == 'a') {
        tape[head] = 'X'; // Mark 'a' with 'X'
        return q1(tape, head + 1); // Go find matching 'b'
    }
    
    // If we find 'b' or 'c' here, it means they are extra or out of order because we haven't started a new triplet cycle yet.
    return false; 
}

bool q1(string& tape, int head) {
    // Logic: Search for 'b'
    if (head >= tape.length()) return false; // Ran out of tape

    if (tape[head] == 'a' || tape[head] == 'X') {
        return q1(tape, head + 1); // Skip intervening 'a's or 'X's
    }
    else if (tape[head] == 'b') {
        tape[head] = 'X'; // Mark 'b' with 'X'
        return q2(tape, head + 1); // Go find matching 'c'
    }

    // Found 'c' before 'b', or invalid char
    return false;
}

bool q2(string& tape, int head) {
    // Logic: Search for 'c'
    if (head >= tape.length()) return false; // Ran out of tape

    if (tape[head] == 'b' || tape[head] == 'X') {
        return q2(tape, head + 1); // Skip intervening 'b's or 'X's
    }
    else if (tape[head] == 'c') {
        tape[head] = 'X'; // Mark 'c' with 'X'
        return q3(tape, head - 1); // Move Left to return to start
    }

    return false;
}

bool q3(string& tape, int head) {
    // Logic: Move Left until head is 0 (Extreme Left)
    if (head > 0) {
        return q3(tape, head - 1);
    }
    // Once at 0, restart the cycle search
    return q0(tape, 0);
}

int main() {
    string tape;
    cout << "--- Turing Machine for a^n b^n c^n (Method: Replace all with X) ---" << endl;
    cout << "Enter string: ";
    getline(cin, tape);

    // Validate basic input
    for (char c : tape) {
        if (c != 'a' && c != 'b' && c != 'c') {
            cout << "Invalid characters in input." << endl;
            return 0;
        }
    }

    if (tape.empty()) {
        cout << "String Rejected (n > 0)" << endl;
        return 0;
    }

    cout << "Simulating..." << endl;
    
    bool result = q0(tape, 0);

    cout << "Final Tape: " << tape << endl;
    if (result) {
        cout << "Result: String Accepted" << endl;
    } else {
        cout << "Result: String Rejected" << endl;
    }

    return 0;
}
