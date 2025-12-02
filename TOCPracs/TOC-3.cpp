#include <iostream>
#include <string>
using namespace std;

// Function declarations
bool state0(const string& w, int i);
bool state1A(const string& w, int i);
bool state1B(const string& w, int i);
bool state2A(const string& w, int i);
bool state2B(const string& w, int i);
bool state3(const string& w, int i);
bool state4(const string& w, int i);
bool state5(const string& w, int i);
bool state6(const string& w, int i);
bool state7(const string& w, int i);
bool state8(const string& w, int i);
bool final_state(const string& w, int i);

// Start state
bool state0(const string& w, int i) {
    cout << " -> S0";
    if (i >= w.length()) return false;
    if (w[i] == 'a') return state1A(w, i + 1);
    else if (w[i] == 'b') return state2A(w, i + 1);
    return false;
}

// First char = a, second char = a
bool state1A(const string& w, int i) {
    cout << " -> S1A";
    if (i >= w.length()) return false;
    if (w[i] == 'a') return state3(w, i + 1);
    else if (w[i] == 'b') return state4(w, i + 1);
    return false;
}

// First char = a, second char = b
bool state1B(const string& w, int i) {
    cout << " -> S1B";
    if (i >= w.length()) return false;
    if (w[i] == 'a') return state5(w, i + 1);
    else if (w[i] == 'b') return state6(w, i + 1);
    return false;
}

// First char = b, second char = a
bool state2A(const string& w, int i) {
    cout << " -> S2A";
    if (i >= w.length()) return false;
    if (w[i] == 'a') return state7(w, i + 1);
    else if (w[i] == 'b') return state8(w, i + 1);
    return false;
}

// First char = b, second char = b
bool state2B(const string& w, int i) {
    cout << " -> S2B";
    if (i >= w.length()) return false;
    if (w[i] == 'a') return state5(w, i + 1);
    else if (w[i] == 'b') return state6(w, i + 1);
    return false;
}

bool state3(const string& w, int i) {
    cout << " -> S3";
    if (i >= w.length() - 2) return final_state(w, i);
    return state3(w, i + 1);
}

bool state4(const string& w, int i) {
    cout << " -> S4";
    if (i >= w.length() - 2) return final_state(w, i);
    return state4(w, i + 1);
}

bool state5(const string& w, int i) {
    cout << " -> S5";
    if (i >= w.length() - 2) return final_state(w, i);
    return state5(w, i + 1);
}

bool state6(const string& w, int i) {
    cout << " -> S6";
    if (i >= w.length() - 2) return final_state(w, i);
    return state6(w, i + 1);
}

bool state7(const string& w, int i) {
    cout << " -> S7";
    if (i >= w.length() - 2) return final_state(w, i);
    return state7(w, i + 1);
}

bool state8(const string& w, int i) {
    cout << " -> S8";
    if (i >= w.length() - 2) return final_state(w, i);
    return state8(w, i + 1);
}

// Final accepting state
bool final_state(const string& w, int i) {
    cout << " -> Final";
    if (i + 2 > w.length()) return false;
    string first2 = w.substr(0,2);
    string last2 = w.substr(w.length() - 2, 2);
    return first2 == last2;
}

int main() {
    string input_string;
    cout << "Enter a string over {a, b}: ";
    getline(cin, input_string);

    for (char c : input_string) {
        if (c != 'a' && c != 'b') {
            cout << "Wrong Input!!\n";
            return 0;
        }
    }

    cout << "State transitions: Start";
    bool accepted = state0(input_string, 0);

    if (accepted) cout << "\nString Accepted" << endl;
    else cout << "\nString Rejected" << endl;
}
