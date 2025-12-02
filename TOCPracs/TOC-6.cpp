#include <iostream>
#include <string>

using namespace std;


// --- FA definitions ---

// L1: {a, b}*a (ends in 'a')
// q0 = not accepting, q1 = accepting
bool L1_q0(const string& w, int i);
bool L1_q1(const string& w, int i);

// L2: {a, b}*b (ends in 'b')
// r0 = not accepting, r1 = accepting
bool L2_r0(const string& w, int i);
bool L2_r1(const string& w, int i);

// Union (L1 | L2)
// States are (L1_state, L2_state)
// Accepting if L1 is accepting OR L2 is accepting
bool U_q0r0(const string& w, int i);
bool U_q0r1(const string& w, int i);
bool U_q1r0(const string& w, int i);
bool U_q1r1(const string& w, int i);

// Intersection (L1 & L2)
// States are (L1_state, L2_state)
// Accepting if L1 is accepting AND L2 is accepting
bool I_q0r0(const string& w, int i);
bool I_q0r1(const string& w, int i);
bool I_q1r0(const string& w, int i);
bool I_q1r1(const string& w, int i);

// Concatenation (L1 L2)
// NFA simulation. States C_q* from L1, C_r* from L2
// Start state is C_q0. Accepting states are C_r1.
bool C_q0(const string& w, int i);
bool C_q1(const string& w, int i);
bool C_r0(const string& w, int i);
bool C_r1(const string& w, int i);


// --- L1 Implementation (ends in 'a') ---
bool L1_q0(const string& w, int i) {
    if (i == w.length()) {
        return false; // End of string, not accepting
    }
    char c = w[i];
    if (c == 'a') {
        return L1_q1(w, i + 1);
    } else { // 'b'
        return L1_q0(w, i + 1);
    }
}

bool L1_q1(const string& w, int i) {
    if (i == w.length()) {
        return true; // End of string, is accepting
    }
    char c = w[i];
    if (c == 'a') {
        return L1_q1(w, i + 1);
    } else { // 'b'
        return L1_q0(w, i + 1);
    }
}

// --- L2 Implementation (ends in 'b') ---
bool L2_r0(const string& w, int i) {
    if (i == w.length()) {
        return false;
    }
    char c = w[i];
    if (c == 'a') {
        return L2_r0(w, i + 1);
    } else { // 'b'
        return L2_r1(w, i + 1);
    }
}

bool L2_r1(const string& w, int i) {
    if (i == w.length()) {
        return true;
    }
    char c = w[i];
    if (c == 'a') {
        return L2_r0(w, i + 1);
    } else { // 'b'
        return L2_r1(w, i + 1);
    }
}

// --- Union (L1 | L2) Implementation ---
// State (q0, r0), Start state
bool U_q0r0(const string& w, int i) {
    if (i == w.length()) {
        return false; // q0 not accepting, r0 not accepting
    }
    char c = w[i];
    if (c == 'a') { // L1: q0->q1, L2: r0->r0
        return U_q1r0(w, i + 1);
    } else { // 'b' - L1: q0->q0, L2: r0->r1
        return U_q0r1(w, i + 1);
    }
}

// State (q0, r1)
bool U_q0r1(const string& w, int i) {
    if (i == w.length()) {
        return true; // r1 is accepting
    }
    char c = w[i];
    if (c == 'a') { // L1: q0->q1, L2: r1->r0
        return U_q1r0(w, i + 1);
    } else { // 'b' - L1: q0->q0, L2: r1->r1
        return U_q0r1(w, i + 1);
    }
}

// State (q1, r0)
bool U_q1r0(const string& w, int i) {
    if (i == w.length()) {
        return true; // q1 is accepting
    }
    char c = w[i];
    if (c == 'a') { // L1: q1->q1, L2: r0->r0
        return U_q1r1(w, i + 1);
    } else { // 'b' - L1: q1->q0, L2: r0->r1
        return U_q0r1(w, i + 1);
    }
}

// State (q1, r1)
bool U_q1r1(const string& w, int i) {
    if (i == w.length()) {
        return true; // Both q1 and r1 are accepting
    }
    char c = w[i];
    if (c == 'a') { // L1: q1->q1, L2: r1->r0
        return U_q1r0(w, i + 1);
    } else { // 'b' - L1: q1->q0, L2: r1->r1
        return U_q0r1(w, i + 1);
    }
}

// --- Intersection (L1 & L2) Implementation ---
// Transitions are identical to Union, only base cases change.
bool I_q0r0(const string& w, int i) {
    if (i == w.length()) {
        return false; // NOT (q1 AND r1)
    }
    char c = w[i];
    if (c == 'a') {
        return I_q1r0(w, i + 1);
    } else { // 'b'
        return I_q0r1(w, i + 1);
    }
}

bool I_q0r1(const string& w, int i) {
    if (i == w.length()) {
        return false; // NOT (q1 AND r1)
    }
    char c = w[i];
    if (c == 'a') {
        return I_q1r0(w, i + 1);
    } else { // 'b'
        return I_q0r1(w, i + 1);
    }
}

bool I_q1r0(const string& w, int i) {
    if (i == w.length()) {
        return false; // NOT (q1 AND r1)
    }
    char c = w[i];
    if (c == 'a') {
        return I_q1r1(w, i + 1);
    } else { // 'b'
        return I_q0r1(w, i + 1);
    }
}

bool I_q1r1(const string& w, int i) {
    if (i == w.length()) {
        return true; // IS (q1 AND r1)
    }
    char c = w[i];
    if (c == 'a') {
        return I_q1r0(w, i + 1);
    } else { // 'b'
        return I_q0r1(w, i + 1);
    }
}


// --- Concatenation (L1 L2) NFA Implementation ---

// State q0 from L1 (Start State of combined NFA)
bool C_q0(const string& w, int i) {
    if (i == w.length()) {
        return false;
    }

    // L1's transitions
    char c = w[i];
    if (c == 'a') {
        return C_q1(w, i + 1);
    } else { // 'b'
        return C_q0(w, i + 1);
    }
}

// State q1 from L1 (Accepting state in L1)
bool C_q1(const string& w, int i) {
    // When we are in an accepting state of L1, we have two
    // non-deterministic choices (epsilon transitions):

    // Choice 1: Jump to the start of L2.
    // This transition consumes no input, so we pass the *current* index.
    bool jump_to_L2 = C_r0(w, i);

    // Choice 2: Stay in L1 and consume the next character.
    // This is only possible if we are not at the end of the string.
    bool stay_in_L1 = false;
    if (i < w.length()) {
        char c = w[i];
        if (c == 'a') {
            stay_in_L1 = C_q1(w, i + 1);
        } else { // 'b'
            stay_in_L1 = C_q0(w, i + 1);
        }
    }

    // The string is accepted if *either* choice leads to acceptance.
    return jump_to_L2 || stay_in_L1;
}

// State r0 from L2 (Start state of L2)
bool C_r0(const string& w, int i) {
    if (i == w.length()) {
        return false; // Not an accepting state in L2
    }

    // L2's transitions
    char c = w[i];
    if (c == 'a') {
        return C_r0(w, i + 1);
    } else { // 'b'
        return C_r1(w, i + 1);
    }
}

// State r1 from L2 (Accepting state of L2)
// This is the *only* accepting state set for the concatenated machine.
bool C_r1(const string& w, int i) {
    if (i == w.length()) {
        return true; // FINAL accepting state
    }

    // L2's transitions
    char c = w[i];
    if (c == 'a') {
        return C_r0(w, i + 1);
    } else { // 'b'
        return C_r1(w, i + 1);
    }
}


int main() {
    string input_string;
    cout << "Enter a string (using 'a' and 'b') or 'q' to quit: ";

    // Read input repeatedly in a loop until user enters 'q'
    while (getline(cin, input_string) && input_string != "q") {

        // --- Validate input ---
        bool valid_input = true;
        for (char c : input_string) {
            if (c != 'a' && c != 'b') {
                valid_input = false;
                break;
            }
        }

        if (!valid_input) {
            cout << "Invalid character in string. Only 'a' and 'b' are allowed." << endl;
        } else {
            cout << "--- String: \"" << input_string << "\" ---" << endl;

            // Test L1 (ends in 'a')
            bool l1_accept = L1_q0(input_string, 0);
            cout << "L1 (ends in 'a'):\t\t" << (l1_accept ? "Accept" : "Reject") << endl;

            // Test L2 (ends in 'b')
            bool l2_accept = L2_r0(input_string, 0);
            cout << "L2 (ends in 'b'):\t\t" << (l2_accept ? "Accept" : "Reject") << endl;

            // Test Union (L1 | L2)
            bool union_accept = U_q0r0(input_string, 0);
            cout << "Union (L1 | L2):\t\t" << (union_accept ? "Accept" : "Reject") << endl;

            // Test Intersection (L1 & L2)
            bool inter_accept = I_q0r0(input_string, 0);
            cout << "Intersection (L1 & L2):\t" << (inter_accept ? "Accept" : "Reject") << endl;

            // Test Concatenation (L1 L2)
            bool concat_accept = C_q0(input_string, 0);
            cout << "Concatenation (L1 L2):\t" << (concat_accept ? "Accept" : "Reject") << endl;
        }

        cout << "\nEnter a string (using 'a' and 'b') or 'q' to quit: ";
    }

    return 0;
}
