#include <iostream>
#include <string>

using namespace std;

// --- State Definitions ---
// q0: Move Right to the end of the string (LSB)
// q1: Perform addition (carry logic) moving Left

bool q0(string& tape, int head);
bool q1(string& tape, int head);

bool q0(string& tape, int head) {
    // Logic: Move head to the rightmost bit
    if (head < tape.length()) {
        return q0(tape, head + 1);
    }
    // When head reaches length (past the last char), move left to last char and switch state
    return q1(tape, head - 1);
}

bool q1(string& tape, int head) {
    // Logic: Add 1.
    // If char is '0' -> become '1', Done (Accept)
    // If char is '1' -> become '0', Move Left (Carry)
    
    if (head < 0) {
        // Overflow case (e.g., 111 -> 1000)
        // We moved past the start of the string implies we have a carry left over.
        tape.insert(0, "1");
        return true; // Accepted
    }

    if (tape[head] == '0') {
        tape[head] = '1';
        return true; // No carry generated, we are done.
    }
    else if (tape[head] == '1') {
        tape[head] = '0';
        return q1(tape, head - 1); // Carry over to the left
    }

    return false; 
}

int main() {
    string tape;
    cout << "--- Turing Machine: Binary Increment (+1) ---" << endl;
    cout << "Enter a binary number: ";
    getline(cin, tape);

    // Validate input
    for (char c : tape) {
        if (c != '0' && c != '1') {
            cout << "Invalid Input! Only 0 and 1 allowed." << endl;
            return 0;
        }
    }

    if (tape.empty()) {
        cout << "Empty input." << endl;
        return 0;
    }

    cout << "Original Tape: " << tape << endl;

    q0(tape, 0);

    cout << "Result Tape:   " << tape << endl;

    return 0;
}
