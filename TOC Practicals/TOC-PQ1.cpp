    #include <iostream>
    #include <string>

    using namespace std;

    // --- State Definitions ---
    // S0: (even a, even b) - START, FINAL
    // S1: (odd a,  even b)
    // S2: (even a, odd b)
    // S3: (odd a,  odd b)

    bool state0(const string& w, int i);
    bool state1(const string& w, int i);
    bool state2(const string& w, int i);
    bool state3(const string& w, int i);

    // S0: (even a, even b) - START, FINAL
    bool state0(const string& w, int i) {
        cout << " -> S0";
        if (i == w.length()) return true; // Accept
        if (w[i] == 'a') return state1(w, i + 1); // odd a
        else if (w[i] == 'b') return state2(w, i + 1); // odd b
        return false; // Should not happen with validated input
    }

    // S1: (odd a,  even b)
    bool state1(const string& w, int i) {
        cout << " -> S1";
        if (i == w.length()) return false; // Reject
        if (w[i] == 'a') return state0(w, i + 1); // even a
        else if (w[i] == 'b') return state3(w, i + 1); // odd b
        return false;
    }

    // S2: (even a, odd b)
    bool state2(const string& w, int i) {
        cout << " -> S2";
        if (i == w.length()) return false; // Reject
        if (w[i] == 'a') return state3(w, i + 1); // odd a
        else if (w[i] == 'b') return state0(w, i + 1); // even b
        return false;
    }

    // S3: (odd a,  odd b)
    bool state3(const string& w, int i) {
        cout << " -> S3";
        if (i == w.length()) return false; // Reject
        if (w[i] == 'a') return state2(w, i + 1); // even a
        else if (w[i] == 'b') return state1(w, i + 1); // even b
        return false;
    }

    int main() {
        string input_string;
        cout << "FA for (Even 'a's AND Even 'b's)\n";
        cout << "Enter a string (using 'a' and 'b') or 'q' to quit: ";

        // Use getline to correctly read an empty string
        while (getline(cin, input_string) && input_string != "q") {

            // Validate input
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
                cout << "\nString: \"" << input_string << "\"" << endl;
                cout << "State transitions: Start";

                // Start the FA simulation at state 0
                bool accepted = state0(input_string, 0);

                if (accepted) cout << "\n\nResult: String Accepted" << endl;
                else cout << "\n\nResult: String Rejected" << endl;
            }

            cout << "\n----------------------------------\n";
            cout << "Enter a string (using 'a' and 'b') or 'q' to quit: ";
        }

        return 0;
    }
