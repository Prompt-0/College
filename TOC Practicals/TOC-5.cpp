#include <iostream>
#include <string>

using namespace std;

bool state0(const string& w, int i);
bool state1(const string& w, int i);
bool state2(const string& w, int i);
bool state3(const string& w, int i);

bool state0(const string& w, int i) { // (even a, even b)
    cout << " -> S0";
    if (i == w.length()) return true;
    if (w[i] == 'a') return state1(w, i + 1);
    else if (w[i] == 'b') return state2(w, i + 1);
    return false;
}

bool state1(const string& w, int i) { // (odd a,  even b)
    cout << " -> S1";
    if (i == w.length()) return false;
    if (w[i] == 'a') return state0(w, i + 1);
    else if (w[i] == 'b') return state3(w, i + 1);
    return false;
}

bool state2(const string& w, int i) { // (even a, odd b)
    cout << " -> S2";
    if (i == w.length()) return false;
    if (w[i] == 'a') return state3(w, i + 1);
    else if (w[i] == 'b') return state0(w, i + 1);
    return false;
}

bool state3(const string& w, int i) { // (odd a,  odd b)
    cout << " -> S3";
    if (i == w.length()) return false;
    if (w[i] == 'a') return state2(w, i + 1);
    else if (w[i] == 'b') return state1(w, i + 1);
    return false;
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

    return 0;
}
